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
L LTRIM L1
U 1 1 58A9E89B
P 1750 1500
F 0 "L1" V 1675 1500 50  0000 C CNN
F 1 "9uH" V 1875 1500 50  0000 C CNN
F 2 "" H 1750 1500 50  0000 C CNN
F 3 "" H 1750 1500 50  0000 C CNN
	1    1750 1500
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 58A9E8EA
P 2050 1500
F 0 "C1" H 2075 1600 50  0000 L CNN
F 1 "120p" H 2075 1400 50  0000 L CNN
F 2 "" H 2088 1350 50  0000 C CNN
F 3 "" H 2050 1500 50  0000 C CNN
	1    2050 1500
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 58A9E920
P 2050 1900
F 0 "C2" H 2075 2000 50  0000 L CNN
F 1 "100n" H 2075 1800 50  0000 L CNN
F 2 "" H 2088 1750 50  0000 C CNN
F 3 "" H 2050 1900 50  0000 C CNN
	1    2050 1900
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 58A9E94A
P 2450 1500
F 0 "R2" V 2530 1500 50  0000 C CNN
F 1 "100" V 2450 1500 50  0000 C CNN
F 2 "" V 2380 1500 50  0000 C CNN
F 3 "" H 2450 1500 50  0000 C CNN
	1    2450 1500
	1    0    0    -1  
$EndComp
$Comp
L BS170 Q1
U 1 1 58A9E9B1
P 2350 2100
F 0 "Q1" H 2550 2175 50  0000 L CNN
F 1 "BF999" H 2550 2100 50  0000 L CNN
F 2 "TO-92" H 2550 2025 50  0001 L CIN
F 3 "" H 2350 2100 50  0000 L CNN
	1    2350 2100
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 58A9EA16
P 2650 1750
F 0 "C3" H 2675 1850 50  0000 L CNN
F 1 "100n" H 2675 1650 50  0000 L CNN
F 2 "" H 2688 1600 50  0000 C CNN
F 3 "" H 2650 1750 50  0000 C CNN
	1    2650 1750
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 58A9EA79
P 2450 2550
F 0 "R3" V 2530 2550 50  0000 C CNN
F 1 "120" V 2450 2550 50  0000 C CNN
F 2 "" V 2380 2550 50  0000 C CNN
F 3 "" H 2450 2550 50  0000 C CNN
	1    2450 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1350 1750 1300
Wire Wire Line
	1550 1300 2450 1300
Wire Wire Line
	2050 1300 2050 1350
Wire Wire Line
	2450 1300 2450 1350
Connection ~ 2050 1300
Wire Wire Line
	1750 1650 1750 1700
Wire Wire Line
	1600 1700 2050 1700
Wire Wire Line
	2050 1650 2050 1750
Connection ~ 2050 1700
Wire Wire Line
	2450 1650 2450 1900
Wire Wire Line
	2500 1750 2450 1750
Connection ~ 2450 1750
Wire Wire Line
	2050 2050 2050 2400
Wire Wire Line
	2050 2150 2150 2150
Wire Wire Line
	2450 2300 2450 2400
$Comp
L R R1
U 1 1 58A9EB3D
P 2050 2550
F 0 "R1" V 2130 2550 50  0000 C CNN
F 1 "100k" V 2050 2550 50  0000 C CNN
F 2 "" V 1980 2550 50  0000 C CNN
F 3 "" H 2050 2550 50  0000 C CNN
	1    2050 2550
	1    0    0    -1  
$EndComp
Connection ~ 2050 2150
Wire Wire Line
	2050 2700 2050 2800
Wire Wire Line
	2050 2750 6150 2750
Wire Wire Line
	2450 2750 2450 2700
$Comp
L CONN_01X02 P1
U 1 1 58A9EBBE
P 1350 1350
F 0 "P1" H 1350 1500 50  0000 C CNN
F 1 "IN" V 1450 1350 50  0000 C CNN
F 2 "" H 1350 1350 50  0000 C CNN
F 3 "" H 1350 1350 50  0000 C CNN
	1    1350 1350
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 58A9EC6F
P 2050 2800
F 0 "#PWR1" H 2050 2550 50  0001 C CNN
F 1 "GND" H 2050 2650 50  0000 C CNN
F 2 "" H 2050 2800 50  0000 C CNN
F 3 "" H 2050 2800 50  0000 C CNN
	1    2050 2800
	1    0    0    -1  
$EndComp
Connection ~ 2050 2750
Wire Wire Line
	1600 1400 1600 1700
Wire Wire Line
	1600 1400 1550 1400
Connection ~ 1750 1300
Connection ~ 1750 1700
Wire Wire Line
	2800 1750 2950 1750
Wire Wire Line
	2950 1750 2950 2750
Connection ~ 2450 2750
$Comp
L C C4
U 1 1 58A9EE06
P 2750 2350
F 0 "C4" H 2775 2450 50  0000 L CNN
F 1 "100n" H 2775 2250 50  0000 L CNN
F 2 "" H 2788 2200 50  0000 C CNN
F 3 "" H 2750 2350 50  0000 C CNN
	1    2750 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 2350 2450 2350
