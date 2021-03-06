EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:transistors-mics
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L BF513 Q1
U 1 1 5899CB59
P 1850 1300
F 0 "Q1" H 1753 1550 70  0000 C CNN
F 1 "KP903A" H 1703 1053 60  0000 C CNN
F 2 "" H 1850 1300 60  0000 C CNN
F 3 "" H 1850 1300 60  0000 C CNN
	1    1850 1300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P1
U 1 1 5899CBC3
P 900 1750
F 0 "P1" H 900 1900 50  0000 C CNN
F 1 "IN" V 1000 1750 50  0000 C CNN
F 2 "" H 900 1750 50  0000 C CNN
F 3 "" H 900 1750 50  0000 C CNN
	1    900  1750
	-1   0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5899CC1A
P 1250 2150
F 0 "R1" V 1330 2150 50  0000 C CNN
F 1 "51" V 1250 2150 50  0000 C CNN
F 2 "" V 1180 2150 50  0000 C CNN
F 3 "" H 1250 2150 50  0000 C CNN
	1    1250 2150
	1    0    0    -1  
$EndComp
$Comp
L BF513 Q2
U 1 1 5899CCB3
P 2450 1300
F 0 "Q2" H 2353 1550 70  0000 C CNN
F 1 "KP903A" H 2303 1053 60  0000 C CNN
F 2 "" H 2450 1300 60  0000 C CNN
F 3 "" H 2450 1300 60  0000 C CNN
	1    2450 1300
	1    0    0    -1  
$EndComp
$Comp
L BF513 Q3
U 1 1 5899CCE5
P 3050 1300
F 0 "Q3" H 2953 1550 70  0000 C CNN
F 1 "KP903A" H 2903 1053 60  0000 C CNN
F 2 "" H 3050 1300 60  0000 C CNN
F 3 "" H 3050 1300 60  0000 C CNN
	1    3050 1300
	1    0    0    -1  
$EndComp
$Comp
L BF513 Q4
U 1 1 5899CD1C
P 3650 1300
F 0 "Q4" H 3553 1550 70  0000 C CNN
F 1 "KP903A" H 3503 1053 60  0000 C CNN
F 2 "" H 3650 1300 60  0000 C CNN
F 3 "" H 3650 1300 60  0000 C CNN
	1    3650 1300
	1    0    0    -1  
$EndComp
$Comp
L BF513 Q5
U 1 1 5899CD60
P 4250 1300
F 0 "Q5" H 4153 1550 70  0000 C CNN
F 1 "KP903A" H 4103 1053 60  0000 C CNN
F 2 "" H 4250 1300 60  0000 C CNN
F 3 "" H 4250 1300 60  0000 C CNN
	1    4250 1300
	1    0    0    -1  
$EndComp
$Comp
L BF513 Q6
U 1 1 5899CD9B
P 4850 1300
F 0 "Q6" H 4753 1550 70  0000 C CNN
F 1 "KP903A" H 4703 1053 60  0000 C CNN
F 2 "" H 4850 1300 60  0000 C CNN
F 3 "" H 4850 1300 60  0000 C CNN
	1    4850 1300
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5899CEBD
P 2000 1950
F 0 "R2" V 2080 1950 50  0000 C CNN
F 1 "510" V 2000 1950 50  0000 C CNN
F 2 "" V 1930 1950 50  0000 C CNN
F 3 "" H 2000 1950 50  0000 C CNN
	1    2000 1950
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5899CF05
P 2000 2350
F 0 "R3" V 2080 2350 50  0000 C CNN
F 1 "1k" V 2000 2350 50  0000 C CNN
F 2 "" V 1930 2350 50  0000 C CNN
F 3 "" H 2000 2350 50  0000 C CNN
	1    2000 2350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5899CF47
P 1700 1950
F 0 "C1" H 1725 2050 50  0000 L CNN
F 1 "100n" H 1725 1850 50  0000 L CNN
F 2 "" H 1738 1800 50  0000 C CNN
F 3 "" H 1700 1950 50  0000 C CNN
	1    1700 1950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 5899D12E
