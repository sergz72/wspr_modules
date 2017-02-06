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
LIBS:ftdi
LIBS:references
LIBS:stmicro
LIBS:wspr_stm32f373-cache
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
L STM32F373CCTx U1
U 1 1 587E2DB4
P 2900 2750
F 0 "U1" H 2000 4400 50  0000 L BNN
F 1 "STM32F373CCTx" H 2550 1350 50  0000 R BNN
F 2 "LQFP48" H 3350 1400 50  0001 R TNN
F 3 "" H 2900 2750 50  0000 C CNN
	1    2900 2750
	1    0    0    -1  
$EndComp
$Comp
L L L1
U 1 1 587E2EEC
P 2750 850
F 0 "L1" V 2700 850 50  0000 C CNN
F 1 "10u" V 2825 850 50  0000 C CNN
F 2 "" H 2750 850 50  0000 C CNN
F 3 "" H 2750 850 50  0000 C CNN
	1    2750 850 
	0    -1   -1   0   
$EndComp
$Comp
L Crystal Y1
U 1 1 587E303E
P 1550 2800
F 0 "Y1" H 1400 2900 50  0000 C CNN
F 1 "12.0" H 1550 2650 50  0000 C CNN
F 2 "" H 1550 2800 50  0000 C CNN
F 3 "" H 1550 2800 50  0000 C CNN
	1    1550 2800
	0    1    1    0   
$EndComp
$Comp
L C C5
U 1 1 587E30DB
P 1200 2600
F 0 "C5" H 1225 2700 50  0000 L CNN
F 1 "22p" H 1225 2500 50  0000 L CNN
F 2 "" H 1238 2450 50  0000 C CNN
F 3 "" H 1200 2600 50  0000 C CNN
	1    1200 2600
	0    1    1    0   
$EndComp
$Comp
L C C6
U 1 1 587E3173
P 1200 3000
F 0 "C6" H 1225 3100 50  0000 L CNN
F 1 "22p" H 1225 2900 50  0000 L CNN
F 2 "" H 1238 2850 50  0000 C CNN
F 3 "" H 1200 3000 50  0000 C CNN
	1    1200 3000
	0    1    1    0   
$EndComp
$Comp
L GND #PWR1
U 1 1 587E31A5
P 2800 4350
F 0 "#PWR1" H 2800 4100 50  0001 C CNN
F 1 "GND" H 2800 4200 50  0000 C CNN
F 2 "" H 2800 4350 50  0000 C CNN
F 3 "" H 2800 4350 50  0000 C CNN
	1    2800 4350
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 587E34A3
P 1200 1250
F 0 "C4" H 1225 1350 50  0000 L CNN
F 1 "100n" H 1225 1150 50  0000 L CNN
F 2 "" H 1238 1100 50  0000 C CNN
F 3 "" H 1200 1250 50  0000 C CNN
	1    1200 1250
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 587E351E
P 1550 1100
F 0 "R2" V 1630 1100 50  0000 C CNN
F 1 "10k" V 1550 1100 50  0000 C CNN
F 2 "" V 1480 1100 50  0000 C CNN
F 3 "" H 1550 1100 50  0000 C CNN
	1    1550 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	1750 1650 1850 1650
Wire Wire Line
	1750 800  1750 950 
Wire Wire Line
	1750 950  1750 1000
Wire Wire Line
	1750 1000 1750 1100
Wire Wire Line
	1750 1100 1750 1650
Wire Wire Line
	1750 950  2600 950 
Wire Wire Line
	2600 950  2700 950 
Wire Wire Line
	2700 950  2800 950 
Wire Wire Line
	2800 950  2800 1050
Wire Wire Line
	2700 1050 2700 950 
Connection ~ 2700 950 
Wire Wire Line
	2600 600  2600 850 
Wire Wire Line
	2600 850  2600 950 
Connection ~ 2600 950 
Wire Wire Line
	2900 850  2900 1050
Wire Wire Line
	3000 850  2900 850 
Wire Wire Line
	1850 2750 1750 2750
Wire Wire Line
	1750 2750 1750 2600
Wire Wire Line
	1750 2600 1550 2600
Wire Wire Line
	1550 2600 1350 2600
Wire Wire Line
	1550 2600 1550 2650
Wire Wire Line
	1850 2850 1750 2850
Wire Wire Line
	1750 2850 1750 3000
Wire Wire Line
	1750 3000 1550 3000
Wire Wire Line
	1550 3000 1350 3000
Wire Wire Line
	1550 3000 1550 2950
Wire Wire Line
	2800 4150 2800 4250
Wire Wire Line
	2800 4250 2800 4350
Wire Wire Line
	1000 4250 1600 4250
Wire Wire Line
	1600 4250 2800 4250
