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
P 10240 2660
F 0 "GPIO_CONTROLLER" H 10240 3845 50  0000 C CNN
F 1 "BlackPill_STM32F4x1_grados73" H 10240 3754 50  0000 C CNN
F 2 "" H 11040 1660 50  0001 C CNN
F 3 "" H 11040 1660 50  0001 C CNN
	1    10240 2660
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2800 4000 2800
Wire Wire Line
	4000 2800 4000 1000
Wire Wire Line
	11540 2860 11140 2860
Wire Wire Line
	3550 2700 3900 2700
Wire Wire Line
	3900 2700 3900 900 
Wire Wire Line
	11640 2960 11140 2960
$Comp
L power:GND #PWR?
U 1 1 61DBA788
P 3130 7110
F 0 "#PWR?" H 3130 6860 50  0001 C CNN
F 1 "GND" H 3135 6937 50  0000 C CNN
F 2 "" H 3130 7110 50  0001 C CNN
F 3 "" H 3130 7110 50  0001 C CNN
	1    3130 7110
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61DBE35F
P 3230 5510
F 0 "#PWR?" H 3230 5360 50  0001 C CNN
F 1 "+3.3V" H 3245 5683 50  0000 C CNN
F 2 "" H 3230 5510 50  0001 C CNN
F 3 "" H 3230 5510 50  0001 C CNN
	1    3230 5510
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 61DC06F2
P 14000 1100
F 0 "#FLG?" H 14000 1175 50  0001 C CNN
F 1 "PWR_FLAG" H 14000 1273 50  0000 C CNN
F 2 "" H 14000 1100 50  0001 C CNN
F 3 "~" H 14000 1100 50  0001 C CNN
	1    14000 1100
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 61DC1287
P 14700 1100
F 0 "#FLG?" H 14700 1175 50  0001 C CNN
F 1 "PWR_FLAG" H 14700 1273 50  0000 C CNN
F 2 "" H 14700 1100 50  0001 C CNN
F 3 "~" H 14700 1100 50  0001 C CNN
	1    14700 1100
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 61DC1D57
P 15400 1100
F 0 "#FLG?" H 15400 1175 50  0001 C CNN
F 1 "PWR_FLAG" H 15400 1273 50  0000 C CNN
F 2 "" H 15400 1100 50  0001 C CNN
F 3 "~" H 15400 1100 50  0001 C CNN
	1    15400 1100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61DC2834
P 14000 1180
F 0 "#PWR?" H 14000 1030 50  0001 C CNN
F 1 "+3.3V" H 14015 1353 50  0000 C CNN
F 2 "" H 14000 1180 50  0001 C CNN
F 3 "" H 14000 1180 50  0001 C CNN
	1    14000 1180
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 61DC4ACB
P 14700 1180
F 0 "#PWR?" H 14700 1030 50  0001 C CNN
F 1 "+5V" H 14715 1353 50  0000 C CNN
F 2 "" H 14700 1180 50  0001 C CNN
F 3 "" H 14700 1180 50  0001 C CNN
	1    14700 1180
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61DC5D3E
P 15400 1180
F 0 "#PWR?" H 15400 930 50  0001 C CNN
F 1 "GND" H 15405 1007 50  0000 C CNN
F 2 "" H 15400 1180 50  0001 C CNN
F 3 "" H 15400 1180 50  0001 C CNN
	1    15400 1180
	1    0    0    -1  
$EndComp
Wire Wire Line
	14000 1100 14000 1180
Wire Wire Line
	14700 1100 14700 1180
Wire Wire Line
	15400 1100 15400 1180
Text GLabel 2560 5810 2    39   Input ~ 0
TFT_CS_PB12
Text GLabel 1590 1600 0    39   Input ~ 0
TFT_CS_PB12
Wire Wire Line
	1590 1600 1750 1600
Wire Wire Line
	2480 5810 2560 5810
Text GLabel 2560 5910 2    39   Input ~ 0
TFT_RST_PB13
Wire Wire Line
	2480 5910 2560 5910
Text GLabel 1590 1700 0    39   Input ~ 0
TFT_RST_PB13
Wire Wire Line
	1590 1700 1750 1700
Text GLabel 2560 6010 2    39   Input ~ 0
TFT_DC_PB14
Wire Wire Line
	2560 6010 2480 6010
Text GLabel 1590 1800 0    39   Input ~ 0
TFT_DC_PB14
Wire Wire Line
	1590 1800 1750 1800
Text GLabel 2560 6110 2    39   Input ~ 0
TFT_MOSI_PA7
Wire Wire Line
	2560 6110 2480 6110
Text GLabel 2560 6210 2    39   Input ~ 0
TFT_SCK_PA5
Wire Wire Line
	2560 6210 2480 6210
Text GLabel 4110 2300 2    39   Input ~ 0
TFT_MOSI_PA7
Wire Wire Line
	4110 2300 3550 2300
