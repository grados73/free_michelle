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


uint8_t system_init(){
	  ILI9341_ClearDisplay(ILI9341_LIGHTGREY);
	  ILI9341_DrawImage(40, 50, logo, 240, 140);
//	  GFX_Image(40, 50, logo, 240, 140); usunieta wolniejsza wersja rysowania

	  HAL_Delay(200); // !!!! TODO

	  EF_SetFont(&arialBlack_20ptFontInfo);
	  uint8_t Len = sprintf(Msg, "Inicjalizacja...");
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

void showCurrentParameters(uint8_t temp_zew, uint8_t temp_wew, uint8_t time, uint8_t water_lvl, uint8_t humidity)
{
		// TODO zrobić żeby czytało właściwe wartości
	  ILI9341_ClearDisplay(ILI9341_LIGHTGREY);
	  EF_SetFont(&arialBlack_20ptFontInfo);
	  uint8_t Len = sprintf(Msg, "Czas: 00:00:00");
	  EF_PutString(Msg, 20, 20, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_BLACK);
	  Len = sprintf(Msg, "Temp. zewn: 0`C");
	  EF_PutString(Msg, 20, 50, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_BLACK);
	  Len = sprintf(Msg, "Temp. wewn: 0`C");
	  EF_PutString(Msg, 20, 80, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_BLACK);
	  Len = sprintf(Msg, "Wilgotność: 0%");
	  EF_PutString(Msg, 20, 110, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_BLACK);
	  Len = sprintf(Msg, "Poziom wody: 0%");
	  EF_PutString(Msg, 20, 140, ILI9341_BLACK, BG_TRANSPARENT, ILI9341_BLACK);
	  Len++;
}

void showControlPanel()
{	// TODO zrobić żeby pokazywało realny panel sterowania

}




