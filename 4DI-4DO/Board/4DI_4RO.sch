EESchema Schematic File Version 2
LIBS:4DI_4RO-rescue
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
LIBS:Moja
LIBS:relay
LIBS:4DI_4RO-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "4DI_4RO_ASCI_RS485"
Date "4 dec 2014"
Rev "1.0"
Comp "EAP"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA8-P IC1
U 1 1 536FA5E5
P 2750 5050
F 0 "IC1" H 2000 6350 40  0000 L BNN
F 1 "ATMEGA8-P" H 3250 3600 40  0000 L BNN
F 2 "DIL28" H 2750 5050 30  0000 C CIN
F 3 "" H 2750 5050 60  0000 C CNN
	1    2750 5050
	1    0    0    -1  
$EndComp
$Comp
L 7805 U1
U 1 1 536FB6E6
P 2900 1100
F 0 "U1" H 3050 904 60  0000 C CNN
F 1 "7805" H 2900 1300 60  0000 C CNN
F 2 "~" H 2900 1100 60  0000 C CNN
F 3 "~" H 2900 1100 60  0000 C CNN
	1    2900 1100
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR01
U 1 1 536FB705
P 900 1900
F 0 "#PWR01" H 900 2000 30  0001 C CNN
F 1 "VCC" H 900 2000 30  0000 C CNN
F 2 "" H 900 1900 60  0000 C CNN
F 3 "" H 900 1900 60  0000 C CNN
	1    900  1900
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR02
U 1 1 536FB720
P 1550 1000
F 0 "#PWR02" H 1550 1100 30  0001 C CNN
F 1 "VCC" H 1550 1100 30  0000 C CNN
F 2 "" H 1550 1000 60  0000 C CNN
F 3 "" H 1550 1000 60  0000 C CNN
	1    1550 1000
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR03
U 1 1 536FB73C
P 2900 2100
F 0 "#PWR03" H 2900 2100 40  0001 C CNN
F 1 "DGND" H 2900 2030 40  0000 C CNN
F 2 "" H 2900 2100 60  0000 C CNN
F 3 "" H 2900 2100 60  0000 C CNN
	1    2900 2100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 536FB74F
P 3300 1000
F 0 "#PWR04" H 3300 1090 20  0001 C CNN
F 1 "+5V" H 3300 1090 30  0000 C CNN
F 2 "" H 3300 1000 60  0000 C CNN
F 3 "" H 3300 1000 60  0000 C CNN
	1    3300 1000
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR05
U 1 1 536FC3D6
P 2750 6650
F 0 "#PWR05" H 2750 6650 40  0001 C CNN
F 1 "DGND" H 2750 6580 40  0000 C CNN
F 2 "" H 2750 6650 60  0000 C CNN
F 3 "" H 2750 6650 60  0000 C CNN
	1    2750 6650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 53710314
P 2750 3600
F 0 "#PWR06" H 2750 3690 20  0001 C CNN
F 1 "+5V" H 2750 3690 30  0000 C CNN
F 2 "" H 2750 3600 60  0000 C CNN
F 3 "" H 2750 3600 60  0000 C CNN
	1    2750 3600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR07
U 1 1 53710335
P 1800 4150
F 0 "#PWR07" H 1800 4240 20  0001 C CNN
F 1 "+5V" H 1800 4240 30  0000 C CNN
F 2 "" H 1800 4150 60  0000 C CNN
F 3 "" H 1800 4150 60  0000 C CNN
	1    1800 4150
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR08
U 1 1 5371033B
P 1800 4550
F 0 "#PWR08" H 1800 4550 40  0001 C CNN
F 1 "DGND" H 1800 4480 40  0000 C CNN
F 2 "" H 1800 4550 60  0000 C CNN
F 3 "" H 1800 4550 60  0000 C CNN
	1    1800 4550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR09
U 1 1 537103D6
P 1300 3900
F 0 "#PWR09" H 1300 3990 20  0001 C CNN
F 1 "+5V" H 1300 3990 30  0000 C CNN
F 2 "" H 1300 3900 60  0000 C CNN
F 3 "" H 1300 3900 60  0000 C CNN
	1    1300 3900
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-4DI_4RO R1
U 1 1 537103DE
P 1550 3950
F 0 "R1" V 1630 3950 40  0000 C CNN
F 1 "4.7k" V 1557 3951 40  0000 C CNN
F 2 "~" V 1480 3950 30  0000 C CNN
F 3 "~" H 1550 3950 30  0000 C CNN
	1    1550 3950
	0    -1   -1   0   
$EndComp
$Comp
L LTV847 U2
U 1 1 537661B1
P 5700 2950
F 0 "U2" H 5400 3850 60  0000 C CNN
F 1 "TIL193" H 5700 2050 60  0000 C CNN
F 2 "" H 5700 2950 60  0000 C CNN
F 3 "" H 5700 2950 60  0000 C CNN
	1    5700 2950
	0    1    1    0   
$EndComp
$Comp
L DGND #PWR010
U 1 1 537661CC
P 4950 3800
F 0 "#PWR010" H 4950 3800 40  0001 C CNN
F 1 "DGND" H 4950 3730 40  0000 C CNN
F 2 "" H 4950 3800 60  0000 C CNN
F 3 "" H 4950 3800 60  0000 C CNN
	1    4950 3800
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR011
U 1 1 537661E0
P 5350 3800
F 0 "#PWR011" H 5350 3800 40  0001 C CNN
F 1 "DGND" H 5350 3730 40  0000 C CNN
F 2 "" H 5350 3800 60  0000 C CNN
F 3 "" H 5350 3800 60  0000 C CNN
	1    5350 3800
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR012
U 1 1 537661E7
P 5750 3800
F 0 "#PWR012" H 5750 3800 40  0001 C CNN
F 1 "DGND" H 5750 3730 40  0000 C CNN
F 2 "" H 5750 3800 60  0000 C CNN
F 3 "" H 5750 3800 60  0000 C CNN
	1    5750 3800
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR013
U 1 1 537661EE
P 6150 3800
F 0 "#PWR013" H 6150 3800 40  0001 C CNN
F 1 "DGND" H 6150 3730 40  0000 C CNN
F 2 "" H 6150 3800 60  0000 C CNN
F 3 "" H 6150 3800 60  0000 C CNN
	1    6150 3800
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR014
U 1 1 537668A6
P 5100 2450
F 0 "#PWR014" H 5100 2500 40  0001 C CNN
F 1 "GNDPWR" H 5100 2370 40  0000 C CNN
F 2 "" H 5100 2450 60  0000 C CNN
F 3 "" H 5100 2450 60  0000 C CNN
	1    5100 2450
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR015
U 1 1 537668B5
P 5500 2450
F 0 "#PWR015" H 5500 2500 40  0001 C CNN
F 1 "GNDPWR" H 5500 2370 40  0000 C CNN
F 2 "" H 5500 2450 60  0000 C CNN
F 3 "" H 5500 2450 60  0000 C CNN
	1    5500 2450
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR016
U 1 1 537668C4
P 5900 2450
F 0 "#PWR016" H 5900 2500 40  0001 C CNN
F 1 "GNDPWR" H 5900 2370 40  0000 C CNN
F 2 "" H 5900 2450 60  0000 C CNN
F 3 "" H 5900 2450 60  0000 C CNN
	1    5900 2450
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR017
U 1 1 537668D3
P 6300 2450
F 0 "#PWR017" H 6300 2500 40  0001 C CNN
F 1 "GNDPWR" H 6300 2370 40  0000 C CNN
F 2 "" H 6300 2450 60  0000 C CNN
F 3 "" H 6300 2450 60  0000 C CNN
	1    6300 2450
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D6
U 1 1 5376699C
P 5150 2000
F 0 "D6" H 5000 1950 40  0000 C CNN
F 1 "Tr 5.8V" H 5200 1950 40  0000 C CNN
F 2 "~" H 5150 2000 60  0000 C CNN
F 3 "~" H 5150 2000 60  0000 C CNN
	1    5150 2000
	0    -1   -1   0   
