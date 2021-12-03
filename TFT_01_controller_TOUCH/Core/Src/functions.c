/*
 * functions.c
 *
 *  	Author: grados73
 *
 *	TODO! " zamienić wszytskie delaye i dodać tu inicjalizację !!!
 *
 */

#include "functions.h"
#include "logo.h"
#include "parser.h"
#include "menuTFT.h"

extern float CTemp;
extern float CPres;
extern float CTempWew;
extern uint8_t CWaterLvl ;
extern uint8_t Time[3];


uint8_t system_init(){
	  ILI9341_ClearDisplay(ILI9341_LIGHTGREY);
	  ILI9341_DrawImage(40, 50, logo, 240, 140);
//	  GFX_Image(40, 50, logo, 240, 140); //usunieta wolniejsza wersja rysowania

	  HAL_Delay(200); // !!!! TODO

	  EF_SetFont(&arialBlack_20ptFontInfo);
	  uint8_t Len = sprintf((char*)Msg, "Inicjalizacja...");
	  EF_PutString(Msg, 60, 20, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_BLACK);
	  Len++;
	  GFX_DrawRoundRectangle(60, 200, 20, 20, 5, ILI9341_RED);
	  GFX_DrawRoundRectangle(90, 200, 20, 20, 5, ILI9341_RED);
	  GFX_DrawRoundRectangle(120, 200, 20, 20, 5, ILI9341_RED);
	  GFX_DrawRoundRectangle(150, 200, 20, 20, 5, ILI9341_RED);
	  GFX_DrawRoundRectangle(180, 200, 20, 20, 5, ILI9341_RED);
	  GFX_DrawRoundRectangle(210, 200, 20, 20, 5, ILI9341_RED);
	  GFX_DrawRoundRectangle(240, 200, 20, 20, 5, ILI9341_RED);

	  HAL_Delay(100); // !!!! TODO
	  GFX_DrawFillRoundRectangle(60, 200, 20, 20, 5, ILI9341_GREEN);
	  HAL_Delay(100); // !!!! TODO
	  GFX_DrawFillRoundRectangle(90, 200, 20, 20, 5, ILI9341_GREEN);
	  HAL_Delay(100); // !!!! TODO
	  GFX_DrawFillRoundRectangle(120, 200, 20, 20, 5, ILI9341_GREEN);
	  HAL_Delay(100); // !!!! TODO
	  GFX_DrawFillRoundRectangle(150, 200, 20, 20, 5, ILI9341_GREEN);
	  HAL_Delay(100); // !!!! TODO
	  GFX_DrawFillRoundRectangle(180, 200, 20, 20, 5, ILI9341_GREEN);
	  HAL_Delay(100); // !!!! TODO
	  GFX_DrawFillRoundRectangle(210, 200, 20, 20, 5, ILI9341_GREEN);
	  HAL_Delay(100); // !!!! TODO
	  GFX_DrawFillRoundRectangle(240, 200, 20, 20, 5, ILI9341_GREEN);
	  HAL_Delay(200); // !!!! TODO





	  return 1; // TODO! DODAĆ SPRAWDZENIE POPRAWNOŚCI INICJALIZACJI I ZWRÓCENIE 1 / 0
}

void showCurrentParameters(float temp_zew, float temp_wew, uint8_t * TimeTab, uint8_t water_lvl, float presure)
{
		// TODO dodac kreske pod naglowkiem
	  ILI9341_ClearDisplay(ILI9341_LIGHTGREY);
	  EF_SetFont(&arialBlack_20ptFontInfo);

	  uint8_t Len = sprintf((char*)Msg, "-=PARAMETRY=-");
	  EF_PutString(Msg, PARAMETRY_STRING_POZ_X, PARAMETRY_STRING_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "Czas: %d : %d : %d", Time[0], Time[1], Time[2]);
	  EF_PutString(Msg, CZAS_POZ_X, CZAS_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "Temp. zewn: %.2f`C", CTemp);
	  EF_PutString(Msg, TEMP_ZEW_POZ_X, TEMP_ZEW_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "Temp. wewn: %.2f`C", CTempWew);
	  EF_PutString(Msg, TEMP_WEW_POZ_X, TEMP_WEW_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "Poz. wody: %d", CWaterLvl);
	  EF_PutString(Msg, POZ_WODY_POZ_X, POZ_WODY_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "Ciśnienie: %.1fhPa", CPres);
	  EF_PutString(Msg, CISN_POZ_X, CISN_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);


	  EF_SetFont(&arial_11ptFontInfo);
	  GFX_DrawFillRoundRectangle(RIGHT_BUTTON_X, RIGHT_BUTTON_Y, RIGHT_BUTTON_W, RIGHT_BUTTON_H, RIGHT_LEFT_BUTTON_R,  ILI9341_GREEN);
	  Len = sprintf((char*)Msg, "CONTROL=>");
	  EF_PutString(Msg, (RIGHT_BUTTON_X + 3), (RIGHT_BUTTON_Y + 2), ILI9341_BLACK, BG_TRANSPARENT, ILI9341_GREEN);

	  GFX_DrawFillRoundRectangle(LEFT_BUTTON_X, LEFT_BUTTON_Y, LEFT_BUTTON_W, LEFT_BUTTON_H, RIGHT_LEFT_BUTTON_R,  ILI9341_GREEN);
	  Len = sprintf((char*)Msg, "<=LIGHTS");
	  EF_PutString(Msg, (LEFT_BUTTON_X + 10), (LEFT_BUTTON_Y + 2), ILI9341_BLACK, BG_TRANSPARENT, ILI9341_GREEN);
	  EF_SetFont(&arialBlack_20ptFontInfo);

	  Len++;
}