Wire Wire Line
	2800 4250 2900 4250
Wire Wire Line
	2900 4250 3000 4250
Wire Wire Line
	3000 4250 3000 4150
Connection ~ 2800 4250
Wire Wire Line
	2900 4150 2900 4250
Connection ~ 2900 4250
Connection ~ 1550 2600
Connection ~ 1550 3000
Wire Wire Line
	1000 2600 1050 2600
Wire Wire Line
	1000 800  1000 1000
Wire Wire Line
	1000 1000 1000 1250
Wire Wire Line
	1000 1250 1000 1450
Wire Wire Line
	1000 1450 1000 2100
Wire Wire Line
	1000 2100 1000 2500
Wire Wire Line
	1000 2500 1000 2600
Wire Wire Line
	1000 2600 1000 3000
Wire Wire Line
	1000 3000 1000 4250
Wire Wire Line
	1050 3000 1000 3000
Connection ~ 1000 3000
Wire Wire Line
	1850 1450 1000 1450
Connection ~ 1000 2600
Wire Wire Line
	1350 1250 1400 1250
Wire Wire Line
	1400 1250 1800 1250
Wire Wire Line
	1800 1250 1850 1250
Wire Wire Line
	1400 1100 1400 1250
Connection ~ 1400 1250
Wire Wire Line
	1700 1100 1750 1100
Connection ~ 1750 1100
Wire Wire Line
	1050 1250 1000 1250
Connection ~ 1000 1450
Wire Wire Line
	800  1750 1100 1750
Wire Wire Line
	1100 1750 1350 1750
Wire Wire Line
	1350 1750 1550 1750
Wire Wire Line
	1550 1750 1700 1750
Wire Wire Line
	1700 1750 1850 1750
$Comp
L C C1
U 1 1 587E395B
P 1100 1950
F 0 "C1" H 1125 2050 50  0000 L CNN
F 1 "100n" H 1125 1850 50  0000 L CNN
F 2 "" H 1138 1800 50  0000 C CNN
F 3 "" H 1100 1950 50  0000 C CNN
	1    1100 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1800 1100 1750
$Comp
L R R1
U 1 1 587E3D0F
P 800 1550
F 0 "R1" V 880 1550 50  0000 C CNN
F 1 "510" V 800 1550 50  0000 C CNN
F 2 "" V 730 1550 50  0000 C CNN
F 3 "" H 800 1550 50  0000 C CNN
	1    800  1550
	1    0    0    -1  
$EndComp
Connection ~ 1100 1750
Wire Wire Line
	800  700  3000 700 
Connection ~ 3000 850 
$Comp
L LM1117-3.3 U2
U 1 1 587E6EA3
P 5550 850
F 0 "U2" H 5650 600 50  0000 C CNN
F 1 "LM1117-3.3" H 5550 1100 50  0000 C CNN
F 2 "" H 5550 850 50  0000 C CNN
F 3 "" H 5550 850 50  0000 C CNN
	1    5550 850 
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X05 P1
U 1 1 587E7077
P 4550 800
F 0 "P1" H 4550 1100 50  0000 C CNN
F 1 "SWD" V 4650 800 50  0000 C CNN
F 2 "" H 4550 800 50  0000 C CNN
F 3 "" H 4550 800 50  0000 C CNN
	1    4550 800 
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR2
U 1 1 587E7C8A
P 5550 1250
F 0 "#PWR2" H 5550 1000 50  0001 C CNN
F 1 "GND" H 5550 1100 50  0000 C CNN
F 2 "" H 5550 1250 50  0000 C CNN
F 3 "" H 5550 1250 50  0000 C CNN
	1    5550 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 1150 5550 1200
Wire Wire Line
	5550 1200 5550 1250
Connection ~ 5550 1200
$Comp
L CP C15
U 1 1 587E8575
P 5050 1000
F 0 "C15" H 4900 1150 50  0000 L CNN
F 1 "47u" H 4900 900 50  0000 L CNN
F 2 "" H 5088 850 50  0000 C CNN
F 3 "" H 5050 1000 50  0000 C CNN
	1    5050 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 800  5250 850 
Wire Wire Line
	5050 800  5200 800 
Wire Wire Line
	5200 800  5250 800 
Wire Wire Line
	5050 600  5050 800 
Wire Wire Line
	5050 800  5050 850 
Wire Wire Line
	2600 600  4850 600 
Wire Wire Line
	4850 600  5050 600 
Connection ~ 5050 800 
Connection ~ 2600 850 
Wire Wire Line
	4550 1000 4550 1100
Wire Wire Line
	4550 1100 4550 1200
Wire Wire Line
	4750 1000 4750 1050
Wire Wire Line
	4750 1050 4850 1050