P 1650 2350
F 0 "P2" H 1650 2500 50  0000 C CNN
F 1 "OUT1" H 1650 2200 50  0000 C CNN
F 2 "" H 1650 2350 50  0000 C CNN
F 3 "" H 1650 2350 50  0000 C CNN
	1    1650 2350
	-1   0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5899D2E7
P 2600 1950
F 0 "R4" V 2680 1950 50  0000 C CNN
F 1 "510" V 2600 1950 50  0000 C CNN
F 2 "" V 2530 1950 50  0000 C CNN
F 3 "" H 2600 1950 50  0000 C CNN
	1    2600 1950
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5899D2ED
P 2600 2350
F 0 "R5" V 2680 2350 50  0000 C CNN
F 1 "1k" V 2600 2350 50  0000 C CNN
F 2 "" V 2530 2350 50  0000 C CNN
F 3 "" H 2600 2350 50  0000 C CNN
	1    2600 2350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5899D2F3
P 2300 1950
F 0 "C2" H 2325 2050 50  0000 L CNN
F 1 "100n" H 2325 1850 50  0000 L CNN
F 2 "" H 2338 1800 50  0000 C CNN
F 3 "" H 2300 1950 50  0000 C CNN
	1    2300 1950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 5899D301
P 2250 2350
F 0 "P3" H 2250 2500 50  0000 C CNN
F 1 "OUT2" H 2250 2200 50  0000 C CNN
F 2 "" H 2250 2350 50  0000 C CNN
F 3 "" H 2250 2350 50  0000 C CNN
	1    2250 2350
	-1   0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 5899D3CC
P 3200 1950
F 0 "R6" V 3280 1950 50  0000 C CNN
F 1 "510" V 3200 1950 50  0000 C CNN
F 2 "" V 3130 1950 50  0000 C CNN
F 3 "" H 3200 1950 50  0000 C CNN
	1    3200 1950
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 5899D3D2
P 3200 2350
F 0 "R7" V 3280 2350 50  0000 C CNN
F 1 "1k" V 3200 2350 50  0000 C CNN
F 2 "" V 3130 2350 50  0000 C CNN
F 3 "" H 3200 2350 50  0000 C CNN
	1    3200 2350
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5899D3D8
P 2900 1950
F 0 "C3" H 2925 2050 50  0000 L CNN
F 1 "100n" H 2925 1850 50  0000 L CNN
F 2 "" H 2938 1800 50  0000 C CNN
F 3 "" H 2900 1950 50  0000 C CNN
	1    2900 1950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P4
U 1 1 5899D3E4
P 2850 2350
F 0 "P4" H 2850 2500 50  0000 C CNN
F 1 "OUT3" H 2850 2200 50  0000 C CNN
F 2 "" H 2850 2350 50  0000 C CNN
F 3 "" H 2850 2350 50  0000 C CNN
	1    2850 2350
	-1   0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 5899D51F
P 3800 1950
F 0 "R8" V 3880 1950 50  0000 C CNN
F 1 "510" V 3800 1950 50  0000 C CNN
F 2 "" V 3730 1950 50  0000 C CNN
F 3 "" H 3800 1950 50  0000 C CNN
	1    3800 1950
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 5899D525
P 3800 2350
F 0 "R9" V 3880 2350 50  0000 C CNN
F 1 "1k" V 3800 2350 50  0000 C CNN
F 2 "" V 3730 2350 50  0000 C CNN
F 3 "" H 3800 2350 50  0000 C CNN
	1    3800 2350
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5899D52B
P 3500 1950
F 0 "C4" H 3525 2050 50  0000 L CNN
F 1 "100n" H 3525 1850 50  0000 L CNN
F 2 "" H 3538 1800 50  0000 C CNN
F 3 "" H 3500 1950 50  0000 C CNN
	1    3500 1950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P5
U 1 1 5899D53A
P 3450 2350
F 0 "P5" H 3450 2500 50  0000 C CNN
F 1 "OUT4" H 3450 2200 50  0000 C CNN
F 2 "" H 3450 2350 50  0000 C CNN
F 3 "" H 3450 2350 50  0000 C CNN
	1    3450 2350
	-1   0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 5899D623
