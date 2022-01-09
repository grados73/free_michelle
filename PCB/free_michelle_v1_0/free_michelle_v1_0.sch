EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "free_michelle"
Date "2022-01-09"
Rev "1.01"
Comp "grados73"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L grad73_library:BlackPill_STM32F4x1_grados73 TFT_CONTROLLER
U 1 1 61DB7364
P 2650 2500
F 0 "TFT_CONTROLLER" H 2650 3685 50  0000 C CNN
F 1 "BlackPill_STM32F4x1_grados73" H 2650 3594 50  0000 C CNN
F 2 "" H 3450 1500 50  0001 C CNN
F 3 "" H 3450 1500 50  0001 C CNN
	1    2650 2500
	1    0    0    -1  
$EndComp
$Comp
L grad73_library:BlackPill_STM32F4x1_grados73 GPIO_CONTROLLER
U 1 1 61DBA5F5
P 7400 2500
F 0 "GPIO_CONTROLLER" H 7400 3685 50  0000 C CNN
F 1 "BlackPill_STM32F4x1_grados73" H 7400 3594 50  0000 C CNN
F 2 "" H 8200 1500 50  0001 C CNN
F 3 "" H 8200 1500 50  0001 C CNN
	1    7400 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2800 4000 2800
Wire Wire Line
	4000 2800 4000 1000
Wire Wire Line
	4000 1000 8700 1000
Wire Wire Line
	8700 1000 8700 2700
Wire Wire Line
	8700 2700 8300 2700
Wire Wire Line
	3550 2700 3900 2700
Wire Wire Line
	3900 2700 3900 900 
Wire Wire Line
	3900 900  8800 900 
Wire Wire Line
	8800 900  8800 2800
Wire Wire Line
	8800 2800 8300 2800
$EndSCHEMATC