Wire Wire Line
	4850 1050 4850 600 
Connection ~ 4850 600 
Wire Wire Line
	3500 2550 4650 2550
Wire Wire Line
	4650 2550 4650 1000
Wire Wire Line
	3500 2450 4450 2450
Wire Wire Line
	4450 2450 4450 1000
Wire Wire Line
	1800 1250 1800 650 
Wire Wire Line
	1800 650  4200 650 
Wire Wire Line
	4200 650  4200 1050
Wire Wire Line
	4200 1050 4350 1050
Wire Wire Line
	4350 1050 4350 1000
Connection ~ 1800 1250
Wire Wire Line
	4750 3750 3500 3750
Wire Wire Line
	4850 3650 3500 3650
$Comp
L C C13
U 1 1 587E9C0E
P 3200 750
F 0 "C13" H 3225 850 50  0000 L CNN
F 1 "100n" H 3225 650 50  0000 L CNN
F 2 "" H 3238 600 50  0000 C CNN
F 3 "" H 3200 750 50  0000 C CNN
	1    3200 750 
	0    1    1    0   
$EndComp
$Comp
L C C14
U 1 1 587E9D3A
P 3200 1000
F 0 "C14" H 3225 1100 50  0000 L CNN
F 1 "100n" V 3300 850 50  0000 L CNN
F 2 "" H 3238 850 50  0000 C CNN
F 3 "" H 3200 1000 50  0000 C CNN
	1    3200 1000
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 1000 3050 1000
Connection ~ 3000 1000
Wire Wire Line
	3050 750  3000 750 
Connection ~ 3000 750 
Wire Wire Line
	3400 1100 4550 1100
Wire Wire Line
	3400 750  3400 1000
Wire Wire Line
	3400 1000 3400 1100
Wire Wire Line
	3400 750  3350 750 
Connection ~ 4550 1100
Wire Wire Line
	3350 1000 3400 1000
Connection ~ 3400 1000
$Comp
L C C2
U 1 1 587EA610
P 1200 800
F 0 "C2" H 1225 900 50  0000 L CNN
F 1 "100n" V 1150 550 50  0000 L CNN
F 2 "" H 1238 650 50  0000 C CNN
F 3 "" H 1200 800 50  0000 C CNN
	1    1200 800 
	0    1    1    0   
$EndComp
$Comp
L C C3
U 1 1 587EA6A9
P 1200 1000
F 0 "C3" H 1225 1100 50  0000 L CNN
F 1 "100n" H 1225 900 50  0000 L CNN
F 2 "" H 1238 850 50  0000 C CNN
F 3 "" H 1200 1000 50  0000 C CNN
	1    1200 1000
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 1000 1750 1000
Connection ~ 1750 1000
Wire Wire Line
	1350 800  1750 800 
Connection ~ 1750 950 
Wire Wire Line
	1050 800  1000 800 
Connection ~ 1000 1250
Wire Wire Line
	1050 1000 1000 1000
Connection ~ 1000 1000
$Comp
L JACK_TRS_6PINS J1
U 1 1 587EB303
P 1100 5000
F 0 "J1" H 1100 5400 50  0000 C CNN
F 1 "JACK_TRS_6PINS" H 1050 4700 50  0001 C CNN
F 2 "" H 1200 4850 50  0000 C CNN
F 3 "" H 1200 4850 50  0000 C CNN
	1    1100 5000
	1    0    0    -1  
$EndComp
$Comp
L JACK_TRS_6PINS J2
U 1 1 587EB4CF
P 1100 5850
F 0 "J2" H 1100 6250 50  0000 C CNN
F 1 "JACK_TRS_6PINS" H 1050 5550 50  0001 C CNN
F 2 "" H 1200 5700 50  0000 C CNN
F 3 "" H 1200 5700 50  0000 C CNN
	1    1100 5850
	1    0    0    -1  
$EndComp
$Comp
L JACK_TRS_6PINS J3
U 1 1 587EB52E
P 1100 6700
F 0 "J3" H 1100 7100 50  0000 C CNN
F 1 "JACK_TRS_6PINS" H 1050 6400 50  0001 C CNN
F 2 "" H 1200 6550 50  0000 C CNN
F 3 "" H 1200 6550 50  0000 C CNN
	1    1100 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 6500 1500 6500
Wire Wire Line
	1600 4250 1600 4500
Wire Wire Line
	1600 4500 1600 4750
Wire Wire Line
	1600 4750 1600 4800
Wire Wire Line
	1600 4800 1600 5350
Wire Wire Line
	1600 5350 1600 5600
Wire Wire Line
	1600 5600 1600 5650
Wire Wire Line
	1600 5650 1600 6200
Wire Wire Line
	1600 6200 1600 6450