P 4400 1950
F 0 "R10" V 4480 1950 50  0000 C CNN
F 1 "510" V 4400 1950 50  0000 C CNN
F 2 "" V 4330 1950 50  0000 C CNN
F 3 "" H 4400 1950 50  0000 C CNN
	1    4400 1950
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 5899D629
P 4400 2350
F 0 "R11" V 4480 2350 50  0000 C CNN
F 1 "1k" V 4400 2350 50  0000 C CNN
F 2 "" V 4330 2350 50  0000 C CNN
F 3 "" H 4400 2350 50  0000 C CNN
	1    4400 2350
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5899D62F
P 4100 1950
F 0 "C5" H 4125 2050 50  0000 L CNN
F 1 "100n" H 4125 1850 50  0000 L CNN
F 2 "" H 4138 1800 50  0000 C CNN
F 3 "" H 4100 1950 50  0000 C CNN
	1    4100 1950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P6
U 1 1 5899D63D
P 4050 2350
F 0 "P6" H 4050 2500 50  0000 C CNN
F 1 "OUT5" H 4050 2200 50  0000 C CNN
F 2 "" H 4050 2350 50  0000 C CNN
F 3 "" H 4050 2350 50  0000 C CNN
	1    4050 2350
	-1   0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 5899D728
P 5000 1950
F 0 "R12" V 5080 1950 50  0000 C CNN
F 1 "510" V 5000 1950 50  0000 C CNN
F 2 "" V 4930 1950 50  0000 C CNN
F 3 "" H 5000 1950 50  0000 C CNN
	1    5000 1950
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 5899D72E
P 5000 2350
F 0 "R13" V 5080 2350 50  0000 C CNN
F 1 "1k" V 5000 2350 50  0000 C CNN
F 2 "" V 4930 2350 50  0000 C CNN
F 3 "" H 5000 2350 50  0000 C CNN
	1    5000 2350
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 5899D734
P 4700 1950
F 0 "C6" H 4725 2050 50  0000 L CNN
F 1 "100n" H 4725 1850 50  0000 L CNN
F 2 "" H 4738 1800 50  0000 C CNN
F 3 "" H 4700 1950 50  0000 C CNN
	1    4700 1950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P7
U 1 1 5899D743
P 4650 2350
F 0 "P7" H 4650 2500 50  0000 C CNN
F 1 "OUT6" H 4650 2200 50  0000 C CNN
F 2 "" H 4650 2350 50  0000 C CNN
F 3 "" H 4650 2350 50  0000 C CNN
	1    4650 2350
	-1   0    0    -1  
$EndComp
$Comp
L L L1
U 1 1 5899E3A5
P 5400 900
F 0 "L1" V 5350 900 50  0000 C CNN
F 1 "20uH" V 5475 900 50  0000 C CNN
F 2 "" H 5400 900 50  0000 C CNN
F 3 "" H 5400 900 50  0000 C CNN
	1    5400 900 
	0    -1   -1   0   
$EndComp
$Comp
L C C7
U 1 1 5899E476
P 5150 1650
F 0 "C7" H 5175 1750 50  0000 L CNN
F 1 "100n" H 5175 1550 50  0000 L CNN
F 2 "" H 5188 1500 50  0000 C CNN
F 3 "" H 5150 1650 50  0000 C CNN
	1    5150 1650
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5899E4F3
P 5600 1650
F 0 "C8" H 5625 1750 50  0000 L CNN
F 1 "100n" H 5625 1550 50  0000 L CNN
F 2 "" H 5638 1500 50  0000 C CNN
F 3 "" H 5600 1650 50  0000 C CNN
	1    5600 1650
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5899E65D
P 6000 1650
F 0 "C9" H 6025 1750 50  0000 L CNN
F 1 "100n" H 6025 1550 50  0000 L CNN
F 2 "" H 6038 1500 50  0000 C CNN
F 3 "" H 6000 1650 50  0000 C CNN
	1    6000 1650
	1    0    0    -1  