Text GLabel 4120 2500 2    39   Input ~ 0
TFT_SCK_PA5
Wire Wire Line
	4120 2500 3550 2500
Wire Wire Line
	2480 5610 3230 5610
Wire Wire Line
	3230 5610 3230 5510
Wire Wire Line
	2480 6310 3230 6310
Wire Wire Line
	3230 6310 3230 5610
Connection ~ 3230 5610
Text GLabel 2560 6410 2    39   Input ~ 0
TFT_MISO_PA6
Wire Wire Line
	2560 6410 2480 6410
Text GLabel 4110 2400 2    39   Input ~ 0
TFT_MISO_PA6
Wire Wire Line
	4110 2400 3550 2400
Text GLabel 2560 6510 2    39   Input ~ 0
T_TFT_SCK_PB3
Wire Wire Line
	2560 6510 2480 6510
Text GLabel 2560 6610 2    39   Input ~ 0
T_TFT_CS_PB10
Text GLabel 2560 6710 2    39   Input ~ 0
T_TFT_MOSI_PB5
Text GLabel 2560 6810 2    39   Input ~ 0
T_TFT_MISO_PB4
Text GLabel 2560 6910 2    39   Input ~ 0
T_TFT_IRQ_PA9
Wire Wire Line
	2560 6610 2480 6610
Wire Wire Line
	2560 6710 2480 6710
Wire Wire Line
	2560 6810 2480 6810
Wire Wire Line
	2560 6910 2480 6910
Text GLabel 1600 2600 0    39   Input ~ 0
T_TFT_SCK_PB3
Text GLabel 4100 1900 2    39   Input ~ 0
T_TFT_CS_PB10
Text GLabel 1600 2800 0    39   Input ~ 0
T_TFT_MOSI_PB5
Text GLabel 1600 2700 0    39   Input ~ 0
T_TFT_MISO_PB4
Text GLabel 1600 2100 0    39   Input ~ 0
T_TFT_IRQ_PA9
Wire Wire Line
	1600 2100 1750 2100
Wire Wire Line
	1600 2600 1750 2600
Wire Wire Line
	1600 2700 1750 2700
Wire Wire Line
	1600 2800 1750 2800
Wire Wire Line
	4100 1900 3550 1900
Wire Wire Line
	3130 7110 3130 5710
Wire Wire Line
	3130 5710 2480 5710
$Comp
L Timer_RTC:DS3231M U?
U 1 1 61DE62B5
P 5180 6140
F 0 "U?" H 5180 5651 50  0000 C CNN
F 1 "DS3231M" H 5180 5560 50  0000 C CNN
F 2 "Package_SO:SOIC-16W_7.5x10.3mm_P1.27mm" H 5180 5540 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231.pdf" H 5450 6190 50  0001 C CNN
	1    5180 6140
	1    0    0    -1  
$EndComp
NoConn ~ 5680 5940
Text GLabel 4340 5940 0    39   Input ~ 0
DS3231_SCL_PB6
Text GLabel 1600 2900 0    39   Input ~ 0
DS3231_SCL_PB6
Wire Wire Line
	1600 2900 1750 2900
Text GLabel 4340 6040 0    39   Input ~ 0
DS3231_SDA_PB7
Text GLabel 1600 3000 0    39   Input ~ 0
DS3231_SDA_PB7
Wire Wire Line
	1600 3000 1750 3000
Text GLabel 4120 2600 2    39   Input ~ 0
DS3231_IRQ_PA4
Wire Wire Line
	4120 2600 3550 2600
$Comp
L power:+3.3V #PWR?
U 1 1 61DEE9A8
P 5080 5300
F 0 "#PWR?" H 5080 5150 50  0001 C CNN
F 1 "+3.3V" H 5095 5473 50  0000 C CNN
F 2 "" H 5080 5300 50  0001 C CNN
F 3 "" H 5080 5300 50  0001 C CNN
	1    5080 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61DF0A08
P 5180 6970
F 0 "#PWR?" H 5180 6720 50  0001 C CNN
F 1 "GND" H 5185 6797 50  0000 C CNN
F 2 "" H 5180 6970 50  0001 C CNN
F 3 "" H 5180 6970 50  0001 C CNN
	1    5180 6970
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell CR2032
U 1 1 61DF2F26
P 6650 6120
F 0 "CR2032" H 6768 6216 50  0000 L CNN
F 1 "3V" H 6768 6125 50  0000 L CNN
F 2 "" V 6650 6180 50  0001 C CNN
F 3 "~" V 6650 6180 50  0001 C CNN
	1    6650 6120
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 5920 6650 5580
Wire Wire Line
	6650 5580 5180 5580
Wire Wire Line
	5180 5580 5180 5740
Wire Wire Line
	6650 6220 6650 6790
Wire Wire Line
	6650 6790 5180 6790
