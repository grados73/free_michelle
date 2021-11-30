/**
  ******************************************************************************
  * @file           : menuTFT.c
  * @project		: free_michelle
  * @author			: grados73 - https://github.com/grados73
  * @purpose		: file to service menu on TFT display
  ******************************************************************************
  **/

#include "main.h"
#include "menuTFT.h"
#include "TFT_ILI9341.h"
#include "XPT2064.h"
#include "GFX_Color.h"
#include "GFX_EnhancedFonts.h"
#include "functions.h"

extern float CTemp;
extern float CPres;
uint8_t StateChangeFlag = 0;



typedef enum
{
	MENUTFT_INIT, 			// Build GUI
	MENUTFT_PARAMETERS, 	// Read parameters
	MENUTFT_SWITCH,			// Show current switch state, and possibility to change them
	MENUTFT_LIGHTS 			// Show current lights state, and possibility to change them
} MenuTFTState;

MenuTFTState State = MENUTFT_INIT; // Initialization state for MenuTFT State Machine

void MenuTFT(void)
{
	switch(State)
	{
	case MENUTFT_INIT:
		system_init();
		State = MENUTFT_PARAMETERS;
		StateChangeFlag = 1;
		break;
	case MENUTFT_PARAMETERS:
		if(StateChangeFlag == 1)
		{
		showCurrentParameters(CTemp, 0, 0, 0, CPres);
		StateChangeFlag = 0;
		}
		break;
	case MENUTFT_SWITCH:
		showControlPanel();
		break;
	case MENUTFT_LIGHTS:
		showLightsControlPanel();
		break;
	}
}


void TouchActivity(void)
{
	// Check if screen was touched
	if(XPT2046_IsTouched())
	{
		uint16_t x, y; // Touch points

		XPT2046_GetTouchPoint(&x, &y); // Get the current couched point

		// Check if that point is inside the LEFT Button
		if((x >= LEFT_BUTTON_X)&&(x <= (LEFT_BUTTON_X+LEFT_BUTTON_W))&&
				(y >= LEFT_BUTTON_Y)&&(y <= (LEFT_BUTTON_Y + LEFT_BUTTON_H)))
		{

		}

//		if((x > DRAW_WINDOW_X_START)&&(x < DRAW_WINDOW_X_STOP)&&(y > DRAW_WINDOW_Y_START)&&(y < DRAW_WINDOW_Y_STOP))
//		{
//			// If yes - just draw a pixel there with current selected color
//			GFX_DrawPixel(x, y, CurrentColor);
//		}
//
//		// Check if any Color change button was touched
//		ColorButtonNubmer = IsColorButtonTouched(x, y);
//		if(ColorButtonNubmer != 0) // If yes
//		{
//			// Chenge current color
//			CurrentColor = UsedColors[ColorButtonNubmer-1];
//			// Redrwa current color indicator
//			ColorIndicator();
//		}
//
//		// Check if any Clearing button was touched
//		if(IsClearButtonTouched(x, y))
//		{
//			// Jump to Clearing state
//			State = PAINT_CLEAR;
//		}
	}
}