$EndComp
$Comp
L DIODESCH D7
U 1 1 537669AB
P 5550 2000
F 0 "D7" H 5400 1950 40  0000 C CNN
F 1 "Tr 5.8V" H 5600 1950 40  0000 C CNN
F 2 "~" H 5550 2000 60  0000 C CNN
F 3 "~" H 5550 2000 60  0000 C CNN
	1    5550 2000
	0    -1   -1   0   
$EndComp
$Comp
L DIODESCH D8
U 1 1 537669BA
P 5950 2000
F 0 "D8" H 5800 1950 40  0000 C CNN
F 1 "Tr 5.8V" H 6000 1950 40  0000 C CNN
F 2 "~" H 5950 2000 60  0000 C CNN
F 3 "~" H 5950 2000 60  0000 C CNN
	1    5950 2000
	0    -1   -1   0   
$EndComp
$Comp
L DIODESCH D9
U 1 1 537669C9
P 6350 2000
F 0 "D9" H 6200 1950 40  0000 C CNN
F 1 "Tr 5.8V" H 6400 1950 40  0000 C CNN
F 2 "~" H 6350 2000 60  0000 C CNN
F 3 "~" H 6350 2000 60  0000 C CNN
	1    6350 2000
	0    -1   -1   0   
$EndComp
$Comp
L CRYSTAL X1
U 1 1 5376726D
P 1300 4750
F 0 "X1" H 1300 4900 60  0000 C CNN
F 1 "3.6864 MHz" H 1300 4600 60  0000 C CNN
F 2 "~" H 1300 4750 60  0000 C CNN
F 3 "~" H 1300 4750 60  0000 C CNN
	1    1300 4750
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-4DI_4RO C1
U 1 1 5376733B
P 1000 4450
F 0 "C1" H 1000 4550 40  0000 L CNN
F 1 "27pF" H 1006 4365 40  0000 L CNN
F 2 "~" H 1038 4300 30  0000 C CNN
F 3 "~" H 1000 4450 60  0000 C CNN
	1    1000 4450
	0    1    1    0   
$EndComp
$Comp
L C-RESCUE-4DI_4RO C2
U 1 1 5376734A
P 1000 5050
F 0 "C2" H 1000 5150 40  0000 L CNN
F 1 "27pF" H 1006 4965 40  0000 L CNN
F 2 "~" H 1038 4900 30  0000 C CNN
F 3 "~" H 1000 5050 60  0000 C CNN
	1    1000 5050
	0    1    1    0   
$EndComp
$Comp
L DGND #PWR018
U 1 1 5376741E
P 750 4500
F 0 "#PWR018" H 750 4500 40  0001 C CNN
F 1 "DGND" H 750 4430 40  0000 C CNN
F 2 "" H 750 4500 60  0000 C CNN
F 3 "" H 750 4500 60  0000 C CNN
	1    750  4500
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR019
U 1 1 53767424
P 750 5100
F 0 "#PWR019" H 750 5100 40  0001 C CNN
F 1 "DGND" H 750 5030 40  0000 C CNN
F 2 "" H 750 5100 60  0000 C CNN
F 3 "" H 750 5100 60  0000 C CNN
	1    750  5100
	1    0    0    -1  
$EndComp
$Comp
L G5L K1
U 1 1 53766F47
P 6350 5650
F 0 "K1" H 6400 5500 50  0000 L BNN
F 1 "RELAY" H 6400 5765 50  0000 L BNN
F 2 "relay-G5LE" H 6350 5800 50  0001 C CNN
F 3 "" H 6350 5650 60  0000 C CNN
	1    6350 5650
	1    0    0    -1  
$EndComp
$Comp
L G5L K2
U 1 1 53766F56
P 7250 5650
F 0 "K2" H 7300 5500 50  0000 L BNN
F 1 "RELAY" H 7300 5765 50  0000 L BNN
F 2 "relay-G5LE" H 7250 5800 50  0001 C CNN
F 3 "" H 7250 5650 60  0000 C CNN
	1    7250 5650
	1    0    0    -1  
$EndComp
$Comp
L G5L K3
U 1 1 53766F65
P 8200 5650
F 0 "K3" H 8250 5500 50  0000 L BNN
F 1 "RELAY" H 8250 5765 50  0000 L BNN
F 2 "relay-G5LE" H 8200 5800 50  0001 C CNN
F 3 "" H 8200 5650 60  0000 C CNN
	1    8200 5650
	1    0    0    -1  
$EndComp
$Comp
L G5L K4
U 1 1 53766F74
P 9150 5700
F 0 "K4" H 9200 5550 50  0000 L BNN
F 1 "RELAY" H 9200 5815 50  0000 L BNN
F 2 "relay-G5LE" H 9150 5850 50  0001 C CNN
F 3 "" H 9150 5700 60  0000 C CNN
	1    9150 5700
	1    0    0    -1  
$EndComp
$Comp
L G5L K1
U 2 1 53766F8D
P 8100 1800
F 0 "K1" H 7950 1850 50  0000 L BNN
F 1 "RELAY" H 8000 2050 50  0000 L BNN
F 2 "relay-G5LE" H 8100 1950 50  0001 C CNN
F 3 "" H 8100 1800 60  0000 C CNN
	2    8100 1800
	-1   0    0    1   
$EndComp
$Comp
L G5L K2
U 2 1 53766FAB
P 8900 1800
F 0 "K2" H 8750 1850 50  0000 L BNN
F 1 "RELAY" H 8800 2050 50  0000 L BNN
F 2 "relay-G5LE" H 8900 1950 50  0001 C CNN
F 3 "" H 8900 1800 60  0000 C CNN
	2    8900 1800
	-1   0    0    1   