Connection ~ 2450 2350
$Comp
L Crystal Y1
U 1 1 58A9EF23
P 3350 2350
F 0 "Y1" H 3350 2500 50  0000 C CNN
F 1 "5.0 MHz" H 3350 2200 50  0000 C CNN
F 2 "" H 3350 2350 50  0000 C CNN
F 3 "" H 3350 2350 50  0000 C CNN
	1    3350 2350
	1    0    0    -1  
$EndComp
$Comp
L Crystal Y2
U 1 1 58A9EF64
P 3900 2350
F 0 "Y2" H 3900 2500 50  0000 C CNN
F 1 "5.0 MHz" H 3900 2200 50  0000 C CNN
F 2 "" H 3900 2350 50  0000 C CNN
F 3 "" H 3900 2350 50  0000 C CNN
	1    3900 2350
	1    0    0    -1  
$EndComp
$Comp
L Crystal Y3
U 1 1 58A9EF93
P 4450 2350
F 0 "Y3" H 4450 2500 50  0000 C CNN
F 1 "5.0 MHz" H 4450 2200 50  0000 C CNN
F 2 "" H 4450 2350 50  0000 C CNN
F 3 "" H 4450 2350 50  0000 C CNN
	1    4450 2350
	1    0    0    -1  
$EndComp
$Comp
L Crystal Y4
U 1 1 58A9EFC8
P 5000 2350
F 0 "Y4" H 5000 2500 50  0000 C CNN
F 1 "5.0 MHz" H 5000 2200 50  0000 C CNN
F 2 "" H 5000 2350 50  0000 C CNN
F 3 "" H 5000 2350 50  0000 C CNN
	1    5000 2350
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 58A9F0A7
P 3050 2550
F 0 "C5" H 3075 2650 50  0000 L CNN
F 1 "200p" H 3075 2450 50  0000 L CNN
F 2 "" H 3088 2400 50  0000 C CNN
F 3 "" H 3050 2550 50  0000 C CNN
	1    3050 2550
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 58A9F0F9
P 3600 2550
F 0 "C6" H 3625 2650 50  0000 L CNN
F 1 "360p" H 3625 2450 50  0000 L CNN
F 2 "" H 3638 2400 50  0000 C CNN
F 3 "" H 3600 2550 50  0000 C CNN
	1    3600 2550
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 58A9F14A
P 4150 2550
F 0 "C7" H 4175 2650 50  0000 L CNN
F 1 "430p" H 4175 2450 50  0000 L CNN
F 2 "" H 4188 2400 50  0000 C CNN
F 3 "" H 4150 2550 50  0000 C CNN
	1    4150 2550
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 58A9F1A0
P 4700 2550
F 0 "C9" H 4725 2650 50  0000 L CNN
F 1 "360p" H 4725 2450 50  0000 L CNN
F 2 "" H 4738 2400 50  0000 C CNN
F 3 "" H 4700 2550 50  0000 C CNN
	1    4700 2550
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 58A9F1EF
P 5250 2550
F 0 "C11" H 5275 2650 50  0000 L CNN
F 1 "200p" H 5275 2450 50  0000 L CNN
F 2 "" H 5288 2400 50  0000 C CNN
F 3 "" H 5250 2550 50  0000 C CNN
	1    5250 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 2750 5250 2700
Connection ~ 2950 2750
Wire Wire Line
	4700 2700 4700 2750
Connection ~ 4700 2750
Wire Wire Line
	4150 2700 4150 2750
Connection ~ 4150 2750
Wire Wire Line
	3600 2700 3600 2750
Connection ~ 3600 2750
Wire Wire Line
	3050 2700 3050 2750
Connection ~ 3050 2750
Wire Wire Line
	2900 2350 3200 2350
Wire Wire Line
	3050 2350 3050 2400
Connection ~ 3050 2350
Wire Wire Line
	3500 2350 3750 2350
Wire Wire Line
	3600 2400 3600 2350
Connection ~ 3600 2350
Wire Wire Line
	4050 2350 4300 2350
Wire Wire Line
	4150 2400 4150 2350
Connection ~ 4150 2350
Wire Wire Line
	4600 2350 4850 2350
Wire Wire Line
	4700 2400 4700 2350
Connection ~ 4700 2350
Wire Wire Line
	5250 2300 5250 2400
Wire Wire Line
	5250 2350 5150 2350
$Comp
L Q_PNP_EBC Q2
U 1 1 58A9F80F
P 5500 1700
F 0 "Q2" H 5700 1750 50  0000 L CNN
F 1 "2n3906" H 5700 1650 50  0000 L CNN
F 2 "" H 5700 1800 50  0000 C CNN
F 3 "" H 5500 1700 50  0000 C CNN
	1    5500 1700
	1    0    0    1   