Connection ~ 5180 6790
Wire Wire Line
	5180 6790 5180 6540
Text GLabel 6020 6240 2    39   Input ~ 0
DS3231_IRQ_PA4
Wire Wire Line
	5680 6240 5850 6240
Wire Wire Line
	5080 5300 5080 5330
$Comp
L Device:R_Small R1
U 1 1 61DFE4B3
P 5850 5980
F 0 "R1" H 5909 6026 50  0000 L CNN
F 1 "10k" H 5909 5935 50  0000 L CNN
F 2 "" H 5850 5980 50  0001 C CNN
F 3 "~" H 5850 5980 50  0001 C CNN
	1    5850 5980
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 6080 5850 6240
Connection ~ 5850 6240
Wire Wire Line
	5850 6240 6020 6240
Wire Wire Line
	5850 5880 5850 5330
Wire Wire Line
	5850 5330 5080 5330
Connection ~ 5080 5330
Wire Wire Line
	5080 5330 5080 5380
Wire Wire Line
	5180 6790 5180 6890
Wire Wire Line
	7090 5330 7090 6890
Wire Wire Line
	7090 6890 5180 6890
Connection ~ 5180 6890
Wire Wire Line
	5180 6890 5180 6970
$Comp
L Device:C C1
U 1 1 61E06AF8
P 6520 5330
F 0 "C1" V 6772 5330 50  0000 C CNN
F 1 "100nF" V 6681 5330 50  0000 C CNN
F 2 "" H 6558 5180 50  0001 C CNN
F 3 "~" H 6520 5330 50  0001 C CNN
	1    6520 5330
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5850 5330 6370 5330
Connection ~ 5850 5330
Wire Wire Line
	6670 5330 7090 5330
Text GLabel 4530 6340 0    39   Input ~ 0
DS3231_RST_PB15
Wire Wire Line
	4530 6340 4680 6340
Text GLabel 1590 1900 0    39   Input ~ 0
DS3231_RST_PB15
Wire Wire Line
	1590 1900 1750 1900
Wire Wire Line
	11640 900  11640 2960
Wire Wire Line
	3900 900  11640 900 
Wire Wire Line
	11540 1000 11540 2860
Wire Wire Line
	4000 1000 11540 1000
$Comp
L Device:R_Small R2
U 1 1 61DB60FA
P 4410 5550
F 0 "R2" H 4351 5504 50  0000 R CNN
F 1 "4k7" H 4351 5595 50  0000 R CNN
F 2 "" H 4410 5550 50  0001 C CNN
F 3 "~" H 4410 5550 50  0001 C CNN
	1    4410 5550
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 61DC4213
P 4650 5540
F 0 "R3" H 4591 5494 50  0000 R CNN
F 1 "4k7" H 4591 5585 50  0000 R CNN
F 2 "" H 4650 5540 50  0001 C CNN
F 3 "~" H 4650 5540 50  0001 C CNN
	1    4650 5540
	-1   0    0    1   
$EndComp
Wire Wire Line
	4340 6040 4680 6040
Wire Wire Line
	4340 5940 4410 5940
Wire Wire Line
	4410 5650 4410 5940
Connection ~ 4410 5940
Wire Wire Line
	4410 5940 4650 5940
Wire Wire Line
	4410 5450 4410 5380
Wire Wire Line
	4410 5380 5080 5380
Connection ~ 5080 5380
Wire Wire Line
	5080 5380 5080 5420
Wire Wire Line
	4650 5440 4650 5420
Wire Wire Line
	4650 5420 5080 5420
Connection ~ 5080 5420
Wire Wire Line
	5080 5420 5080 5740
Wire Wire Line
	4650 5640 4650 5940
Connection ~ 4650 5940
Wire Wire Line
	4650 5940 4680 5940
$Comp
L power:GND #PWR?
U 1 1 61DD74E4
P 1700 8540
F 0 "#PWR?" H 1700 8290 50  0001 C CNN
F 1 "GND" H 1705 8367 50  0000 C CNN
F 2 "" H 1700 8540 50  0001 C CNN
F 3 "" H 1700 8540 50  0001 C CNN
	1    1700 8540
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 8280 1840 8280
Wire Wire Line
	1700 8280 1700 8410
Wire Wire Line
	2490 8080 2550 8080
Wire Wire Line
	2550 8080 2550 8410
Wire Wire Line
	2550 8410 1700 8410
Connection ~ 1700 8410
Wire Wire Line
	1700 8410 1700 8540
$Comp
L free_michelle_v1_0-cache:+3.3V #PWR?
U 1 1 61DBFF7C
P 2600 7810
F 0 "#PWR?" H 2600 7660 50  0001 C CNN
F 1 "+3.3V" H 2615 7983 50  0000 C CNN
F 2 "" H 2600 7810 50  0001 C CNN
F 3 "" H 2600 7810 50  0001 C CNN
	1    2600 7810
	1    0    0    -1  