$EndComp
$Comp
L G5L K3
U 2 1 53766FBA
P 9700 1800
F 0 "K3" H 9550 1850 50  0000 L BNN
F 1 "RELAY" H 9600 2050 50  0000 L BNN
F 2 "relay-G5LE" H 9700 1950 50  0001 C CNN
F 3 "" H 9700 1800 60  0000 C CNN
	2    9700 1800
	-1   0    0    1   
$EndComp
$Comp
L G5L K4
U 2 1 53766FC9
P 10500 1800
F 0 "K4" H 10350 1850 50  0000 L BNN
F 1 "RELAY" H 10400 2050 50  0000 L BNN
F 2 "relay-G5LE" H 10500 1950 50  0001 C CNN
F 3 "" H 10500 1800 60  0000 C CNN
	2    10500 1800
	-1   0    0    1   
$EndComp
$Comp
L DGND #PWR020
U 1 1 53767468
P 5950 6250
F 0 "#PWR020" H 5950 6250 40  0001 C CNN
F 1 "DGND" H 5950 6180 40  0000 C CNN
F 2 "" H 5950 6250 60  0000 C CNN
F 3 "" H 5950 6250 60  0000 C CNN
	1    5950 6250
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR021
U 1 1 5376746E
P 6850 6300
F 0 "#PWR021" H 6850 6300 40  0001 C CNN
F 1 "DGND" H 6850 6230 40  0000 C CNN
F 2 "" H 6850 6300 60  0000 C CNN
F 3 "" H 6850 6300 60  0000 C CNN
	1    6850 6300
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR022
U 1 1 53767474
P 7800 6300
F 0 "#PWR022" H 7800 6300 40  0001 C CNN
F 1 "DGND" H 7800 6230 40  0000 C CNN
F 2 "" H 7800 6300 60  0000 C CNN
F 3 "" H 7800 6300 60  0000 C CNN
	1    7800 6300
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR023
U 1 1 5376747A
P 8750 6300
F 0 "#PWR023" H 8750 6300 40  0001 C CNN
F 1 "DGND" H 8750 6230 40  0000 C CNN
F 2 "" H 8750 6300 60  0000 C CNN
F 3 "" H 8750 6300 60  0000 C CNN
	1    8750 6300
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR024
U 1 1 5376787B
P 4800 6700
F 0 "#PWR024" H 4800 6700 40  0001 C CNN
F 1 "DGND" H 4800 6630 40  0000 C CNN
F 2 "" H 4800 6700 60  0000 C CNN
F 3 "" H 4800 6700 60  0000 C CNN
	1    4800 6700
	1    0    0    -1  
$EndComp
Text Label 5200 6100 0    60   ~ 0
A
Text GLabel 5400 6100 2    60   Output ~ 0
A
Text GLabel 5400 6300 2    60   Output ~ 0
B
Text GLabel 7000 1650 3    60   Input ~ 0
A
Text GLabel 7200 1650 3    60   Input ~ 0
B
$Comp
L BC337 Q1
U 1 1 538088FF
P 6150 5900
F 0 "Q1" H 6350 5800 50  0000 C CNN
F 1 "BC337" H 6400 6050 50  0000 C CNN
F 2 "TO92-EBC" H 6340 5900 30  0001 C CNN
F 3 "~" H 6150 5900 60  0000 C CNN
	1    6150 5900
	0    1    1    0   
$EndComp
$Comp
L BC337 Q2
U 1 1 5380890E
P 7050 5950
F 0 "Q2" H 7250 5850 50  0000 C CNN
F 1 "BC337" H 7300 6100 50  0000 C CNN
F 2 "TO92-EBC" H 7240 5950 30  0001 C CNN
F 3 "~" H 7050 5950 60  0000 C CNN
	1    7050 5950
	0    1    1    0   
$EndComp
$Comp
L BC337 Q3
U 1 1 53808A58
P 8000 5950
F 0 "Q3" H 8200 5850 50  0000 C CNN
F 1 "BC337" H 8250 6100 50  0000 C CNN
F 2 "TO92-EBC" H 8190 5950 30  0001 C CNN
F 3 "~" H 8000 5950 60  0000 C CNN
	1    8000 5950
	0    1    1    0   
$EndComp
$Comp
L BC337 Q4
U 1 1 53808A67
P 8950 5950
F 0 "Q4" H 9150 5850 50  0000 C CNN
F 1 "BC337" H 9200 6100 50  0000 C CNN
F 2 "TO92-EBC" H 9140 5950 30  0001 C CNN
F 3 "~" H 8950 5950 60  0000 C CNN
	1    8950 5950
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR025
U 1 1 53808A80
P 4800 5750
F 0 "#PWR025" H 4800 5840 20  0001 C CNN
F 1 "+5V" H 4800 5840 30  0000 C CNN
F 2 "" H 4800 5750 60  0000 C CNN
F 3 "" H 4800 5750 60  0000 C CNN
	1    4800 5750
	1    0    0    -1  
$EndComp
$Comp
L CONN_5 P2
U 1 1 53808DE2
P 5550 600
F 0 "P2" V 5500 600 50  0000 C CNN
F 1 "5 PIN" V 5600 600 50  0000 C CNN
F 2 "~" H 5550 600 60  0000 C CNN
F 3 "~" H 5550 600 60  0000 C CNN
	1    5550 600 
	0    -1   -1   0   
$EndComp
$Comp
L GNDPWR #PWR026
U 1 1 53808DFE
P 5950 800
F 0 "#PWR026" H 5950 850 40  0001 C CNN
F 1 "GNDPWR" H 5950 720 40  0000 C CNN
F 2 "" H 5950 800 60  0000 C CNN
F 3 "" H 5950 800 60  0000 C CNN
	1    5950 800 
	-1   0    0    1   
