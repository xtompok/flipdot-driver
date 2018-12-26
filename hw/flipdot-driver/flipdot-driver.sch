EESchema Schematic File Version 4
EELAYER 26 0
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
L MCU_ST_STM32F1:STM32F103C8Tx U?
U 1 1 5C094D06
P 5500 3300
F 0 "U?" H 5450 1714 50  0000 C CNN
F 1 "STM32F103C8Tx" H 5450 1623 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 4900 1900 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 5500 3300 50  0001 C CNN
	1    5500 3300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x10_Top_Bottom J?
U 1 1 5C094EB5
P 2100 2850
F 0 "J?" H 2150 3467 50  0000 C CNN
F 1 "Conn_02x10_Top_Bottom" H 2150 3376 50  0000 C CNN
F 2 "" H 2100 2850 50  0001 C CNN
F 3 "~" H 2100 2850 50  0001 C CNN
	1    2100 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 2450 1650 2450
Wire Wire Line
	1900 2550 1650 2550
Wire Wire Line
	1900 2650 1650 2650
Wire Wire Line
	1900 2750 1650 2750
Wire Wire Line
	1900 2850 1650 2850
Wire Wire Line
	1900 2950 1650 2950
Wire Wire Line
	1900 3050 1650 3050
Wire Wire Line
	1900 3150 1650 3150
Wire Wire Line
	1900 3250 1650 3250
Wire Wire Line
	1900 3350 1650 3350
Wire Wire Line
	2400 2450 2650 2450
Wire Wire Line
	2400 2550 2650 2550
Wire Wire Line
	2400 2650 2650 2650
Wire Wire Line
	2400 2750 2650 2750
Wire Wire Line
	2400 2850 2650 2850
Wire Wire Line
	2400 2950 2650 2950
Wire Wire Line
	2400 3050 2650 3050
Wire Wire Line
	2400 3150 2650 3150
Wire Wire Line
	2400 3250 2650 3250
Wire Wire Line
	2400 3350 2650 3350
Text Label 1650 2450 0    50   ~ 0
ROW_7N
Text Label 1650 2550 0    50   ~ 0
ROW_6N
Text Label 1650 2650 0    50   ~ 0
ROW_5N
Text Label 1650 2750 0    50   ~ 0
ROW_4N
Text Label 1650 2850 0    50   ~ 0
ROW_3N
Text Label 1650 2950 0    50   ~ 0
ROW_2N
Text Label 1650 3050 0    50   ~ 0
ROW_1N
Text Label 1650 3150 0    50   ~ 0
ROW_7P
Text Label 1650 3250 0    50   ~ 0
ROW_6P
Text Label 1650 3350 0    50   ~ 0
ROW_5P
Text Label 2650 2450 2    50   ~ 0
ROW_4P
Text Label 2650 2550 2    50   ~ 0
ROW_3P
Text Label 2650 2650 2    50   ~ 0
ROW_2P
Text Label 2650 2750 2    50   ~ 0
ROW_1P
Text Label 2650 2850 2    50   ~ 0
P_DATA
Text Label 2650 2950 2    50   ~ 0
P_RET
Text Label 2650 3050 2    50   ~ 0
P_RST
Text Label 2650 3150 2    50   ~ 0
P_CLK
Text Label 2650 3250 2    50   ~ 0
P_VCC
Text Label 2650 3350 2    50   ~ 0
P_GND
$Comp
L power:+24V #PWR?
U 1 1 5C096117
P 2950 1750
F 0 "#PWR?" H 2950 1600 50  0001 C CNN
F 1 "+24V" H 2965 1923 50  0000 C CNN
F 2 "" H 2950 1750 50  0001 C CNN
F 3 "" H 2950 1750 50  0001 C CNN
	1    2950 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C09617E
P 2950 2000
F 0 "#PWR?" H 2950 1750 50  0001 C CNN
F 1 "GND" H 2955 1827 50  0000 C CNN
F 2 "" H 2950 2000 50  0001 C CNN
F 3 "" H 2950 2000 50  0001 C CNN
	1    2950 2000
	1    0    0    -1  
$EndComp
$Comp
L Transistor_Array:ULN2803A U?
U 1 1 5C09621F
P 5450 6000
F 0 "U?" H 5450 6567 50  0000 C CNN
F 1 "ULN2803A" H 5450 6476 50  0000 C CNN
F 2 "" H 5500 5350 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2803a.pdf" H 5550 5800 50  0001 C CNN
	1    5450 6000
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_GSD Q?
U 1 1 5C096451
P 1450 4600
F 0 "Q?" H 1656 4554 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 1656 4645 50  0000 L CNN
F 2 "" H 1650 4700 50  0001 C CNN
F 3 "~" H 1450 4600 50  0001 C CNN
	1    1450 4600
	0    1    1    0   
$EndComp
$Comp
L power:+24V #PWR?
U 1 1 5C096746
P 1100 4700
F 0 "#PWR?" H 1100 4550 50  0001 C CNN
F 1 "+24V" H 1115 4873 50  0000 C CNN
F 2 "" H 1100 4700 50  0001 C CNN
F 3 "" H 1100 4700 50  0001 C CNN
	1    1100 4700
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_ALT D?
U 1 1 5C096A2B
P 1850 4550
F 0 "D?" H 1850 4766 50  0000 C CNN
F 1 "D_ALT" H 1850 4675 50  0000 C CNN
F 2 "" H 1850 4550 50  0001 C CNN
F 3 "~" H 1850 4550 50  0001 C CNN
	1    1850 4550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1100 4700 1150 4700
Wire Wire Line
	1650 4700 1850 4700
Connection ~ 1850 4700
$Comp
L power:GND #PWR?
U 1 1 5C098539
P 2000 4400
F 0 "#PWR?" H 2000 4150 50  0001 C CNN
F 1 "GND" H 2005 4227 50  0000 C CNN
F 2 "" H 2000 4400 50  0001 C CNN
F 3 "" H 2000 4400 50  0001 C CNN
	1    2000 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4400 2000 4400
Text Label 2350 4700 2    50   ~ 0
ROW_1N
Wire Wire Line
	1850 4700 2350 4700
$Comp
L Device:R R?
U 1 1 5C099362
P 1150 4450
F 0 "R?" H 1220 4496 50  0000 L CNN
F 1 "R" H 1220 4405 50  0000 L CNN
F 2 "" V 1080 4450 50  0001 C CNN
F 3 "~" H 1150 4450 50  0001 C CNN
	1    1150 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 4600 1150 4700
Connection ~ 1150 4700
Wire Wire Line
	1150 4700 1250 4700
Wire Wire Line
	1150 4300 1450 4300
Wire Wire Line
	1450 4300 1450 4400
$Comp
L Transistor_Array:ULN2003A U?
U 1 1 5C099D02
P 2000 6050
F 0 "U?" H 2000 6717 50  0000 C CNN
F 1 "ULN2003A" H 2000 6626 50  0000 C CNN
F 2 "" H 2050 5500 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2003a.pdf" H 2100 5850 50  0001 C CNN
	1    2000 6050
	1    0    0    -1  
$EndComp
$EndSCHEMATC