void showControlPanel()
{

	  ILI9341_ClearDisplay(ILI9341_LIGHTGREY);
	  EF_SetFont(&arialBlack_20ptFontInfo);

	  uint8_t Len = sprintf((char*)Msg, "-=PRZEŁĄCZNIKI=-");
	  EF_PutString(Msg, PRZELACZNIKI_STRING_POZ_X, PRZELACZNIKI_STRING_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "PRZEŁĄCZNIK 1:");
	  EF_PutString(Msg, STRING_SWITCH_POZ_X, STRING_SWITCH_1_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "PRZEŁĄCZNIK 2:");
	  EF_PutString(Msg, STRING_SWITCH_POZ_X, STRING_SWITCH_2_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "PRZEŁĄCZNIK 3:");
	  EF_PutString(Msg, STRING_SWITCH_POZ_X, STRING_SWITCH_3_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "PRZEŁĄCZNIK 4:");
	  EF_PutString(Msg, STRING_SWITCH_POZ_X, STRING_SWITCH_4_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  EF_SetFont(&arial_11ptFontInfo);
	  GFX_DrawFillRoundRectangle(RIGHT_BUTTON_X, RIGHT_BUTTON_Y, RIGHT_BUTTON_W, RIGHT_BUTTON_H, RIGHT_LEFT_BUTTON_R,  ILI9341_GREEN);
	  Len = sprintf((char*)Msg, "LIGHTS=>");
	  EF_PutString(Msg, (RIGHT_BUTTON_X + 3), (RIGHT_BUTTON_Y + 2), ILI9341_BLACK, BG_TRANSPARENT, ILI9341_GREEN);

	  GFX_DrawFillRoundRectangle(LEFT_BUTTON_X, LEFT_BUTTON_Y, LEFT_BUTTON_W, LEFT_BUTTON_H, RIGHT_LEFT_BUTTON_R,  ILI9341_GREEN);
	  Len = sprintf((char*)Msg, "<=PARAM");
	  EF_PutString(Msg, (LEFT_BUTTON_X + 10), (LEFT_BUTTON_Y + 2), ILI9341_BLACK, BG_TRANSPARENT, ILI9341_GREEN);
	  EF_SetFont(&arialBlack_20ptFontInfo);

	  Len++;

	  //TODO: Dodać sprawdzenie aktualnego stanu
	  GFX_DrawRoundRectangle(SWITCH_BUTTON_X, SWITCH_1_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_BUTTON_COLOR);
	  GFX_DrawRoundRectangle(SWITCH_BUTTON_X, SWITCH_2_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_BUTTON_COLOR);
	  GFX_DrawRoundRectangle(SWITCH_BUTTON_X, SWITCH_3_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_BUTTON_COLOR);
	  GFX_DrawRoundRectangle(SWITCH_BUTTON_X, SWITCH_4_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_BUTTON_COLOR);
}

void showLightsControlPanel()
{
	  ILI9341_ClearDisplay(ILI9341_LIGHTGREY);
	  EF_SetFont(&arialBlack_20ptFontInfo);

	  uint8_t Len = sprintf((char*)Msg, "-=ŚWIATŁA=-");
	  EF_PutString(Msg, SWIATLA_STRING_POZ_X, SWIATLA_STRING_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "ŚWIATŁO 1:");
	  EF_PutString(Msg, STRING_LIGHTS_POZ_X, STRING_LIGHTS_1_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "ŚWIATŁO 2:");
	  EF_PutString(Msg, STRING_LIGHTS_POZ_X, STRING_LIGHTS_2_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "ŚWIATŁO 3:");
	  EF_PutString(Msg, STRING_LIGHTS_POZ_X, STRING_LIGHTS_3_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "ŚWIATŁO 4:");
	  EF_PutString(Msg, STRING_LIGHTS_POZ_X, STRING_LIGHTS_4_POZ_Y, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  EF_SetFont(&arial_11ptFontInfo);
	  GFX_DrawFillRoundRectangle(RIGHT_BUTTON_X, RIGHT_BUTTON_Y, RIGHT_BUTTON_W, RIGHT_BUTTON_H, RIGHT_LEFT_BUTTON_R,  ILI9341_GREEN);
	  Len = sprintf((char*)Msg, "PARAM=>");
	  EF_PutString(Msg, (RIGHT_BUTTON_X + 10), (RIGHT_BUTTON_Y + 2), ILI9341_BLACK, BG_TRANSPARENT, ILI9341_GREEN);

	  GFX_DrawFillRoundRectangle(LEFT_BUTTON_X, LEFT_BUTTON_Y, LEFT_BUTTON_W, LEFT_BUTTON_H, RIGHT_LEFT_BUTTON_R,  ILI9341_GREEN);
	  Len = sprintf((char*)Msg, "<=CONTROL");
	  EF_PutString(Msg, (LEFT_BUTTON_X + 3), (LEFT_BUTTON_Y + 2), ILI9341_BLACK, BG_TRANSPARENT, ILI9341_GREEN);
	  EF_SetFont(&arialBlack_20ptFontInfo);

	  Len++;

	  GFX_DrawRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_1_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_BUTTON_COLOR);
	  GFX_DrawRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_2_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_BUTTON_COLOR);
	  GFX_DrawRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_3_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_BUTTON_COLOR);
	  GFX_DrawRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_4_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_BUTTON_COLOR);

}