$EndComp
$Comp
L CONN_PWR-RESCUE-4DI_4RO P1
U 1 1 53809C1F
P 1000 950
F 0 "P1" V 950 950 40  0000 C CNN
F 1 "3 PIN" V 1050 950 40  0000 C CNN
F 2 "~" H 1000 950 60  0000 C CNN
F 3 "~" H 1000 950 60  0000 C CNN
	1    1000 950 
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-4DI_4RO R7
U 1 1 5380D228
P 4700 4650
F 0 "R7" V 4700 4550 40  0000 C CNN
F 1 "560" V 4700 4700 40  0000 C CNN
F 2 "~" V 4630 4650 30  0000 C CNN
F 3 "~" H 4700 4650 30  0000 C CNN
	1    4700 4650
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-4DI_4RO R9
U 1 1 5380D237
P 4700 4850
F 0 "R9" V 4700 4750 40  0000 C CNN
F 1 "560" V 4700 4900 40  0000 C CNN
F 2 "~" V 4630 4850 30  0000 C CNN
F 3 "~" H 4700 4850 30  0000 C CNN
	1    4700 4850
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-4DI_4RO R8
U 1 1 5380D246
P 4700 4750
F 0 "R8" V 4700 4650 40  0000 C CNN
F 1 "560" V 4700 4800 40  0000 C CNN
F 2 "~" V 4630 4750 30  0000 C CNN
F 3 "~" H 4700 4750 30  0000 C CNN
	1    4700 4750
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-4DI_4RO R10
U 1 1 5380D255
P 4700 4950
F 0 "R10" V 4700 4850 40  0000 C CNN
F 1 "560" V 4700 5000 40  0000 C CNN
F 2 "~" V 4630 4950 30  0000 C CNN
F 3 "~" H 4700 4950 30  0000 C CNN
	1    4700 4950
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-4DI_4RO R11
U 1 1 5380D3F1
P 5250 1500
F 0 "R11" V 5250 1400 40  0000 C CNN
F 1 "3,9k" V 5250 1550 40  0000 C CNN
F 2 "~" V 5180 1500 30  0000 C CNN
F 3 "~" H 5250 1500 30  0000 C CNN
	1    5250 1500
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-4DI_4RO R12
U 1 1 5380D400
P 5650 1500
F 0 "R12" V 5650 1400 40  0000 C CNN
F 1 "3,9k" V 5650 1550 40  0000 C CNN
F 2 "~" V 5580 1500 30  0000 C CNN
F 3 "~" H 5650 1500 30  0000 C CNN
	1    5650 1500
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-4DI_4RO R13
U 1 1 5380D40F
P 6050 1500
F 0 "R13" V 6050 1400 40  0000 C CNN
F 1 "3,9k" V 6050 1550 40  0000 C CNN
F 2 "~" V 5980 1500 30  0000 C CNN
F 3 "~" H 6050 1500 30  0000 C CNN
	1    6050 1500
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-4DI_4RO R14
U 1 1 5380D41E
P 6450 1500
F 0 "R14" V 6450 1400 40  0000 C CNN
F 1 "3,9k" V 6450 1550 40  0000 C CNN
F 2 "~" V 6380 1500 30  0000 C CNN
F 3 "~" H 6450 1500 30  0000 C CNN
	1    6450 1500
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-4DI_4RO R6
U 1 1 5380D5F6
P 4300 3650
F 0 "R6" V 4300 3550 40  0000 C CNN
F 1 "10k" V 4300 3700 40  0000 C CNN
F 2 "~" V 4230 3650 30  0000 C CNN
F 3 "~" H 4300 3650 30  0000 C CNN
	1    4300 3650
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-4DI_4RO R5
U 1 1 5380D605
P 4150 3750
F 0 "R5" V 4150 3650 40  0000 C CNN
F 1 "10k" V 4150 3800 40  0000 C CNN
F 2 "~" V 4080 3750 30  0000 C CNN
F 3 "~" H 4150 3750 30  0000 C CNN
	1    4150 3750
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-4DI_4RO R4
U 1 1 5380D614
P 4000 3850
F 0 "R4" V 4000 3750 40  0000 C CNN
F 1 "10k" V 4000 3900 40  0000 C CNN
F 2 "~" V 3930 3850 30  0000 C CNN
F 3 "~" H 4000 3850 30  0000 C CNN
	1    4000 3850
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-4DI_4RO R3
U 1 1 5380D623
P 3850 3950
F 0 "R3" V 3850 3850 40  0000 C CNN
F 1 "10k" V 3850 4000 40  0000 C CNN
F 2 "~" V 3780 3950 30  0000 C CNN
F 3 "~" H 3850 3950 30  0000 C CNN
	1    3850 3950
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-4DI_4RO C12
U 1 1 53810910
P 5100 5850
F 0 "C12" H 5100 5950 40  0000 L CNN
F 1 "100nF" H 5106 5765 40  0000 L CNN
F 2 "~" H 5138 5700 30  0000 C CNN
F 3 "~" H 5100 5850 60  0000 C CNN
	1    5100 5850
	0    -1   -1   0   
$EndComp
$Comp
L DGND #PWR027
U 1 1 5381091D
P 5550 5850
F 0 "#PWR027" H 5550 5850 40  0001 C CNN
F 1 "DGND" H 5550 5780 40  0000 C CNN
F 2 "" H 5550 5850 60  0000 C CNN
F 3 "" H 5550 5850 60  0000 C CNN
	1    5550 5850
	0    -1   -1   0   
$EndComp
$Comp
L CPsmall C4
U 1 1 53810A83
P 2250 1600
F 0 "C4" H 2275 1650 30  0000 L CNN
F 1 "47uF" H 2275 1525 30  0000 L CNN
F 2 "~" H 2250 1600 60  0000 C CNN
F 3 "~" H 2250 1600 60  0000 C CNN
	1    2250 1600
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D2
U 1 1 53810D7E
P 1550 1600
F 0 "D2" H 1550 1700 40  0000 C CNN
F 1 "Tr 30V" H 1550 1500 40  0000 C CNN
F 2 "~" H 1550 1600 60  0000 C CNN
F 3 "~" H 1550 1600 60  0000 C CNN
	1    1550 1600
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D13
U 1 1 5381203A
P 9550 5700
F 0 "D13" H 9550 5800 40  0000 C CNN
F 1 "DIODE" H 9550 5600 40  0000 C CNN
F 2 "~" H 9550 5700 60  0000 C CNN
F 3 "~" H 9550 5700 60  0000 C CNN
	1    9550 5700
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D12
U 1 1 53812049
P 8500 5650
F 0 "D12" H 8500 5750 40  0000 C CNN
F 1 "DIODE" H 8500 5550 40  0000 C CNN
F 2 "~" H 8500 5650 60  0000 C CNN
F 3 "~" H 8500 5650 60  0000 C CNN
	1    8500 5650
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D11
U 1 1 53812058
P 7550 5650
F 0 "D11" H 7550 5750 40  0000 C CNN
F 1 "DIODE" H 7550 5550 40  0000 C CNN
F 2 "~" H 7550 5650 60  0000 C CNN
F 3 "~" H 7550 5650 60  0000 C CNN
	1    7550 5650
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D10
U 1 1 53812067
P 6650 5650
F 0 "D10" H 6650 5750 40  0000 C CNN
F 1 "DIODE" H 6650 5550 40  0000 C CNN
F 2 "~" H 6650 5650 60  0000 C CNN
F 3 "~" H 6650 5650 60  0000 C CNN
	1    6650 5650
	0    -1   -1   0   
$EndComp
$Comp
L C-RESCUE-4DI_4RO C3
U 1 1 53812D72
P 1650 4350
F 0 "C3" H 1650 4450 40  0000 L CNN
F 1 "100nF" H 1656 4265 40  0000 L CNN
F 2 "~" H 1688 4200 30  0000 C CNN
F 3 "~" H 1650 4350 60  0000 C CNN
	1    1650 4350
	1    0    0    -1  