Wire Wire Line
	1600 6450 1600 6500
Connection ~ 1600 4250
Wire Wire Line
	1500 4800 1600 4800
Connection ~ 1600 4800
Wire Wire Line
	1500 5650 1600 5650
Connection ~ 1600 5650
$Comp
L C C8
U 1 1 587EBE1E
P 1850 5000
F 0 "C8" H 1875 5100 50  0000 L CNN
F 1 "1u" H 1875 4900 50  0000 L CNN
F 2 "" H 1888 4850 50  0000 C CNN
F 3 "" H 1850 5000 50  0000 C CNN
	1    1850 5000
	0    1    1    0   
$EndComp
$Comp
L C C10
U 1 1 587EC175
P 1850 5850
F 0 "C10" H 1875 5950 50  0000 L CNN
F 1 "1u" H 1875 5750 50  0000 L CNN
F 2 "" H 1888 5700 50  0000 C CNN
F 3 "" H 1850 5850 50  0000 C CNN
	1    1850 5850
	0    1    1    0   
$EndComp
$Comp
L C C12
U 1 1 587EC2BA
P 1850 6700
F 0 "C12" H 1875 6800 50  0000 L CNN
F 1 "1u" H 1875 6600 50  0000 L CNN
F 2 "" H 1888 6550 50  0000 C CNN
F 3 "" H 1850 6700 50  0000 C CNN
	1    1850 6700
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 5000 1700 5000
Wire Wire Line
	1500 5850 1700 5850
Wire Wire Line
	1500 6700 1700 6700
$Comp
L R R5
U 1 1 587EC605
P 1850 4750
F 0 "R5" V 1930 4750 50  0000 C CNN
F 1 "10k" V 1850 4750 50  0000 C CNN
F 2 "" V 1780 4750 50  0000 C CNN
F 3 "" H 1850 4750 50  0000 C CNN
	1    1850 4750
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 587EC7E4
P 1850 5600
F 0 "R6" V 1930 5600 50  0000 C CNN
F 1 "10k" V 1850 5600 50  0000 C CNN
F 2 "" V 1780 5600 50  0000 C CNN
F 3 "" H 1850 5600 50  0000 C CNN
	1    1850 5600
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 587EC894
P 1850 6450
F 0 "R7" V 1930 6450 50  0000 C CNN
F 1 "10k" V 1850 6450 50  0000 C CNN
F 2 "" V 1780 6450 50  0000 C CNN
F 3 "" H 1850 6450 50  0000 C CNN
	1    1850 6450
	0    1    1    0   
$EndComp
$Comp
L C C7
U 1 1 587ECA78
P 1850 4500
F 0 "C7" H 1875 4600 50  0000 L CNN
F 1 "10n" H 1875 4400 50  0000 L CNN
F 2 "" H 1888 4350 50  0000 C CNN
F 3 "" H 1850 4500 50  0000 C CNN
	1    1850 4500
	0    1    1    0   
$EndComp
$Comp
L C C9
U 1 1 587ECB87
P 1850 5350
F 0 "C9" H 1875 5450 50  0000 L CNN
F 1 "10n" H 1875 5250 50  0000 L CNN
F 2 "" H 1888 5200 50  0000 C CNN
F 3 "" H 1850 5350 50  0000 C CNN
	1    1850 5350
	0    1    1    0   
$EndComp
$Comp
L C C11
U 1 1 587ECC40
P 1850 6200
F 0 "C11" H 1875 6300 50  0000 L CNN
F 1 "10n" H 1875 6100 50  0000 L CNN
F 2 "" H 1888 6050 50  0000 C CNN
F 3 "" H 1850 6200 50  0000 C CNN
	1    1850 6200
	0    1    1    0   
$EndComp
Wire Wire Line
	1700 4500 1600 4500
Connection ~ 1600 4500
Wire Wire Line
	1700 4750 1600 4750
Connection ~ 1600 4750
Wire Wire Line
	2000 4500 2100 4500
Wire Wire Line
	2100 4350 2100 4500
Wire Wire Line
	2100 4500 2100 4750
Wire Wire Line
	2100 4750 2100 5000
Wire Wire Line
	2000 5000 2100 5000
Wire Wire Line
	2100 5000 2200 5000
Wire Wire Line
	2000 4750 2100 4750
Connection ~ 2100 4750
Wire Wire Line
	2000 5350 2100 5350
Wire Wire Line
	2100 5350 3600 5350
Wire Wire Line
	2100 5350 2100 5600
Wire Wire Line
	2100 5600 2100 5850
Wire Wire Line
	2000 5850 2100 5850
Wire Wire Line
	2100 5850 2200 5850
Wire Wire Line
	2000 5600 2100 5600
Connection ~ 2100 5600
Wire Wire Line
	1700 5350 1600 5350
