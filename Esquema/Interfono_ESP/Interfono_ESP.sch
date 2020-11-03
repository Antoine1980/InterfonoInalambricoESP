EESchema Schematic File Version 4
EELAYER 30 0
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
L ESP-01:ESP-01 U2
U 1 1 5FA1D174
P 6200 3750
F 0 "U2" H 6200 3600 50  0000 C CNN
F 1 "ESP-01" H 6200 3900 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Horizontal" H 6200 3600 50  0001 C CNN
F 3 "" H 6200 3600 50  0001 C CNN
	1    6200 3750
	1    0    0    -1  
$EndComp
$Comp
L ESP-01:KY-038 U1
U 1 1 5FA1E83C
P 4150 4400
F 0 "U1" H 4150 4250 50  0000 C CNN
F 1 "KY-038" H 4150 4400 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 4150 4400 50  0001 C CNN
F 3 "" H 4150 4400 50  0001 C CNN
	1    4150 4400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J1
U 1 1 5FA20957
P 7950 3950
F 0 "J1" H 7978 3926 50  0000 L CNN
F 1 "Conn_01x02_Female" H 7978 3835 50  0000 L CNN
F 2 "Connector_JST:JST_EH_B2B-EH-A_1x02_P2.50mm_Vertical" H 7950 3950 50  0001 C CNN
F 3 "~" H 7950 3950 50  0001 C CNN
	1    7950 3950
	1    0    0    -1  
$EndComp
NoConn ~ 4950 4550
$Comp
L Device:R R1
U 1 1 5FA224A3
P 6950 3700
F 0 "R1" V 6743 3700 50  0000 C CNN
F 1 "10K" V 6834 3700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P2.54mm_Vertical" V 6880 3700 50  0001 C CNN
F 3 "~" H 6950 3700 50  0001 C CNN
	1    6950 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	4950 4250 5500 4250
Wire Wire Line
	5500 4250 5500 3700
Wire Wire Line
	5500 3700 5850 3700
Wire Wire Line
	7750 3950 7500 3950
Wire Wire Line
	7500 3950 7500 3700
Wire Wire Line
	7500 3700 7100 3700
Wire Wire Line
	6800 3700 6500 3700
Connection ~ 7500 3950
Wire Wire Line
	7500 3950 7500 4350
Wire Wire Line
	7500 4350 4950 4350
Wire Wire Line
	6500 3950 7500 3950
Wire Wire Line
	7750 4050 7750 4450
Wire Wire Line
	7750 4450 5150 4450
Wire Wire Line
	5850 3550 3500 3550
Wire Wire Line
	3500 3550 3500 4850
Wire Wire Line
	3500 4850 5150 4850
Wire Wire Line
	5150 4850 5150 4450
Connection ~ 5150 4450
Wire Wire Line
	5150 4450 4950 4450
NoConn ~ 5850 3800
NoConn ~ 5850 3950
NoConn ~ 6500 3800
$EndSCHEMATC
