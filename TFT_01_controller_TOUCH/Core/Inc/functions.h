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
#include "string.h"
#include "stdio.h"
#include "functions.h"

uint8_t Msg[32];

uint8_t system_init();
void showCurrentParameters(uint8_t temp_zew, uint8_t temp_wew, uint8_t Time[3], uint8_t water_lvl, uint8_t presure);
void showControlPanel();

#endif /* INC_FUNCTIONS_H_ */