Connection ~ 1600 5350
Wire Wire Line
	1700 5600 1600 5600
Connection ~ 1600 5600
Wire Wire Line
	1700 6450 1600 6450
Connection ~ 1600 6450
Wire Wire Line
	1700 6200 1600 6200
Connection ~ 1600 6200
Wire Wire Line
	2000 6200 2100 6200
Wire Wire Line
	2100 6200 3700 6200
Wire Wire Line
	2100 6200 2100 6450
Wire Wire Line
	2100 6450 2100 6700
Wire Wire Line
	2000 6700 2100 6700
Wire Wire Line
	2100 6700 2200 6700
Wire Wire Line
	2000 6450 2100 6450
Connection ~ 2100 6450
Wire Wire Line
	1850 3550 1750 3550
Wire Wire Line
	1750 3550 1750 4350
Wire Wire Line
	1750 4350 2100 4350
Connection ~ 2100 4500
Wire Wire Line
	3500 3050 3600 3050
Wire Wire Line
	3600 3050 3600 5350
Connection ~ 2100 5350
Wire Wire Line
	3500 2850 3700 2850
Wire Wire Line
	3700 2850 3700 6200
Connection ~ 2100 6200
$Comp
L R R8
U 1 1 587EFB14
P 2350 5000
F 0 "R8" V 2430 5000 50  0000 C CNN
F 1 "10k" V 2350 5000 50  0000 C CNN
F 2 "" V 2280 5000 50  0000 C CNN
F 3 "" H 2350 5000 50  0000 C CNN
	1    2350 5000
	0    1    1    0   
$EndComp
$Comp
L R R9
U 1 1 587EFBD9
P 2350 5850
F 0 "R9" V 2430 5850 50  0000 C CNN
F 1 "10k" V 2350 5850 50  0000 C CNN
F 2 "" V 2280 5850 50  0000 C CNN
F 3 "" H 2350 5850 50  0000 C CNN
	1    2350 5850
	0    1    1    0   
$EndComp
$Comp
L R R10
U 1 1 587EFCA1
P 2350 6700
F 0 "R10" V 2430 6700 50  0000 C CNN
F 1 "10k" V 2350 6700 50  0000 C CNN
F 2 "" V 2280 6700 50  0000 C CNN
F 3 "" H 2350 6700 50  0000 C CNN
	1    2350 6700
	0    1    1    0   
$EndComp
Connection ~ 2100 5850
Connection ~ 2100 5000
Connection ~ 2100 6700
Wire Wire Line
	3000 700  3000 750 
Wire Wire Line
	3000 750  3000 850 
Wire Wire Line
	3000 850  3000 1000
Wire Wire Line
	3000 1000 3000 1050
Wire Wire Line
	1700 1750 1700 4400
Wire Wire Line
	1700 4400 2600 4400
Wire Wire Line
	2600 4400 2600 5000
Wire Wire Line
	2600 5000 2600 5850
Wire Wire Line
	2600 5850 2600 6700
Wire Wire Line
	2600 5000 2500 5000
Connection ~ 1700 1750
Wire Wire Line
	2600 6700 2500 6700
Connection ~ 2600 5000
Wire Wire Line
	2500 5850 2600 5850
Connection ~ 2600 5850
$Comp
L CONN_01X05 P2
U 1 1 587F3806
P 7300 3150
F 0 "P2" H 7300 3450 50  0000 C CNN
F 1 "I2C1" V 7400 3150 50  0000 C CNN
F 2 "" H 7300 3150 50  0000 C CNN
F 3 "" H 7300 3150 50  0000 C CNN
	1    7300 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3350 7100 3350
Wire Wire Line
	7000 2950 7100 2950
Connection ~ 7000 2950
Wire Wire Line
	5050 1150 5050 1200
Connection ~ 5050 1200
Connection ~ 5200 800 
Wire Wire Line
	3500 2650 6900 2650
Wire Wire Line
	6900 2650 6900 3000
Wire Wire Line
	6900 3000 6900 3050
Wire Wire Line
	6900 3050 7100 3050
Wire Wire Line
	3500 3150 5400 3150
Wire Wire Line
	5400 3150 5400 3250
Wire Wire Line
	5400 3250 6850 3250
Wire Wire Line
	6850 3250 7100 3250
$Comp
L R R11
U 1 1 587F6596
P 6650 3000
F 0 "R11" V 6730 3000 50  0000 C CNN
F 1 "3k" V 6650 3000 50  0000 C CNN
F 2 "" V 6580 3000 50  0000 C CNN
F 3 "" H 6650 3000 50  0000 C CNN
	1    6650 3000
	0    1    1    0   
