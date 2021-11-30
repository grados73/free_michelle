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

extern float CTemp;
extern float CPres;
extern float CTempWew;
extern uint8_t CWaterLvl ;
extern uint8_t Time[3];


uint8_t system_init(){
	  ILI9341_ClearDisplay(ILI9341_LIGHTGREY);
	  ILI9341_DrawImage(40, 50, logo, 240, 140);
//	  GFX_Image(40, 50, logo, 240, 140); usunieta wolniejsza wersja rysowania

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

	  showCurrentParameters(0.0, 0.0, Time, 0, 0.0);



	  return 1; // TODO! DODAĆ SPRAWDZENIE POPRAWNOŚCI INICJALIZACJI I ZWRÓCENIE 1 / 0
}

void showCurrentParameters(float temp_zew, float temp_wew, uint8_t * TimeTab, uint8_t water_lvl, float presure)
{
		// TODO zrobić żeby czytało właściwe wartości
	  ILI9341_ClearDisplay(ILI9341_LIGHTGREY);
	  EF_SetFont(&arialBlack_20ptFontInfo);
	  uint8_t Len = sprintf((char*)Msg, "Czas: %d:%d:%d", Time[0], Time[1], Time[2]);
	  EF_PutString(Msg, 20, 20, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "Temp. zewn: %.2f`C", CTemp);
	  EF_PutString(Msg, 20, 50, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "Temp. wewn: %.2f`C", CTempWew);
	  EF_PutString(Msg, 20, 80, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "Poz. wody: %d", CWaterLvl);
	  EF_PutString(Msg, 20, 110, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_LIGHTGREY);

	  Len = sprintf((char*)Msg, "Ciśnienie: %.1fhPa", CPres);
	  EF_PutString(Msg, 20, 140, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);

	  Len++;
}

void showControlPanel()
{	// TODO zrobić żeby pokazywało realny panel sterowania

}