$EndComp
Wire Wire Line
	2490 7980 2600 7980
Wire Wire Line
	2600 7980 2600 7890
NoConn ~ 1840 7980
NoConn ~ 1840 8080
NoConn ~ 1840 8180
Text GLabel 3380 8280 2    39   Input ~ 0
EEPROM_SDA_PB8
Text GLabel 1600 3100 0    39   Input ~ 0
EEPROM_SDA_PB8
Wire Wire Line
	1600 3100 1750 3100
Text GLabel 3380 8180 2    39   Input ~ 0
EEPROM_SCL_PA8
Text GLabel 1590 2000 0    39   Input ~ 0
EEPROM_SCL_PA8
Wire Wire Line
	1590 2000 1750 2000
Wire Wire Line
	2490 8180 2700 8180
Wire Wire Line
	2490 8280 2990 8280
$Comp
L Device:R_Small R4
U 1 1 61DDD494
P 2700 8010
F 0 "R4" H 2759 8056 50  0000 L CNN
F 1 "4K7" H 2759 7965 50  0000 L CNN
F 2 "" H 2700 8010 50  0001 C CNN
F 3 "~" H 2700 8010 50  0001 C CNN
	1    2700 8010
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R5
U 1 1 61DDDE8B
P 2990 8010
F 0 "R5" H 3049 8056 50  0000 L CNN
F 1 "4K7" H 3049 7965 50  0000 L CNN
F 2 "" H 2990 8010 50  0001 C CNN
F 3 "~" H 2990 8010 50  0001 C CNN
	1    2990 8010
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 8110 2700 8180
Connection ~ 2700 8180
Wire Wire Line
	2700 8180 3380 8180
Wire Wire Line
	2990 8110 2990 8280
Connection ~ 2990 8280
Wire Wire Line
	2990 8280 3380 8280
Wire Wire Line
	2700 7910 2700 7890
Wire Wire Line
	2700 7890 2600 7890
Connection ~ 2600 7890
Wire Wire Line
	2600 7890 2600 7840
Wire Wire Line
	2990 7910 2990 7840
Wire Wire Line
	2990 7840 2600 7840
Connection ~ 2600 7840
Wire Wire Line
	2600 7840 2600 7810
$Comp
L power:PWR_FLAG #FLG?
U 1 1 61DEC757
P 13300 1100
F 0 "#FLG?" H 13300 1175 50  0001 C CNN
F 1 "PWR_FLAG" H 13300 1273 50  0000 C CNN
F 2 "" H 13300 1100 50  0001 C CNN
F 3 "~" H 13300 1100 50  0001 C CNN
	1    13300 1100
	1    0    0    -1  
$EndComp
$Comp
L power:+9V #PWR?
U 1 1 61DEE2E8
P 13300 1180
F 0 "#PWR?" H 13300 1030 50  0001 C CNN
F 1 "+9V" H 13315 1353 50  0000 C CNN
F 2 "" H 13300 1180 50  0001 C CNN
F 3 "" H 13300 1180 50  0001 C CNN
	1    13300 1180
	-1   0    0    1   
$EndComp
Wire Wire Line
	13300 1180 13300 1100
$Comp
L Regulator_Linear:L7805 U?
U 1 1 61DF26E8
P 13020 1980
F 0 "U?" H 13020 2222 50  0000 C CNN
F 1 "L7805" H 13020 2131 50  0000 C CNN
F 2 "" H 13045 1830 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 13020 1930 50  0001 C CNN
	1    13020 1980
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61DF3DFA
P 13020 2520
F 0 "#PWR?" H 13020 2270 50  0001 C CNN
F 1 "GND" H 13025 2347 50  0000 C CNN
F 2 "" H 13020 2520 50  0001 C CNN
F 3 "" H 13020 2520 50  0001 C CNN
	1    13020 2520
	1    0    0    -1  
$EndComp
$Comp
L power:+9V #PWR?
U 1 1 61DF7AEA
P 12100 1810
F 0 "#PWR?" H 12100 1660 50  0001 C CNN
F 1 "+9V" H 12115 1983 50  0000 C CNN
F 2 "" H 12100 1810 50  0001 C CNN
F 3 "" H 12100 1810 50  0001 C CNN
	1    12100 1810
	1    0    0    -1  
$EndComp
Wire Wire Line
	12100 1810 12100 1980
$Comp
L power:+5V #PWR?
U 1 1 61DFBCEF
P 13870 1810
F 0 "#PWR?" H 13870 1660 50  0001 C CNN
F 1 "+5V" H 13885 1983 50  0000 C CNN
F 2 "" H 13870 1810 50  0001 C CNN
F 3 "" H 13870 1810 50  0001 C CNN
	1    13870 1810
	1    0    0    -1  
$EndComp
Wire Wire Line
	13870 1810 13870 1980