$EndComp
$Comp
L R R14
U 1 1 5899E6C4
P 5800 900
F 0 "R14" V 5880 900 50  0000 C CNN
F 1 "9.1" V 5800 900 50  0000 C CNN
F 2 "" V 5730 900 50  0000 C CNN
F 3 "" H 5800 900 50  0000 C CNN
	1    5800 900 
	0    1    1    0   
$EndComp
$Comp
L CONN_01X02 P8
U 1 1 5899E837
P 6500 950
F 0 "P8" H 6500 1100 50  0000 C CNN
F 1 "12V" V 6600 950 50  0000 C CNN
F 2 "" H 6500 950 50  0000 C CNN
F 3 "" H 6500 950 50  0000 C CNN
	1    6500 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1800 1150 1800
Wire Wire Line
	1150 1800 1150 2550
Wire Wire Line
	1150 2550 6250 2550
Wire Wire Line
	1250 2550 1250 2300
Wire Wire Line
	1100 1700 4500 1700
Wire Wire Line
	1250 1700 1250 2000
Wire Wire Line
	4500 1700 4500 1300
Wire Wire Line
	4500 1300 4550 1300
Connection ~ 1250 1700
Wire Wire Line
	3900 1700 3900 1300
Wire Wire Line
	3900 1300 3950 1300
Connection ~ 3900 1700
Wire Wire Line
	3300 1700 3300 1300
Wire Wire Line
	3300 1300 3350 1300
Connection ~ 3300 1700
Wire Wire Line
	2700 1700 2700 1300
Wire Wire Line
	2700 1300 2750 1300
Connection ~ 2700 1700
Wire Wire Line
	2100 1700 2100 1300
Wire Wire Line
	2100 1300 2150 1300
Connection ~ 2100 1700
Wire Wire Line
	1500 1700 1500 1300
Wire Wire Line
	1500 1300 1550 1300
Connection ~ 1500 1700
Wire Wire Line
	2000 2550 2000 2500
Connection ~ 1250 2550
Wire Wire Line
	1700 2100 1700 2150
Wire Wire Line
	1700 2150 2000 2150
Wire Wire Line
	2000 2100 2000 2200
Connection ~ 2000 2150
Wire Wire Line
	1700 1800 1700 1750
Wire Wire Line
	1700 1750 2000 1750
Wire Wire Line
	2000 1650 2000 1800
Connection ~ 2000 1750
Wire Wire Line
	1850 2300 1900 2300
Wire Wire Line
	1900 2300 1900 2150
Connection ~ 1900 2150
Wire Wire Line
	1850 2400 1900 2400
Wire Wire Line
	1900 2400 1900 2550
Connection ~ 1900 2550
Wire Wire Line
	2300 2100 2300 2150
Wire Wire Line
	2300 2150 2600 2150
Wire Wire Line
	2600 2100 2600 2200
Connection ~ 2600 2150
Wire Wire Line
	2300 1800 2300 1750
Wire Wire Line
	2300 1750 2600 1750
Wire Wire Line
	2600 1650 2600 1800
Connection ~ 2600 1750
Wire Wire Line
	2450 2300 2500 2300
Wire Wire Line
	2500 2300 2500 2150
Connection ~ 2500 2150
Wire Wire Line
	2450 2400 2500 2400
Wire Wire Line
	2500 2400 2500 2550
Wire Wire Line
	2900 2100 2900 2150
Wire Wire Line
	2900 2150 3200 2150
Wire Wire Line
	3200 2100 3200 2200
Connection ~ 3200 2150
Wire Wire Line
	2900 1800 2900 1750
Wire Wire Line
	3200 1650 3200 1800
Wire Wire Line
	3050 2300 3100 2300
Wire Wire Line
	3100 2300 3100 2150
Connection ~ 3100 2150
Wire Wire Line
	3050 2400 3100 2400
Wire Wire Line
	3100 2400 3100 2550
Wire Wire Line
	3800 2550 3800 2500