$EndComp
$Comp
L R R12
U 1 1 587F66CA
P 6650 3350
F 0 "R12" V 6730 3350 50  0000 C CNN
F 1 "3k" V 6650 3350 50  0000 C CNN
F 2 "" V 6580 3350 50  0000 C CNN
F 3 "" H 6650 3350 50  0000 C CNN
	1    6650 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 3000 6900 3000
Connection ~ 6900 3000
Wire Wire Line
	6850 3350 6850 3250
Connection ~ 6850 3250
Wire Wire Line
	6850 3350 6800 3350
Wire Wire Line
	6400 3350 6500 3350
Wire Wire Line
	6400 2050 6400 3000
Wire Wire Line
	6400 3000 6400 3350
Wire Wire Line
	6400 3350 6400 3800
Wire Wire Line
	6400 3800 6400 4150
Wire Wire Line
	6400 4150 6400 4500
Wire Wire Line
	6400 4500 6400 4950
Wire Wire Line
	5200 3000 6400 3000
Wire Wire Line
	6400 3000 6500 3000
$Comp
L CONN_01X05 P3
U 1 1 587F705F
P 7300 3950
F 0 "P3" H 7300 4250 50  0000 C CNN
F 1 "I2C2" V 7400 3950 50  0000 C CNN
F 2 "" H 7300 3950 50  0000 C CNN
F 3 "" H 7300 3950 50  0000 C CNN
	1    7300 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4150 7100 4150
Wire Wire Line
	7000 3750 7100 3750
Connection ~ 7000 3750
Wire Wire Line
	6900 3850 7100 3850
$Comp
L R R13
U 1 1 587F706D
P 6650 3800
F 0 "R13" V 6730 3800 50  0000 C CNN
F 1 "3k" V 6650 3800 50  0000 C CNN
F 2 "" V 6580 3800 50  0000 C CNN
F 3 "" H 6650 3800 50  0000 C CNN
	1    6650 3800
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 587F7073
P 6650 4150
F 0 "R14" V 6730 4150 50  0000 C CNN
F 1 "3k" V 6650 4150 50  0000 C CNN
F 2 "" V 6580 4150 50  0000 C CNN
F 3 "" H 6650 4150 50  0000 C CNN
	1    6650 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 3800 6900 3800
Wire Wire Line
	6850 4150 6850 4050
Connection ~ 6850 4050
Wire Wire Line
	6850 4150 6800 4150
Connection ~ 7000 3350
Wire Wire Line
	7100 3950 6950 3950
Wire Wire Line
	6950 3150 6950 3950
Wire Wire Line
	6950 3950 6950 4750
Connection ~ 6950 3150
Wire Wire Line
	6900 3700 6900 3800
Wire Wire Line
	6900 3800 6900 3850
Wire Wire Line
	6400 4150 6500 4150
Connection ~ 6400 3350
Wire Wire Line
	6500 3800 6400 3800
Connection ~ 6400 3800
Wire Wire Line
	3500 3250 5300 3250
Wire Wire Line
	5300 3250 5300 3700
Wire Wire Line
	5300 3700 6900 3700
Connection ~ 6900 3800
Wire Wire Line
	3500 3350 5200 3350
Wire Wire Line
	5200 3350 5200 4050
Wire Wire Line
	5200 4050 6850 4050
Wire Wire Line
	6850 4050 7100 4050
$Comp
L CONN_01X05 P4
U 1 1 587F8B95
P 7300 4750
F 0 "P4" H 7300 5050 50  0000 C CNN
F 1 "I2C3" V 7400 4750 50  0000 C CNN
F 2 "" H 7300 4750 50  0000 C CNN
F 3 "" H 7300 4750 50  0000 C CNN
	1    7300 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 4550 7100 4550
Connection ~ 7000 4150
Wire Wire Line
	7000 4950 7100 4950
Connection ~ 7000 4550
Wire Wire Line
	6950 4750 7100 4750
Connection ~ 6950 3950
Wire Wire Line
	3500 3450 5100 3450
Wire Wire Line
	5100 3450 5100 4650
Wire Wire Line
	5100 4650 6900 4650
Wire Wire Line
	6900 4650 7100 4650
Wire Wire Line
	3500 3550 5000 3550
Wire Wire Line
	5000 3550 5000 4850
Wire Wire Line
	5000 4850 6900 4850
Wire Wire Line
	6900 4850 7100 4850
$Comp
L R R15
U 1 1 587FA8C2
P 6700 4500
F 0 "R15" V 6780 4500 50  0000 C CNN
F 1 "3k" V 6700 4500 50  0000 C CNN
F 2 "" V 6630 4500 50  0000 C CNN
F 3 "" H 6700 4500 50  0000 C CNN
	1    6700 4500
	0    1    1    0   