Wire Wire Line
	13870 1980 13480 1980
$Comp
L Device:CP_Small C?
U 1 1 61E00529
P 12100 2120
F 0 "C?" H 12188 2166 50  0000 L CNN
F 1 "47uF" H 12188 2075 50  0000 L CNN
F 2 "" H 12100 2120 50  0001 C CNN
F 3 "~" H 12100 2120 50  0001 C CNN
	1    12100 2120
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61E02529
P 12460 2120
F 0 "C?" H 12552 2166 50  0000 L CNN
F 1 "100nF" H 12552 2075 50  0000 L CNN
F 2 "" H 12460 2120 50  0001 C CNN
F 3 "~" H 12460 2120 50  0001 C CNN
	1    12460 2120
	1    0    0    -1  
$EndComp
Wire Wire Line
	12100 1980 12460 1980
Wire Wire Line
	12100 2020 12100 1980
Connection ~ 12100 1980
Wire Wire Line
	12460 2020 12460 1980
Connection ~ 12460 1980
Wire Wire Line
	12460 1980 12720 1980
Wire Wire Line
	12460 2220 12460 2420
Wire Wire Line
	12460 2420 13020 2420
Connection ~ 13020 2420
$Comp
L Device:C_Small C?
U 1 1 61E310BD
P 13480 2120
F 0 "C?" H 13572 2166 50  0000 L CNN
F 1 "100nF" H 13572 2075 50  0000 L CNN
F 2 "" H 13480 2120 50  0001 C CNN
F 3 "~" H 13480 2120 50  0001 C CNN
	1    13480 2120
	1    0    0    -1  
$EndComp
Wire Wire Line
	13480 2020 13480 1980
Connection ~ 13480 1980
Wire Wire Line
	13480 1980 13320 1980
$Comp
L grad73_library:LD1117V33 U?
U 1 1 61E4A9E3
P 15000 1980
F 0 "U?" H 15000 2222 50  0000 C CNN
F 1 "LD1117V33" H 15000 2131 50  0000 C CNN
F 2 "" H 15025 1830 50  0001 L CIN
F 3 "" H 15000 1930 50  0001 C CNN
	1    15000 1980
	1    0    0    -1  
$EndComp
$Comp
L free_michelle_v1_0-cache:grad73_library_24AA01 U?
U 1 1 61E51F54
P 2140 7830
F 0 "U?" H 2165 7945 50  0000 C CNN
F 1 "EEPROM_24AA01" H 2165 7854 50  0000 C CNN
F 2 "" H 2140 7830 50  0001 C CNN
F 3 "" H 2140 7830 50  0001 C CNN
	1    2140 7830
	1    0    0    -1  
$EndComp
$Comp
L grad73_library:TFT_320x240_ILI9341 D?
U 1 1 61E56922
P 2330 5410
F 0 "D?" H 2063 5475 50  0000 C CNN
F 1 "TFT_320x240_ILI9341" H 2063 5384 50  0000 C CNN
F 2 "" H 2330 5410 50  0001 C CNN
F 3 "" H 2330 5410 50  0001 C CNN
	1    2330 5410
	1    0    0    -1  
$EndComp
$Comp
L power:+9V #PWR?
U 1 1 61E6D4C2
P 14060 1810
F 0 "#PWR?" H 14060 1660 50  0001 C CNN
F 1 "+9V" H 14075 1983 50  0000 C CNN
F 2 "" H 14060 1810 50  0001 C CNN
F 3 "" H 14060 1810 50  0001 C CNN
	1    14060 1810
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61E6EB78
P 15000 2510
F 0 "#PWR?" H 15000 2260 50  0001 C CNN
F 1 "GND" H 15005 2337 50  0000 C CNN
F 2 "" H 15000 2510 50  0001 C CNN
F 3 "" H 15000 2510 50  0001 C CNN
	1    15000 2510
	1    0    0    -1  
$EndComp
Wire Wire Line
	14060 1810 14060 1980
Wire Wire Line
	14060 1980 14460 1980
Wire Wire Line
	15300 1980 15540 1980
Wire Wire Line
	15880 1980 15880 1810
Wire Wire Line
	15000 2510 15000 2400
$Comp
L Device:CP_Small C?
U 1 1 61E7B8D4
P 14060 2140
F 0 "C?" H 14148 2186 50  0000 L CNN
F 1 "47uF" H 14148 2095 50  0000 L CNN
F 2 "" H 14060 2140 50  0001 C CNN
F 3 "~" H 14060 2140 50  0001 C CNN
	1    14060 2140
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61E7BEE4
P 14460 2140
F 0 "C?" H 14552 2186 50  0000 L CNN
F 1 "100nF" H 14552 2095 50  0000 L CNN
F 2 "" H 14460 2140 50  0001 C CNN
F 3 "~" H 14460 2140 50  0001 C CNN
	1    14460 2140
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 61E7C508
P 15540 2150
F 0 "C?" H 15632 2196 50  0000 L CNN
F 1 "100nF" H 15632 2105 50  0000 L CNN
F 2 "" H 15540 2150 50  0001 C CNN
F 3 "~" H 15540 2150 50  0001 C CNN
	1    15540 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	13020 2420 13020 2520