$EndComp
$Comp
L ADM485 IC2
U 1 1 53820162
P 4800 6200
F 0 "IC2" H 4600 6450 40  0000 C CNN
F 1 "ADM485" H 5000 5950 40  0000 C CNN
F 2 "DIP8" H 4800 6200 35  0000 C CIN
F 3 "" H 4800 6200 60  0000 C CNN
	1    4800 6200
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 53823A7C
P 900 1600
F 0 "D1" H 900 1700 40  0000 C CNN
F 1 "DIODE" H 900 1500 40  0000 C CNN
F 2 "~" H 900 1600 60  0000 C CNN
F 3 "~" H 900 1600 60  0000 C CNN
	1    900  1600
	0    1    1    0   
$EndComp
$Comp
L LED-RESCUE-4DI_4RO D3
U 1 1 53823C35
P 1800 1850
F 0 "D3" H 1800 1950 50  0000 C CNN
F 1 "LED" H 1800 1750 50  0000 C CNN
F 2 "~" H 1800 1850 60  0000 C CNN
F 3 "~" H 1800 1850 60  0000 C CNN
	1    1800 1850
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-4DI_4RO R2
U 1 1 53823C44
P 1800 1350
F 0 "R2" V 1800 1250 40  0000 C CNN
F 1 "3,9k" V 1800 1400 40  0000 C CNN
F 2 "~" V 1730 1350 30  0000 C CNN
F 3 "~" H 1800 1350 30  0000 C CNN
	1    1800 1350
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-4DI_4RO C11
U 1 1 5384B522
P 5000 2000
F 0 "C11" H 5000 2100 40  0000 L CNN
F 1 "100nF" H 5006 1915 40  0000 L CNN
F 2 "~" H 5038 1850 30  0000 C CNN
F 3 "~" H 5000 2000 60  0000 C CNN
	1    5000 2000
	-1   0    0    1   
$EndComp
$Comp
L C-RESCUE-4DI_4RO C13
U 1 1 5384B531
P 5400 2000
F 0 "C13" H 5400 2100 40  0000 L CNN
F 1 "100nF" H 5406 1915 40  0000 L CNN
F 2 "~" H 5438 1850 30  0000 C CNN
F 3 "~" H 5400 2000 60  0000 C CNN
	1    5400 2000
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-4DI_4RO C14
U 1 1 5384B540
P 5800 2000
F 0 "C14" H 5800 2100 40  0000 L CNN
F 1 "100nF" H 5806 1915 40  0000 L CNN
F 2 "~" H 5838 1850 30  0000 C CNN
F 3 "~" H 5800 2000 60  0000 C CNN
	1    5800 2000
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-4DI_4RO C15
U 1 1 5384B54F
P 6200 2000
F 0 "C15" H 6200 2100 40  0000 L CNN
F 1 "100nF" H 6206 1915 40  0000 L CNN
F 2 "~" H 6238 1850 30  0000 C CNN
F 3 "~" H 6200 2000 60  0000 C CNN
	1    6200 2000
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D5
U 1 1 53863744
P 6800 1300
F 0 "D5" H 6800 1400 40  0000 C CNN
F 1 "Tr 15V" H 6800 1200 40  0000 C CNN
F 2 "~" H 6800 1300 60  0000 C CNN
F 3 "~" H 6800 1300 60  0000 C CNN
	1    6800 1300
	0    -1   -1   0   
$EndComp
$Comp
L DIODESCH D4
U 1 1 53863CB0
P 7350 1300
F 0 "D4" H 7350 1400 40  0000 C CNN
F 1 "Tr 15V" H 7350 1200 40  0000 C CNN
F 2 "~" H 7350 1300 60  0000 C CNN
F 3 "~" H 7350 1300 60  0000 C CNN
	1    7350 1300
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-4DI_4RO R15
U 1 1 538ACD2A
P 7000 1300
F 0 "R15" V 7000 1200 40  0000 C CNN
F 1 "10R" V 7000 1350 40  0000 C CNN
F 2 "~" V 6930 1300 30  0000 C CNN
F 3 "~" H 7000 1300 30  0000 C CNN
	1    7000 1300
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-4DI_4RO R16
U 1 1 538ACD39
P 7200 1300
F 0 "R16" V 7200 1200 40  0000 C CNN
F 1 "10R" V 7200 1350 40  0000 C CNN
F 2 "~" V 7130 1300 30  0000 C CNN
F 3 "~" H 7200 1300 30  0000 C CNN
	1    7200 1300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR028
U 1 1 538ADBD6
P 4300 3350
F 0 "#PWR028" H 4300 3440 20  0001 C CNN
F 1 "+5V" H 4300 3440 30  0000 C CNN
F 2 "" H 4300 3350 60  0000 C CNN
F 3 "" H 4300 3350 60  0000 C CNN
	1    4300 3350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR029
U 1 1 538ADBDC
P 4150 3450
F 0 "#PWR029" H 4150 3540 20  0001 C CNN
F 1 "+5V" H 4150 3540 30  0000 C CNN
F 2 "" H 4150 3450 60  0000 C CNN
F 3 "" H 4150 3450 60  0000 C CNN
	1    4150 3450
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR030
U 1 1 538ADBE2
P 4000 3550
F 0 "#PWR030" H 4000 3640 20  0001 C CNN
F 1 "+5V" H 4000 3640 30  0000 C CNN
F 2 "" H 4000 3550 60  0000 C CNN
F 3 "" H 4000 3550 60  0000 C CNN
	1    4000 3550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR031
