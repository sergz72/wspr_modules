#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define HOST "wsprnet.org"
#define PAGE "/post"
#define PORT 80
#define USERAGENT "uploader 1.0"
#define RQRG_OFFSET 1500

int create_tcp_socket()
{
  int sock;
  if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
  {
    perror("Can't create TCP socket");
    exit(2);
  }
  return sock;
}

#define IPLEN 15

char *get_ip(char *host)
{
  struct hostent *hent;
  static char ip[IPLEN + 1]; //XXX.XXX.XXX.XXX
  if((hent = gethostbyname(host)) == NULL)
  {
    herror("Can't get IP");
    exit(3);
  }
  if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, IPLEN) == NULL)
  {
    perror("Can't resolve host");
    exit(4);
  }
  return ip;
}

#define QUERYMAX 500

char *build_get_query(char *params)
{
  static char query[QUERYMAX];
  static const char *format = "GET " PAGE "?%s HTTP/1.1\r\nHost: " HOST "\r\nUser-Agent: " USERAGENT "\r\n\r\n";
  snprintf(query, QUERYMAX, format, params);
  return query;
}

#define MAXPARAMS 300

char *build_params(char *line, char *call, char* grid, char *version, char *mode, int rqrg, int date, int time)
{
  static char params[MAXPARAMS];
  char srqrg[20], *sig, *dt, *freq, *tcall, *tgrid, *pwr, *drift;
  
  rqrg += 1500;
  snprintf(srqrg, 20, "%d.%06d", rqrg / 1000000, rqrg % 1000000);
  
  dt = strtok(line, " ");
  
  do
  {
    if (strchr(dt, '.'))
      break;
    sig = dt;
  } while ((dt = strtok(NULL, " ")));
  
  if (!dt)
    return NULL;
  
  freq = strtok(NULL, " ");
  tcall = strtok(NULL, " ");
  tgrid = strtok(NULL, " ");
  pwr = strtok(NULL, " ");
  drift = strtok(NULL, " ");
  if (strlen(tgrid) == 2)
  {
    drift = pwr;
    pwr = tgrid;
    tgrid = "";
  }
  
  snprintf(params, MAXPARAMS,
           "function=wspr&rcall=%s&rgrid=%s&rqrg=%s&date=%06d&time=%04d&sig=%s&dt=%s"
           "&drift=%s&tqrg=%s&tcall=%s&tgrid=%s&dbm=%s&version=%s&mode=%s",
           call, grid, srqrg, date, time, sig, dt, drift, freq, tcall, tgrid, pwr, version, mode);
  
  return params;
}

#define LINEMAX 200

int main(int argc, char **argv)
{
  struct sockaddr_in remote;
  int sock, tmpres, len, sent, test_mode, rqrg, MHz, date, time;
  time_t timestamp;
  char *ip, *get, *params, *filename, *freq, *call, *grid, *version, *mode;
  static char buf[BUFSIZ+1], line[LINEMAX];
  FILE * fh;
  struct tm *t;
  
  test_mode = argc == 9;
  
  if ((argc != 8 && argc != 9) || (test_mode && strcmp(argv[8], "test")))
  {
    fprintf(stderr, "Usage: wsprupload file_name frequency timestamp call grid version mode [test]\n");
    return 1;
  }

  filename = argv[1];
  freq = argv[2];
  timestamp = atoi(argv[3]);
  call = argv[4];
  grid = argv[5];
  version= argv[6];
  mode = argv[7];
  
  sscanf(freq, "%d.%d", &MHz, &rqrg);
  rqrg += MHz * 1000000;
  
  t = gmtime(&timestamp);
  date = (t->tm_year - 100) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;
  time = t->tm_hour * 100 + t->tm_min;  
  
  if (!test_mode)
  {
    ip = get_ip(HOST);
    printf("IP for host " HOST " is %s\n", ip);
    remote.sin_family = AF_INET;
    tmpres = inet_pton(AF_INET, ip, (void *)(&(remote.sin_addr.s_addr)));
    if (tmpres < 0)  
    {
      perror("Can't set remote.sin_addr.s_addr");
      return 5;
    }
    else if (tmpres == 0)
    {
      fprintf(stderr, "%s is not a valid IP address\n", ip);
      return 6;
    }
    remote.sin_port = htons(PORT);
  }
  
  fh = fopen(argv[1], "r");
  if (fh == NULL)
  {
    fprintf(stderr, "File open error.");
    return 7;
  }
  
  while (fgets(line, LINEMAX, fh) != NULL)
  {
    params = build_params(line, call, grid, version, mode, rqrg, date, time);
    if (params == NULL)
      continue;
    get = build_get_query(params);
    fprintf(stderr, "Query is:\n%s\n", get);
    if (test_mode)
      continue;
    
    sock = create_tcp_socket();

    if(connect(sock, (struct sockaddr *)&remote, sizeof(struct sockaddr)) < 0)
    {
      perror("Could not connect");
      fclose(fh);
      return 8;
    }

    //Send the query to the server
    sent = 0;
    len = strlen(get);
    while(sent < len)
    {
      tmpres = send(sock, get+sent, len-sent, 0);
      if(tmpres == -1){
        perror("Can't send query");
        fclose(fh);
        close(sock);
        return 9;
      }
      sent += tmpres;
    }
    
    //now it is time to receive the answer
    if ((tmpres = recv(sock, buf, BUFSIZ, 0)) > 0)
    {
      buf[tmpres] = 0;
      printf(buf);
    }
    else if(tmpres < 0)
      perror("Error receiving answer.");
    close(sock);
  }
  
  return 0;
}