Wire Wire Line
	12100 2220 12100 2420
Wire Wire Line
	12100 2420 12460 2420
Connection ~ 12460 2420
Wire Wire Line
	14060 2040 14060 1980
Connection ~ 14060 1980
Wire Wire Line
	14060 2240 14060 2400
Wire Wire Line
	14060 2400 14460 2400
Connection ~ 15000 2400
Wire Wire Line
	15000 2400 15000 2280
Wire Wire Line
	14460 2240 14460 2400
Connection ~ 14460 2400
Wire Wire Line
	14460 2400 15000 2400
Wire Wire Line
	14460 2040 14460 1980
Connection ~ 14460 1980
Wire Wire Line
	14460 1980 14700 1980
Wire Wire Line
	15000 2400 15540 2400
Wire Wire Line
	15540 2400 15540 2250
Wire Wire Line
	15540 2050 15540 1980
Connection ~ 15540 1980
Wire Wire Line
	15540 1980 15880 1980
Wire Wire Line
	13020 2280 13020 2420
Wire Wire Line
	13480 2420 13020 2420
Wire Wire Line
	13480 2220 13480 2420
$Comp
L power:GND #PWR?
U 1 1 61EABE5B
P 680 4130
F 0 "#PWR?" H 680 3880 50  0001 C CNN
F 1 "GND" H 685 3957 50  0000 C CNN
F 2 "" H 680 4130 50  0001 C CNN
F 3 "" H 680 4130 50  0001 C CNN
	1    680  4130
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3400 680  3400
Wire Wire Line
	680  3400 680  900 
Wire Wire Line
	680  900  3810 900 
Wire Wire Line
	3810 900  3810 1700
Wire Wire Line
	3810 1700 3550 1700
Connection ~ 680  3400
$Comp
L power:GND #PWR?
U 1 1 61EB7012
P 8700 4260
F 0 "#PWR?" H 8700 4010 50  0001 C CNN
F 1 "GND" H 8705 4087 50  0000 C CNN
F 2 "" H 8700 4260 50  0001 C CNN
F 3 "" H 8700 4260 50  0001 C CNN
	1    8700 4260
	1    0    0    -1  
$EndComp
Wire Wire Line
	9340 3560 8700 3560
Wire Wire Line
	8700 3560 8700 1100
Wire Wire Line
	8700 1100 11420 1100
Wire Wire Line
	11420 1100 11420 1860
Wire Wire Line
	11420 1860 11140 1860
Connection ~ 8700 3560
$Comp
L power:+3.3V #PWR?
U 1 1 61EC816A
P 15880 1810
F 0 "#PWR?" H 15880 1660 50  0001 C CNN
F 1 "+3.3V" H 15895 1983 50  0000 C CNN
F 2 "" H 15880 1810 50  0001 C CNN
F 3 "" H 15880 1810 50  0001 C CNN
	1    15880 1810
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61EC910A
P 800 1130
F 0 "#PWR?" H 800 980 50  0001 C CNN
F 1 "+3.3V" H 815 1303 50  0000 C CNN
F 2 "" H 800 1130 50  0001 C CNN
F 3 "" H 800 1130 50  0001 C CNN
	1    800  1130
	1    0    0    -1  
$EndComp
Wire Wire Line
	680  3400 680  4100
Wire Wire Line
	2750 3800 2750 4100
Wire Wire Line
	2750 4100 680  4100
Connection ~ 680  4100
Wire Wire Line
	680  4100 680  4130
Wire Wire Line
	2450 4000 800  4000
Wire Wire Line
	800  4000 800  3500
Wire Wire Line
	1750 3500 800  3500
Connection ~ 800  3500
Wire Wire Line
	800  3500 800  1200
Wire Wire Line
	3550 1800 3710 1800
Wire Wire Line
	3710 1800 3710 1200
Wire Wire Line
	3710 1200 800  1200
Connection ~ 800  1200
Wire Wire Line
	800  1200 800  1130
Wire Wire Line
	8700 3560 8700 4200
Wire Wire Line
	10340 3960 10340 4200
Wire Wire Line
	10340 4200 8700 4200
Connection ~ 8700 4200
Wire Wire Line
	8700 4200 8700 4260
$Comp
L power:+3.3V #PWR?
U 1 1 61F05942
P 8810 1330
F 0 "#PWR?" H 8810 1180 50  0001 C CNN
F 1 "+3.3V" H 8825 1503 50  0000 C CNN
F 2 "" H 8810 1330 50  0001 C CNN
F 3 "" H 8810 1330 50  0001 C CNN
	1    8810 1330
	1    0    0    -1  