Wire Wire Line
	3500 2100 3500 2150
Wire Wire Line
	3500 2150 3800 2150
Wire Wire Line
	3800 2100 3800 2200
Connection ~ 3800 2150
Wire Wire Line
	3500 1800 3500 1750
Wire Wire Line
	3500 1750 3800 1750
Wire Wire Line
	3800 1650 3800 1800
Connection ~ 3800 1750
Wire Wire Line
	3650 2300 3700 2300
Wire Wire Line
	3700 2300 3700 2150
Connection ~ 3700 2150
Wire Wire Line
	3650 2400 3700 2400
Wire Wire Line
	3700 2400 3700 2550
Wire Wire Line
	4100 2100 4100 2150
Wire Wire Line
	4100 2150 4400 2150
Wire Wire Line
	4400 2100 4400 2200
Connection ~ 4400 2150
Wire Wire Line
	4100 1800 4100 1750
Wire Wire Line
	4100 1750 4400 1750
Wire Wire Line
	4400 1650 4400 1800
Connection ~ 4400 1750
Wire Wire Line
	4250 2300 4300 2300
Wire Wire Line
	4300 2300 4300 2150
Connection ~ 4300 2150
Wire Wire Line
	4250 2400 4300 2400
Wire Wire Line
	4300 2400 4300 2550
Wire Wire Line
	5000 2550 5000 2500
Wire Wire Line
	4700 2100 4700 2150
Wire Wire Line
	4700 2150 5000 2150
Wire Wire Line
	5000 2100 5000 2200
Connection ~ 5000 2150
Wire Wire Line
	4700 1800 4700 1750
Wire Wire Line
	4700 1750 5000 1750
Wire Wire Line
	5000 1650 5000 1800
Connection ~ 5000 1750
Wire Wire Line
	4850 2300 4900 2300
Wire Wire Line
	4900 2300 4900 2150
Connection ~ 4900 2150
Wire Wire Line
	4850 2400 4900 2400
Wire Wire Line
	4900 2400 4900 2550
Connection ~ 2000 2550
Connection ~ 2500 2550
Connection ~ 3100 2550
Connection ~ 3700 2550
Connection ~ 3800 2550
Connection ~ 4300 2550
Connection ~ 4900 2550
Wire Wire Line
	2600 2500 2600 2550
Connection ~ 2600 2550
Wire Wire Line
	3200 2500 3200 2550
Connection ~ 3200 2550
Wire Wire Line
	4400 2500 4400 2550
Connection ~ 4400 2550
Wire Wire Line
	2000 950  2000 900 
Wire Wire Line
	2000 900  5250 900 
Wire Wire Line
	2600 950  2600 900 
Connection ~ 2600 900 
Wire Wire Line
	3200 950  3200 900 
Connection ~ 3200 900 
Wire Wire Line
	3800 950  3800 900 
Connection ~ 3800 900 
Wire Wire Line
	4400 950  4400 900 
Connection ~ 4400 900 
Wire Wire Line
	5000 950  5000 900 
Connection ~ 5000 900 
Wire Wire Line
	5150 1500 5150 900 
Connection ~ 5150 900 
Wire Wire Line
	5150 2550 5150 1800
Connection ~ 5000 2550
Wire Wire Line
	5550 900  5650 900 
Wire Wire Line
	5600 900  5600 1500
Connection ~ 5600 900 
Wire Wire Line
	5600 2550 5600 1800
Connection ~ 5150 2550
Wire Wire Line
	6300 1000 6250 1000
Wire Wire Line
	6250 1000 6250 2550
Connection ~ 5600 2550
Wire Wire Line
	6000 1800 6000 2550
Connection ~ 6000 2550
Wire Wire Line
	6000 1500 6000 900 
Wire Wire Line
	5950 900  6300 900 
Connection ~ 6000 900 
Wire Wire Line
	2900 1750 3200 1750
Connection ~ 3200 1750
Text Label 6250 900  0    60   ~ 0
+
Text Label 6250 1000 0    60   ~ 0
-
$EndSCHEMATC