$EndComp
$Comp
L R R16
U 1 1 587FA991
P 6700 4950
F 0 "R16" V 6780 4950 50  0000 C CNN
F 1 "3k" V 6700 4950 50  0000 C CNN
F 2 "" V 6630 4950 50  0000 C CNN
F 3 "" H 6700 4950 50  0000 C CNN
	1    6700 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 4950 6550 4950
Connection ~ 6400 4150
Wire Wire Line
	6550 4500 6400 4500
Connection ~ 6400 4500
Wire Wire Line
	6850 4500 6900 4500
Wire Wire Line
	6900 4500 6900 4650
Connection ~ 6900 4650
Wire Wire Line
	6850 4950 6900 4950
Wire Wire Line
	6900 4950 6900 4850
Connection ~ 6900 4850
Wire Wire Line
	4550 1200 5050 1200
Wire Wire Line
	5050 1200 5550 1200
Wire Wire Line
	5550 1200 6100 1200
Wire Wire Line
	6100 1200 6400 1200
Wire Wire Line
	6400 1200 6850 1200
Wire Wire Line
	6850 1200 7000 1200
Wire Wire Line
	5200 3000 5200 1500
Wire Wire Line
	5200 1500 5200 1500
Wire Wire Line
	5200 1500 5200 800 
$Comp
L TL431DBZ D1
U 1 1 58989019
P 1350 2150
F 0 "D1" H 1250 2250 50  0000 C CNN
F 1 "LM4041" V 1300 1950 50  0000 C CNN
F 2 "SOT-23" H 1350 2000 50  0001 C CIN
F 3 "" H 1350 2150 50  0000 C CNN
	1    1350 2150
	0    1    -1   0   
$EndComp
Wire Wire Line
	1350 2050 1350 1750
Connection ~ 1350 1750
$Comp
L R R3
U 1 1 5898955A
P 1550 1950
F 0 "R3" V 1630 1950 50  0000 C CNN
F 1 "4.7k" V 1550 1950 50  0000 C CNN
F 2 "" V 1480 1950 50  0000 C CNN
F 3 "" H 1550 1950 50  0000 C CNN
	1    1550 1950
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 589895CD
P 1550 2350
F 0 "R4" V 1630 2350 50  0000 C CNN
F 1 "3k" V 1550 2350 50  0000 C CNN
F 2 "" V 1480 2350 50  0000 C CNN
F 3 "" H 1550 2350 50  0000 C CNN
	1    1550 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	800  2100 1000 2100
Wire Wire Line
	1000 2100 1100 2100
Connection ~ 1000 2100
Wire Wire Line
	1350 2250 1350 2500
Wire Wire Line
	1000 2500 1350 2500
Wire Wire Line
	1350 2500 1550 2500
Connection ~ 1000 2500
Wire Wire Line
	1450 2150 1550 2150
Wire Wire Line
	1550 2100 1550 2150
Wire Wire Line
	1550 2150 1550 2200
Connection ~ 1550 2150
Wire Wire Line
	1550 1800 1550 1750
Connection ~ 1550 1750
Connection ~ 1350 2500
Text Notes 1350 1750 0    60   ~ 0
+2v
$Comp
L CP C16
U 1 1 5898AFAE
P 800 1950
F 0 "C16" H 825 2050 50  0000 L CNN
F 1 "10u" H 825 1850 50  0000 L CNN
F 2 "" H 838 1800 50  0000 C CNN
F 3 "" H 800 1950 50  0000 C CNN
	1    800  1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	800  1400 800  700 
Wire Wire Line
	800  1700 800  1750
Wire Wire Line
	800  1750 800  1800
Connection ~ 800  1750
$Comp
L USB_B P6
U 1 1 5898C2CE
P 7400 2350
F 0 "P6" H 7600 2150 50  0000 C CNN
F 1 "USB_B" H 7350 2550 50  0000 C CNN
F 2 "" V 7350 2250 50  0000 C CNN
F 3 "" V 7350 2250 50  0000 C CNN
	1    7400 2350
	0    1    1    0   
$EndComp
$Comp
L R R19
U 1 1 5898D147
P 6700 2350
F 0 "R19" V 6780 2350 50  0000 C CNN
F 1 "22" V 6700 2350 50  0000 C CNN
F 2 "" V 6630 2350 50  0000 C CNN
F 3 "" H 6700 2350 50  0000 C CNN
	1    6700 2350
	0    1    1    0   
$EndComp
$Comp
L R R18
U 1 1 5898D3BB
P 6700 2250
F 0 "R18" V 6600 2250 50  0000 C CNN
F 1 "22" V 6700 2250 50  0000 C CNN
F 2 "" V 6630 2250 50  0000 C CNN
F 3 "" H 6700 2250 50  0000 C CNN
	1    6700 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 2250 6550 2250