U 1 1 538ADBE8
P 3850 3650
F 0 "#PWR031" H 3850 3740 20  0001 C CNN
F 1 "+5V" H 3850 3740 30  0000 C CNN
F 2 "" H 3850 3650 60  0000 C CNN
F 3 "" H 3850 3650 60  0000 C CNN
	1    3850 3650
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-4DI_4RO C7
U 1 1 538E0ECE
P 3900 1600
F 0 "C7" H 3900 1700 40  0000 L CNN
F 1 "100nF" H 3906 1515 40  0000 L CNN
F 2 "~" H 3938 1450 30  0000 C CNN
F 3 "~" H 3900 1600 60  0000 C CNN
	1    3900 1600
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-4DI_4RO C8
U 1 1 53908383
P 4150 1600
F 0 "C8" H 4150 1700 40  0000 L CNN
F 1 "100nF" H 4156 1515 40  0000 L CNN
F 2 "~" H 4188 1450 30  0000 C CNN
F 3 "~" H 4150 1600 60  0000 C CNN
	1    4150 1600
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-4DI_4RO C9
U 1 1 53908389
P 4400 1600
F 0 "C9" H 4400 1700 40  0000 L CNN
F 1 "100nF" H 4406 1515 40  0000 L CNN
F 2 "~" H 4438 1450 30  0000 C CNN
F 3 "~" H 4400 1600 60  0000 C CNN
	1    4400 1600
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-4DI_4RO C10
U 1 1 5390838F
P 4650 1600
F 0 "C10" H 4650 1700 40  0000 L CNN
F 1 "100nF" H 4656 1515 40  0000 L CNN
F 2 "~" H 4688 1450 30  0000 C CNN
F 3 "~" H 4650 1600 60  0000 C CNN
	1    4650 1600
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR032
U 1 1 53A9C744
P 3850 6150
F 0 "#PWR032" H 3850 6150 40  0001 C CNN
F 1 "DGND" H 3850 6080 40  0000 C CNN
F 2 "" H 3850 6150 60  0000 C CNN
F 3 "" H 3850 6150 60  0000 C CNN
	1    3850 6150
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR033
U 1 1 53A9CC4D
P 3850 5250
F 0 "#PWR033" H 3850 5250 40  0001 C CNN
F 1 "DGND" H 3850 5180 40  0000 C CNN
F 2 "" H 3850 5250 60  0000 C CNN
F 3 "" H 3850 5250 60  0000 C CNN
	1    3850 5250
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR034
U 1 1 53A9CE7D
P 3850 4500
F 0 "#PWR034" H 3850 4500 40  0001 C CNN
F 1 "DGND" H 3850 4430 40  0000 C CNN
F 2 "" H 3850 4500 60  0000 C CNN
F 3 "" H 3850 4500 60  0000 C CNN
	1    3850 4500
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 P3
U 1 1 53A9B36A
P 7100 650
F 0 "P3" V 7050 650 50  0000 C CNN
F 1 "3 PIN" V 7150 650 40  0000 C CNN
F 2 "~" H 7100 650 60  0000 C CNN
F 3 "~" H 7100 650 60  0000 C CNN
	1    7100 650 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 P4
U 1 1 53A9B379
P 8900 700
F 0 "P4" V 8850 700 50  0000 C CNN
F 1 "3 PIN" V 8950 700 40  0000 C CNN
F 2 "~" H 8900 700 60  0000 C CNN
F 3 "~" H 8900 700 60  0000 C CNN
	1    8900 700 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 P5
U 1 1 53A9B388
P 9200 700
F 0 "P5" V 9150 700 50  0000 C CNN
F 1 "3 PIN" V 9250 700 40  0000 C CNN
F 2 "~" H 9200 700 60  0000 C CNN
F 3 "~" H 9200 700 60  0000 C CNN
	1    9200 700 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 P6
U 1 1 53A9B397
P 9500 700
F 0 "P6" V 9450 700 50  0000 C CNN
F 1 "3 PIN" V 9550 700 40  0000 C CNN
F 2 "~" H 9500 700 60  0000 C CNN
F 3 "~" H 9500 700 60  0000 C CNN
	1    9500 700 
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 P7
U 1 1 53A9B3A6
P 9800 700
F 0 "P7" V 9750 700 50  0000 C CNN
F 1 "3 PIN" V 9850 700 40  0000 C CNN
F 2 "~" H 9800 700 60  0000 C CNN
F 3 "~" H 9800 700 60  0000 C CNN
	1    9800 700 
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR035
U 1 1 53AAFC58
P 6650 5250
F 0 "#PWR035" H 6650 5350 30  0001 C CNN
F 1 "VCC" H 6650 5350 30  0000 C CNN
F 2 "" H 6650 5250 60  0000 C CNN
F 3 "" H 6650 5250 60  0000 C CNN
	1    6650 5250
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR036
U 1 1 53AAFC68
P 7550 5250
F 0 "#PWR036" H 7550 5350 30  0001 C CNN
F 1 "VCC" H 7550 5350 30  0000 C CNN
F 2 "" H 7550 5250 60  0000 C CNN
F 3 "" H 7550 5250 60  0000 C CNN
	1    7550 5250
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR037
U 1 1 53AAFC6E
P 8500 5250
F 0 "#PWR037" H 8500 5350 30  0001 C CNN
F 1 "VCC" H 8500 5350 30  0000 C CNN
F 2 "" H 8500 5250 60  0000 C CNN
F 3 "" H 8500 5250 60  0000 C CNN
	1    8500 5250
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR038
U 1 1 53AAFC74
P 9550 5250
F 0 "#PWR038" H 9550 5350 30  0001 C CNN
F 1 "VCC" H 9550 5350 30  0000 C CNN
F 2 "" H 9550 5250 60  0000 C CNN
F 3 "" H 9550 5250 60  0000 C CNN
	1    9550 5250
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR039
U 1 1 53BC2F85
P 7600 1300
F 0 "#PWR039" H 7600 1300 40  0001 C CNN
F 1 "DGND" H 7600 1230 40  0000 C CNN
F 2 "" H 7600 1300 60  0000 C CNN
F 3 "" H 7600 1300 60  0000 C CNN
	1    7600 1300
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR040
U 1 1 53BC3314
P 7350 1550
F 0 "#PWR040" H 7350 1550 40  0001 C CNN
F 1 "DGND" H 7350 1480 40  0000 C CNN
F 2 "" H 7350 1550 60  0000 C CNN
F 3 "" H 7350 1550 60  0000 C CNN
	1    7350 1550
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR041
U 1 1 53BC331A
P 6800 1550
F 0 "#PWR041" H 6800 1550 40  0001 C CNN
F 1 "DGND" H 6800 1480 40  0000 C CNN
F 2 "" H 6800 1550 60  0000 C CNN
F 3 "" H 6800 1550 60  0000 C CNN
	1    6800 1550
	1    0    0    -1  
$EndComp
$Comp
L CPsmall C6
U 1 1 53C41E21
P 3300 1550
F 0 "C6" H 3325 1600 30  0000 L CNN
F 1 "47uF" H 3325 1475 30  0000 L CNN
F 2 "~" H 3300 1550 60  0000 C CNN
F 3 "~" H 3300 1550 60  0000 C CNN
	1    3300 1550
	1    0    0    -1  
$EndComp
$Comp
L CPsmall C5
U 1 1 53C42027
P 2500 1600
F 0 "C5" H 2525 1650 30  0000 L CNN
F 1 "4,7uF" H 2525 1525 30  0000 L CNN
F 2 "~" H 2500 1600 60  0000 C CNN
F 3 "~" H 2500 1600 60  0000 C CNN
	1    2500 1600
	1    0    0    -1  
$EndComp
$Comp
L CPsmall C16
U 1 1 53C42231
P 3600 1550
F 0 "C16" H 3625 1600 30  0000 L CNN
F 1 "4,7uF" H 3625 1475 30  0000 L CNN
F 2 "~" H 3600 1550 60  0000 C CNN
F 3 "~" H 3600 1550 60  0000 C CNN
	1    3600 1550
	1    0    0    -1  