$EndComp
$Comp
L LTRIM L2
U 1 1 58A9F8BC
P 5950 2550
F 0 "L2" V 5875 2550 50  0000 C CNN
F 1 "9uH" V 6075 2550 50  0000 C CNN
F 2 "" H 5950 2550 50  0000 C CNN
F 3 "" H 5950 2550 50  0000 C CNN
	1    5950 2550
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 58A9F909
P 5600 2550
F 0 "C12" H 5625 2650 50  0000 L CNN
F 1 "120p" H 5625 2450 50  0000 L CNN
F 2 "" H 5638 2400 50  0000 C CNN
F 3 "" H 5600 2550 50  0000 C CNN
	1    5600 2550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 P2
U 1 1 58A9FA0E
P 4600 1300
F 0 "P2" H 4600 1400 50  0000 C CNN
F 1 "VCC 9v" V 4700 1300 50  0000 C CNN
F 2 "" H 4600 1300 50  0000 C CNN
F 3 "" H 4600 1300 50  0000 C CNN
	1    4600 1300
	-1   0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 58A9FAD5
P 5050 1300
F 0 "R7" V 5130 1300 50  0000 C CNN
F 1 "120" V 5050 1300 50  0000 C CNN
F 2 "" V 4980 1300 50  0000 C CNN
F 3 "" H 5050 1300 50  0000 C CNN
	1    5050 1300
	0    1    1    0   
$EndComp
$Comp
L C C10
U 1 1 58A9FC15
P 5250 2150
F 0 "C10" H 5275 2250 50  0000 L CNN
F 1 "100n" H 5275 2050 50  0000 L CNN
F 2 "" H 5288 2000 50  0000 C CNN
F 3 "" H 5250 2150 50  0000 C CNN
	1    5250 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1300 4900 1300
Wire Wire Line
	5200 1300 5600 1300
Wire Wire Line
	5250 1300 5250 2000
Connection ~ 5250 2350
$Comp
L R R5
U 1 1 58A9FDDC
P 4850 1500
F 0 "R5" V 4930 1500 50  0000 C CNN
F 1 "1.5k" V 4850 1500 50  0000 C CNN
F 2 "" V 4780 1500 50  0000 C CNN
F 3 "" H 4850 1500 50  0000 C CNN
	1    4850 1500
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 58A9FE2F
P 4850 1900
F 0 "R6" V 4930 1900 50  0000 C CNN
F 1 "7.5k" V 4850 1900 50  0000 C CNN
F 2 "" V 4780 1900 50  0000 C CNN
F 3 "" H 4850 1900 50  0000 C CNN
	1    4850 1900
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 58A9FE7C
P 4550 1900
F 0 "C8" H 4575 2000 50  0000 L CNN
F 1 "100n" H 4575 1800 50  0000 L CNN
F 2 "" H 4588 1750 50  0000 C CNN
F 3 "" H 4550 1900 50  0000 C CNN
	1    4550 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1300 5600 1500
Connection ~ 5250 1300
Wire Wire Line
	4550 1750 4550 1700
Wire Wire Line
	4550 1700 5300 1700
Wire Wire Line
	4850 1650 4850 1750
Connection ~ 4850 1700
$Comp
L GND #PWR2
U 1 1 58AA0320
P 4700 2150
F 0 "#PWR2" H 4700 1900 50  0001 C CNN
F 1 "GND" H 4850 2100 50  0000 C CNN
F 2 "" H 4700 2150 50  0000 C CNN
F 3 "" H 4700 2150 50  0000 C CNN
	1    4700 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2100 4850 2050
Wire Wire Line
	4550 2100 4850 2100
Wire Wire Line
	4700 2100 4700 2150
Wire Wire Line
	4550 2050 4550 2100
Connection ~ 4700 2100
Wire Wire Line
	4850 1350 4850 1300
Connection ~ 4850 1300
Wire Wire Line
	5600 1900 5600 2400
Wire Wire Line
	5600 2750 5600 2700
Connection ~ 5250 2750
Wire Wire Line
	5950 2750 5950 2700
Connection ~ 5600 2750
Wire Wire Line
	5950 2400 5950 2350
Wire Wire Line
	5600 2350 6200 2350
Connection ~ 5600 2350
$Comp
L CONN_01X02 P3
U 1 1 58AA0777
P 6400 2400
F 0 "P3" H 6400 2550 50  0000 C CNN
F 1 "OUT" V 6500 2400 50  0000 C CNN
F 2 "" H 6400 2400 50  0000 C CNN
F 3 "" H 6400 2400 50  0000 C CNN
	1    6400 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2450 6150 2450
Wire Wire Line
	6150 2450 6150 2750
Connection ~ 5950 2750
Connection ~ 5950 2350
$Comp
L R R4
U 1 1 58AA0A6C
P 3300 950
F 0 "R4" V 3380 950 50  0000 C CNN
F 1 "100" V 3300 950 50  0000 C CNN
F 2 "" V 3230 950 50  0000 C CNN
F 3 "" H 3300 950 50  0000 C CNN
	1    3300 950 
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 1150 1350 950 
Wire Wire Line
	1350 950  3150 950 
Wire Wire Line
	4600 1150 4600 950 
Wire Wire Line
	4600 950  3450 950 
Text Notes 3700 2900 0    60   ~ 0
300 Hz filter
$EndSCHEMATC