Wire Wire Line
	3500 2350 6550 2350
Wire Wire Line
	6850 2250 7100 2250
Wire Wire Line
	6850 2350 6900 2350
Wire Wire Line
	6900 2350 7100 2350
Wire Wire Line
	7000 1200 7000 1450
Wire Wire Line
	7000 1450 7000 1850
Wire Wire Line
	7000 1850 7000 2450
Wire Wire Line
	7000 2450 7000 2700
Wire Wire Line
	7000 2700 7000 2950
Wire Wire Line
	7000 2950 7000 3350
Wire Wire Line
	7000 3350 7000 3750
Wire Wire Line
	7000 3750 7000 4150
Wire Wire Line
	7000 4150 7000 4550
Wire Wire Line
	7000 4550 7000 4950
Wire Wire Line
	7500 2650 7500 2700
Wire Wire Line
	7500 2700 7000 2700
Connection ~ 7000 2700
Wire Wire Line
	7100 2450 7000 2450
Connection ~ 7000 2450
$Comp
L R R17
U 1 1 5898EA28
P 6700 2050
F 0 "R17" V 6600 2050 50  0000 C CNN
F 1 "1.5k" V 6700 2050 50  0000 C CNN
F 2 "" V 6630 2050 50  0000 C CNN
F 3 "" H 6700 2050 50  0000 C CNN
	1    6700 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	6850 2050 6900 2050
Wire Wire Line
	6900 2050 6900 2350
Connection ~ 6900 2350
Wire Wire Line
	5950 3150 6950 3150
Wire Wire Line
	6950 3150 7100 3150
Connection ~ 6400 3000
Wire Wire Line
	6550 2050 6400 2050
$Comp
L L L2
U 1 1 58990192
P 6600 850
F 0 "L2" V 6550 850 50  0000 C CNN
F 1 "1u" V 6675 850 50  0000 C CNN
F 2 "" H 6600 850 50  0000 C CNN
F 3 "" H 6600 850 50  0000 C CNN
	1    6600 850 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6450 850  6400 850 
Wire Wire Line
	6400 850  6100 850 
Wire Wire Line
	6100 850  5950 850 
Wire Wire Line
	5950 850  5850 850 
Wire Wire Line
	6750 850  6850 850 
Wire Wire Line
	6850 850  7100 850 
Wire Wire Line
	7100 850  7100 1650
Wire Wire Line
	7100 1650 7100 2150
$Comp
L C C19
U 1 1 58990639
P 6850 1050
F 0 "C19" H 6875 1150 50  0000 L CNN
F 1 "100n" H 6875 950 50  0000 L CNN
F 2 "" H 6888 900 50  0000 C CNN
F 3 "" H 6850 1050 50  0000 C CNN
	1    6850 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 900  6850 850 
Connection ~ 6850 850 
Connection ~ 6850 1200
$Comp
L C C18
U 1 1 58990BFB
P 6400 1050
F 0 "C18" H 6425 1150 50  0000 L CNN
F 1 "100n" H 6425 950 50  0000 L CNN
F 2 "" H 6438 900 50  0000 C CNN
F 3 "" H 6400 1050 50  0000 C CNN
	1    6400 1050
	1    0    0    -1  
$EndComp
Connection ~ 6400 1200
Wire Wire Line
	6400 900  6400 850 
Connection ~ 6400 850 
$Comp
L CP C17
U 1 1 58991219
P 6100 1050
F 0 "C17" H 6125 1150 50  0000 L CNN
F 1 "10u" H 6125 950 50  0000 L CNN
F 2 "" H 6138 900 50  0000 C CNN
F 3 "" H 6100 1050 50  0000 C CNN
	1    6100 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 900  6100 850 
Connection ~ 6100 850 
Connection ~ 6100 1200
Wire Wire Line
	5950 3150 5950 850 
Connection ~ 5950 850 
$Comp
L CONN_01X05 P5
U 1 1 58991B5B
P 7400 1650
F 0 "P5" H 7400 1950 50  0000 C CNN
F 1 "UART" V 7500 1650 50  0000 C CNN
F 2 "" H 7400 1650 50  0000 C CNN
F 3 "" H 7400 1650 50  0000 C CNN
	1    7400 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 1850 7000 1850
Connection ~ 7000 1850
Wire Wire Line
	7200 1450 7000 1450
Connection ~ 7000 1450
Wire Wire Line
	7200 1650 7100 1650
Connection ~ 7100 1650
Wire Wire Line
	4850 3650 4850 1750
Wire Wire Line
	4850 1750 7200 1750
Wire Wire Line
	4750 3750 4750 1550
Wire Wire Line
	4750 1550 7200 1550
$EndSCHEMATC