$EndComp
$Comp
L DGND #PWR042
U 1 1 536FB6F5
P 1100 1550
F 0 "#PWR042" H 1100 1550 40  0001 C CNN
F 1 "DGND" H 1100 1480 40  0000 C CNN
F 2 "" H 1100 1550 60  0000 C CNN
F 3 "" H 1100 1550 60  0000 C CNN
	1    1100 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1550 1100 1300
Wire Wire Line
	3300 1000 3300 1450
Wire Wire Line
	2500 1050 2500 1500
Wire Wire Line
	2750 6550 2750 6650
Wire Wire Line
	2750 3600 2750 3650
Wire Wire Line
	1850 4150 1850 4250
Wire Wire Line
	1850 4350 1800 4350
Wire Wire Line
	1800 4350 1800 4550
Wire Wire Line
	1650 4150 1850 4150
Wire Wire Line
	1850 3950 1800 3950
Wire Wire Line
	1300 3950 1300 3900
Connection ~ 3300 1050
Connection ~ 2500 1050
Wire Wire Line
	3750 3950 5250 3950
Wire Wire Line
	3750 4050 5650 4050
Wire Wire Line
	3750 4150 6050 4150
Wire Wire Line
	3750 4250 6450 4250
Wire Wire Line
	4300 3400 4300 3400
Wire Wire Line
	4150 3500 4150 3500
Wire Wire Line
	4000 3600 4000 3600
Wire Wire Line
	3850 3700 3850 3700
Wire Wire Line
	4450 4650 3750 4650
Wire Wire Line
	3750 4750 4450 4750
Wire Wire Line
	4450 4850 3750 4850
Wire Wire Line
	4450 4950 3750 4950
Wire Wire Line
	4950 4950 6150 4950
Wire Wire Line
	4950 4850 7050 4850
Wire Wire Line
	4950 4750 8000 4750
Wire Wire Line
	4950 4650 8950 4650
Wire Wire Line
	1850 4650 1550 4650
Wire Wire Line
	1550 4650 1550 4450
Wire Wire Line
	1550 4450 1200 4450
Wire Wire Line
	1850 4850 1550 4850
Wire Wire Line
	1550 4850 1550 5050
Wire Wire Line
	1550 5050 1200 5050
Connection ~ 1300 4450
Connection ~ 1300 5050
Wire Wire Line
	800  5050 750  5050
Wire Wire Line
	750  5050 750  5100
Wire Wire Line
	800  4450 750  4450
Wire Wire Line
	750  4450 750  4500
Wire Wire Line
	4800 5850 4800 5750
Wire Wire Line
	4300 3900 4300 3950
Connection ~ 4300 3950
Wire Wire Line
	4150 4000 4150 4050
Connection ~ 4150 4050
Wire Wire Line
	4000 4100 4000 4150
Connection ~ 4000 4150
Wire Wire Line
	3850 4200 3850 4250
Connection ~ 3850 4250
Wire Wire Line
	5750 1000 5750 1050
Wire Wire Line
	4950 3800 4950 3550
Wire Wire Line
	5350 3550 5350 3800
Wire Wire Line
	5750 3800 5750 3550
Wire Wire Line
	6150 3550 6150 3800
Wire Wire Line
	5250 3950 5250 3550
Wire Wire Line
	5650 4050 5650 3550
Wire Wire Line
	6050 4150 6050 3550
Wire Wire Line
	6450 4250 6450 3550
Wire Wire Line
	5550 5850 5300 5850
Wire Wire Line
	4900 5850 4800 5850
Connection ~ 2250 1050
Wire Wire Line
	1550 1000 1550 1400
Connection ~ 1550 1050
Wire Wire Line
	1550 1050 2500 1050
Wire Wire Line
	2250 1050 2250 1500
Wire Wire Line
	1800 4550 1650 4550
Connection ~ 1800 4150
Wire Wire Line
	4400 6150 4400 6250
Wire Wire Line
	3750 5350 4400 5350
Wire Wire Line
	4400 5350 4400 6050
Wire Wire Line
	3750 5450 4300 5450
Wire Wire Line
	4300 5450 4300 6350
Wire Wire Line
	4300 6350 4400 6350
Wire Wire Line
	4400 6150 4200 6150
Wire Wire Line
	4200 6150 4200 5550
Wire Wire Line
	4200 5550 3750 5550
Wire Wire Line
	6150 4950 6150 5700
Wire Wire Line
	7050 4850 7050 5750
Wire Wire Line
	8000 4750 8000 5750
Wire Wire Line
	8950 4650 8950 5750
Wire Wire Line
	900  1300 900  1400
Wire Wire Line
	900  1800 900  1900
Wire Wire Line
	1550 1800 1550 2050
Wire Wire Line
	1550 2050 4650 2050
Connection ~ 1800 2050
Wire Wire Line
	2250 2050 2250 1700
Wire Wire Line
	3600 1650 3600 2050
Connection ~ 2250 2050
Wire Wire Line
	2900 1350 2900 2100
Connection ~ 2900 2050
Wire Wire Line
	2500 1700 2500 2050
Connection ~ 2500 2050
Wire Wire Line
	1800 1100 1800 1050
Connection ~ 1800 1050
Wire Wire Line
	1800 1600 1800 1650
Wire Wire Line
	5350 1000 5250 1000
Wire Wire Line
	5250 1000 5250 1250
Wire Wire Line
	5250 1750 5250 2300
Connection ~ 5250 1800
Wire Wire Line
	4950 2300 4950 2200
Wire Wire Line
	4950 2200 5150 2200
Connection ~ 5000 2200
Wire Wire Line
	5100 2450 5100 2200
Connection ~ 5100 2200
Wire Wire Line
	5350 2200 5550 2200
Wire Wire Line
	5750 2200 5950 2200
Wire Wire Line
	6150 2200 6350 2200
Wire Wire Line
	6300 2450 6300 2200
Connection ~ 6300 2200
Wire Wire Line
	6150 2300 6150 2200
Connection ~ 6200 2200
Wire Wire Line
	5900 2450 5900 2200
Connection ~ 5900 2200
Wire Wire Line
	5500 2450 5500 2200
Connection ~ 5500 2200
Wire Wire Line
	5350 2300 5350 2200
Connection ~ 5400 2200
Wire Wire Line
	5750 2300 5750 2200
Connection ~ 5800 2200
Wire Wire Line
	5650 1750 5650 2300
Wire Wire Line
	6050 1750 6050 2300
Wire Wire Line
	6450 1750 6450 2300
Wire Wire Line
	5450 1250 5450 1000
Wire Wire Line
	6050 1200 6050 1250
Wire Wire Line
	5550 1200 6050 1200
Wire Wire Line
	5550 1200 5550 1000
Wire Wire Line
	6450 1150 6450 1300
Wire Wire Line
	5650 1150 6450 1150
Wire Wire Line
	5650 1150 5650 1000
Wire Wire Line
	5750 1050 5950 1050
Wire Wire Line
	5950 1050 5950 800 
Connection ~ 6050 1800
Connection ~ 5650 1800
Wire Wire Line
	5000 1800 5250 1800
