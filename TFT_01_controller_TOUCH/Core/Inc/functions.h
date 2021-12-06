/*
 * functions.h
 *
 *  	Author: grados73
 *
 *
 */



#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include "main.h"
#include "TFT_ILI9341.h"
#include "GFX_Color.h"
#include "GFX_EnhancedFonts.h"
#include "EnhancedFonts/arialBlack_20ptFontInfo.h"
#include "EnhancedFonts/ArialBlack_28pts_bold.h"
#include "EnhancedFonts/arialBlack_11ptFontInfo.h"
#include "string.h"
#include "stdio.h"
#include "functions.h"
#include "uartdma.h"


//
// Define position string in showCurrentParameters funcion
//
#define PARAMETRY_STRING_POZ_X 47
#define PARAMETRY_STRING_POZ_Y 10
#define CZAS_POZ_X 20
#define CZAS_POZ_Y 50
#define TEMP_ZEW_POZ_X 20
#define TEMP_ZEW_POZ_Y 80
#define TEMP_WEW_POZ_X 20
#define TEMP_WEW_POZ_Y 110
#define POZ_WODY_POZ_X 20
#define POZ_WODY_POZ_Y 140
#define CISN_POZ_X 20
#define CISN_POZ_Y 170

//
// Define position string in showControlPanel funcion
//
#define PRZELACZNIKI_STRING_POZ_X 35
#define PRZELACZNIKI_STRING_POZ_Y 10
#define STRING_SWITCH_POZ_X 20
#define STRING_SWITCH_1_POZ_Y 60
#define STRING_SWITCH_2_POZ_Y 90
#define STRING_SWITCH_3_POZ_Y 120
#define STRING_SWITCH_4_POZ_Y 150

//
// Define position string in showLightsControlPanel funcion
//
#define SWIATLA_STRING_POZ_X 70
#define SWIATLA_STRING_POZ_Y 10
#define STRING_LIGHTS_POZ_X 20
#define STRING_LIGHTS_1_POZ_Y 60
#define STRING_LIGHTS_2_POZ_Y 90
#define STRING_LIGHTS_3_POZ_Y 120
#define STRING_LIGHTS_4_POZ_Y 150

//
// Define errata begin of string in connection to begin of button
//
#define STRING_ERRATA_X 3
#define STRING_ERRATA_Y 2

#define HEADER_UNDERLINE_POZ_Y 41
#define HEADER_UNDERLINE_COLOR ILI9341_ORANGE



uint8_t Msg[32];


//
// Prototype of functions
//
uint8_t system_init();
void showCurrentParameters(float temp_zew, float temp_wew, uint8_t * TimeTab, uint8_t water_lvl, float presure);
void showControlPanel();
void showLightsControlPanel();

#endif /* INC_FUNCTIONS_H_ */
