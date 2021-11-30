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

uint8_t Msg[32];

uint8_t system_init();
void showCurrentParameters(float temp_zew, float temp_wew, uint8_t * TimeTab, uint8_t water_lvl, float presure);
void showControlPanel();
void showLightsControlPanel();

#endif /* INC_FUNCTIONS_H_ */