Wire Wire Line
	5400 1800 5650 1800
Wire Wire Line
	5800 1800 6050 1800
Wire Wire Line
	6200 1800 6450 1800
Wire Wire Line
	5200 6100 5400 6100
Wire Wire Line
	5450 1250 5650 1250
Connection ~ 5150 1800
Connection ~ 5550 1800
Connection ~ 5950 1800
Connection ~ 6350 1800
Wire Wire Line
	7000 1000 7000 1050
Wire Wire Line
	7000 1550 7000 1650
Wire Wire Line
	7200 1550 7200 1650
Wire Wire Line
	4300 3350 4300 3400
Wire Wire Line
	4150 3450 4150 3500
Wire Wire Line
	4000 3550 4000 3600
Wire Wire Line
	3850 3650 3850 3700
Wire Wire Line
	7100 1050 7350 1050
Wire Wire Line
	7100 1050 7100 1000
Wire Wire Line
	7200 1000 7600 1000
Wire Wire Line
	3300 1050 4650 1050
Wire Wire Line
	3600 1050 3600 1450
Wire Wire Line
	3900 2050 3900 1800
Connection ~ 3600 2050
Connection ~ 3600 1050
Wire Wire Line
	4150 2050 4150 1800
Connection ~ 3900 2050
Wire Wire Line
	4400 2050 4400 1800
Connection ~ 4150 2050
Wire Wire Line
	4650 2050 4650 1800
Connection ~ 4400 2050
Wire Wire Line
	9150 5400 9550 5400
Wire Wire Line
	9150 5400 9150 5500
Wire Wire Line
	9550 5250 9550 5500
Wire Wire Line
	9150 5900 9550 5900
Wire Wire Line
	9150 5900 9150 6050
Wire Wire Line
	8750 6050 8750 6300
Wire Wire Line
	8200 5350 8500 5350
Wire Wire Line
	8200 5350 8200 5450
Wire Wire Line
	8500 5250 8500 5450
Wire Wire Line
	8500 5850 8200 5850
Wire Wire Line
	8200 5850 8200 6050
Wire Wire Line
	7800 6050 7800 6300
Wire Wire Line
	7250 5350 7550 5350
Wire Wire Line
	7250 5350 7250 5450
Wire Wire Line
	7550 5250 7550 5450
Wire Wire Line
	7550 5850 7250 5850
Wire Wire Line
	7250 5850 7250 6050
Connection ~ 9550 5400
Connection ~ 8500 5350
Connection ~ 7550 5350
Wire Wire Line
	6650 5250 6650 5450
Wire Wire Line
	6650 5450 6350 5450
Wire Wire Line
	6650 5850 6350 5850
Wire Wire Line
	6350 5850 6350 6000
Wire Wire Line
	5950 6000 5950 6250
Wire Wire Line
	3750 5650 3850 5650
Wire Wire Line
	3850 5650 3850 6150
Wire Wire Line
	3750 5750 3850 5750
Connection ~ 3850 5750
Wire Wire Line
	3750 5850 3850 5850
Connection ~ 3850 5850
Wire Wire Line
	3750 5950 3850 5950
Connection ~ 3850 5950
Wire Wire Line
	3750 6050 3850 6050
Connection ~ 3850 6050
Wire Wire Line
	3750 5050 3850 5050
Wire Wire Line
	3850 5050 3850 5250
Wire Wire Line
	3750 5150 3850 5150
Connection ~ 3850 5150
Wire Wire Line
	3750 4350 3850 4350
Wire Wire Line
	3850 4350 3850 4500
Wire Wire Line
	3750 4450 3850 4450
Connection ~ 3850 4450
Wire Wire Line
	8100 1700 8100 1200
Wire Wire Line
	8100 1200 8900 1200
Wire Wire Line
	8900 1200 8900 1050
Wire Wire Line
	8300 2000 8300 1050
Wire Wire Line
	8300 1050 8800 1050
Wire Wire Line
	7900 2000 7900 1250
Wire Wire Line
	7900 1250 9000 1250
Wire Wire Line
	9000 1250 9000 1050
Wire Wire Line
	8900 1700 8900 1400
Wire Wire Line
	8900 1400 9200 1400
Wire Wire Line
	9200 1400 9200 1050
Wire Wire Line
	9100 2000 9100 1050
Wire Wire Line
	8700 2000 8700 1300
Wire Wire Line
	8700 1300 9300 1300
Wire Wire Line
	9300 1300 9300 1050
Wire Wire Line
	9700 1700 9700 1400
Wire Wire Line
	9700 1400 9500 1400
Wire Wire Line
	9500 1400 9500 1050
Wire Wire Line
	9500 2000 9500 1500
Wire Wire Line
	9500 1500 9600 1500
Wire Wire Line
	9600 1500 9600 1050
Wire Wire Line
	9900 2000 9900 1600
Wire Wire Line
	9900 1600 9400 1600
Wire Wire Line
	9400 1600 9400 1050
Wire Wire Line
	10500 1700 10500 1350
Wire Wire Line
	10500 1350 9800 1350
Wire Wire Line
	9800 1350 9800 1050
Wire Wire Line
	10300 2000 10300 1050
Wire Wire Line
	10300 1050 9900 1050
Wire Wire Line
	10700 2000 10700 1200
Wire Wire Line
	10700 1200 9700 1200
Wire Wire Line
	9700 1200 9700 1050
Wire Wire Line
	7600 1000 7600 1300
Wire Wire Line
	7350 1050 7350 1100
Connection ~ 7200 1050
Wire Wire Line
	7000 1050 6800 1050
Wire Wire Line
	6800 1050 6800 1100
Wire Wire Line
	7350 1500 7350 1550
Wire Wire Line
	6800 1500 6800 1550
Wire Wire Line
	5200 6300 5400 6300
Wire Wire Line
	4800 6550 4800 6700
Wire Wire Line
	3300 1650 3300 2050
Connection ~ 3300 2050
Wire Wire Line
	3900 1400 3900 1050
Connection ~ 3900 1050
Wire Wire Line
	4150 1400 4150 1050
Connection ~ 4150 1050
Wire Wire Line
	4400 1050 4400 1400
Wire Wire Line
	4650 1050 4650 1400
Connection ~ 4400 1050
Wire Wire Line
	1200 1350 1200 1550
$Comp
L GND-RESCUE-4DI_4RO #PWR043
U 1 1 538AF92B
P 1200 1550
F 0 "#PWR043" H 1200 1550 30  0001 C CNN
F 1 "GND" H 1200 1480 30  0001 C CNN
F 2 "" H 1200 1550 60  0000 C CNN
F 3 "" H 1200 1550 60  0000 C CNN
	1    1200 1550
	1    0    0    -1  
$EndComp
Connection ~ 6450 1800
Wire Wire Line
	6850 6050 6850 6300
$EndSCHEMATC