$EndComp
Wire Wire Line
	8810 1330 8810 1400
Wire Wire Line
	8810 4100 10040 4100
Wire Wire Line
	10040 4100 10040 3960
Wire Wire Line
	9340 3660 8810 3660
Connection ~ 8810 3660
Wire Wire Line
	8810 3660 8810 4100
Wire Wire Line
	11140 1960 11320 1960
Wire Wire Line
	11320 1960 11320 1400
Wire Wire Line
	11320 1400 8810 1400
Connection ~ 8810 1400
Wire Wire Line
	8810 1400 8810 3660
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 61F2C264
P 2550 4600
F 0 "J?" V 2704 4312 50  0000 R CNN
F 1 "SW" V 2613 4312 50  0000 R CNN
F 2 "" H 2550 4600 50  0001 C CNN
F 3 "~" H 2550 4600 50  0001 C CNN
	1    2550 4600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 3800 2450 4000
Connection ~ 2450 4000
Wire Wire Line
	2450 4000 2450 4400
Wire Wire Line
	2550 3800 2550 4400
Wire Wire Line
	2650 3800 2650 4400
Wire Wire Line
	2750 4100 2750 4400
Connection ~ 2750 4100
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 61F4F876
P 10140 4650
F 0 "J?" V 10294 4362 50  0000 R CNN
F 1 "SW" V 10203 4362 50  0000 R CNN
F 2 "" H 10140 4650 50  0001 C CNN
F 3 "~" H 10140 4650 50  0001 C CNN
	1    10140 4650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10040 4100 10040 4450
Connection ~ 10040 4100
Wire Wire Line
	10140 3960 10140 4450
Wire Wire Line
	10240 3960 10240 4450
Wire Wire Line
	10340 4200 10340 4450
Connection ~ 10340 4200
$Comp
L grad73_library:BMP280 U?
U 1 1 61F880B9
P 9150 5490
F 0 "U?" H 9133 5555 50  0000 C CNN
F 1 "BMP280" H 9133 5464 50  0000 C CNN
F 2 "" H 9150 5440 50  0001 C CNN
F 3 "" H 9150 5440 50  0001 C CNN
	1    9150 5490
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 61F9233B
P 9500 5500
F 0 "#PWR?" H 9500 5350 50  0001 C CNN
F 1 "+3.3V" H 9515 5673 50  0000 C CNN
F 2 "" H 9500 5500 50  0001 C CNN
F 3 "" H 9500 5500 50  0001 C CNN
	1    9500 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 5690 9500 5690
Wire Wire Line
	9500 5690 9500 5500
$Comp
L power:GND #PWR?
U 1 1 61F9BBC2
P 9500 6400
F 0 "#PWR?" H 9500 6150 50  0001 C CNN
F 1 "GND" H 9505 6227 50  0000 C CNN
F 2 "" H 9500 6400 50  0001 C CNN
F 3 "" H 9500 6400 50  0001 C CNN
	1    9500 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 5790 9500 5790
Wire Wire Line
	9500 5790 9500 6400
Text GLabel 9600 5890 2    39   Input ~ 0
BMP_SCL_PB8
Text GLabel 9600 5990 2    39   Input ~ 0
BMP_SDA_PB9
Wire Wire Line
	9600 5890 9300 5890
Wire Wire Line
	9600 5990 9300 5990
Text GLabel 8540 3260 0    39   Input ~ 0
BMP_SCL_PB8
Wire Wire Line
	8540 3260 9340 3260
Text GLabel 8540 3360 0    39   Input ~ 0
BMP_SDA_PB9
Wire Wire Line
	8540 3360 9340 3360
NoConn ~ 9300 6090
NoConn ~ 9300 6190
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 61FEF438
P 12700 6000
F 0 "J?" H 12808 6281 50  0000 C CNN
F 1 "WS2812b" H 12808 6190 50  0000 C CNN
F 2 "" H 12700 6000 50  0001 C CNN
F 3 "~" H 12700 6000 50  0001 C CNN
	1    12700 6000
	-1   0    0    1   
$EndComp
$Comp
L power:+5VP #PWR?
U 1 1 61FF0CBC
P 12600 1180
F 0 "#PWR?" H 12600 1030 50  0001 C CNN
F 1 "+5VP" H 12615 1353 50  0000 C CNN
F 2 "" H 12600 1180 50  0001 C CNN
F 3 "" H 12600 1180 50  0001 C CNN
	1    12600 1180
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 61FF3126
P 12600 1100
F 0 "#FLG?" H 12600 1175 50  0001 C CNN
F 1 "PWR_FLAG" H 12600 1273 50  0000 C CNN
F 2 "" H 12600 1100 50  0001 C CNN
F 3 "~" H 12600 1100 50  0001 C CNN
	1    12600 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	12600 1100 12600 1180
Text Notes 12390 780  0    28   ~ 0
NAPIĘCIE ZASILANIA
Text Notes 12340 830  0    28   ~ 0
O WYSOKIEJ WYDAJNOŚCI
Text Notes 12490 880  0    28   ~ 0
PRĄDOWEJ
Text Notes 13170 840  0    28   ~ 0
WEJŚCIOWE
Text Notes 13070 780  0    28   ~ 0
NAPIĘCIE ZASILANIA
Text Notes 13790 780  0    28   ~ 0
NAPIĘCIE ZASILANIA
Text Notes 13870 840  0    28   ~ 0
LOGIKI 3,3V
Text Notes 14490 780  0    28   ~ 0
NAPIĘCIE ZASILANIA
Text Notes 14600 840  0    28   ~ 0
LOGIKI 5V
$Comp
L power:+5VP #PWR?
U 1 1 620A9A5F
P 12240 5790
F 0 "#PWR?" H 12240 5640 50  0001 C CNN
F 1 "+5VP" H 12255 5963 50  0000 C CNN
F 2 "" H 12240 5790 50  0001 C CNN
F 3 "" H 12240 5790 50  0001 C CNN
	1    12240 5790
	1    0    0    -1  
$EndComp
Wire Wire Line
	12500 6100 12240 6100
Wire Wire Line
	12240 6100 12240 6190
$Comp
L power:GND #PWR?
U 1 1 620B4DAE
P 12240 6190
F 0 "#PWR?" H 12240 5940 50  0001 C CNN
F 1 "GND" H 12245 6017 50  0000 C CNN
F 2 "" H 12240 6190 50  0001 C CNN
F 3 "" H 12240 6190 50  0001 C CNN
	1    12240 6190
	1    0    0    -1  
$EndComp
Wire Wire Line
	12240 5790 12240 5900
Wire Wire Line
	12240 5900 12500 5900
$Comp
L Transistor_FET:BSS138 Q?
U 1 1 620C023B
P 11600 5900
F 0 "Q?" V 11849 5900 50  0000 C CNN
F 1 "BSS138" V 11940 5900 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 11800 5825 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/BSS138-D.PDF" H 11600 5900 50  0001 L CNN
	1    11600 5900
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 620FDC1E
P 11900 5500
F 0 "R?" V 11704 5500 50  0000 C CNN
F 1 "4k7" V 11795 5500 50  0000 C CNN
F 2 "" H 11900 5500 50  0001 C CNN
F 3 "~" H 11900 5500 50  0001 C CNN
	1    11900 5500
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 621092CD
P 11900 5300
F 0 "#PWR?" H 11900 5150 50  0001 C CNN
F 1 "+5V" H 11915 5473 50  0000 C CNN
F 2 "" H 11900 5300 50  0001 C CNN
F 3 "" H 11900 5300 50  0001 C CNN
	1    11900 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	11800 6000 11900 6000
Connection ~ 11900 6000
Wire Wire Line
	11900 6000 12500 6000
Wire Wire Line
	11900 5400 11900 5300
Text GLabel 11050 6000 0    39   Input ~ 0
WS2812b_PA9
Wire Wire Line
	11050 6000 11200 6000
$Comp
L Device:R_Small R?
U 1 1 62212931
P 11200 5800
F 0 "R?" V 11004 5800 50  0000 C CNN
F 1 "4k7" V 11095 5800 50  0000 C CNN
F 2 "" H 11200 5800 50  0001 C CNN
F 3 "~" H 11200 5800 50  0001 C CNN
	1    11200 5800
	-1   0    0    1   
$EndComp
Wire Wire Line
	11200 5900 11200 6000
Connection ~ 11200 6000
Wire Wire Line
	11200 6000 11400 6000
$Comp
L power:+3.3V #PWR?
U 1 1 6221DC88
P 11600 5300
F 0 "#PWR?" H 11600 5150 50  0001 C CNN
F 1 "+3.3V" H 11615 5473 50  0000 C CNN
F 2 "" H 11600 5300 50  0001 C CNN
F 3 "" H 11600 5300 50  0001 C CNN
	1    11600 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6225EEF6
P 11600 5500
F 0 "R?" V 11404 5500 50  0000 C CNN
F 1 "4k7" V 11495 5500 50  0000 C CNN
F 2 "" H 11600 5500 50  0001 C CNN
F 3 "~" H 11600 5500 50  0001 C CNN
	1    11600 5500
	-1   0    0    1   
$EndComp
Wire Wire Line
	11600 5700 11600 5600
Wire Wire Line
	11600 5400 11600 5340
Wire Wire Line
	11200 5340 11600 5340
Wire Wire Line
	11200 5340 11200 5700
Connection ~ 11600 5340
Wire Wire Line
	11600 5340 11600 5300
Wire Wire Line
	11900 5600 11900 6000
$EndSCHEMATC
