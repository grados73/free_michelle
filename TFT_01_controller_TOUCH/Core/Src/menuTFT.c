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

uint32_t TimerTouch = 0; // Timer to debouncing function

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
		TouchParametersActivity();
		break;
	case MENUTFT_SWITCH:
		if(StateChangeFlag == 1)
		{
			showControlPanel();
			StateChangeFlag = 0;
		}
		TouchSwitchActivity();
		break;
	case MENUTFT_LIGHTS:
		if(StateChangeFlag == 1)
		{
			showLightsControlPanel();
			StateChangeFlag = 0;
		}
		TouchLightsActivity();
		break;
	}
}


void TouchParametersActivity(void)
{
	// Check if screen was touched
	if(XPT2046_IsTouched())
	{
		if(HAL_GetTick() - TimerTouch >= SWITCH_DEBOUNCING_TIME_MS) // If pass 1000ms from last change State
		{
			uint16_t x, y; // Touch points
			XPT2046_GetTouchPoint(&x, &y); // Get the current couched point

			//
			// Check if it is button to change screen
			//
			// Check if that point is inside the LEFT Button
			if((x >= LEFT_BUTTON_X)&&(x <= (LEFT_BUTTON_X+LEFT_BUTTON_W))&&
					(y >= LEFT_BUTTON_Y)&&(y <= (LEFT_BUTTON_Y + LEFT_BUTTON_H)))
			{
				State = MENUTFT_LIGHTS;
				StateChangeFlag = 1;
			}

			// Check if that point is inside the RIGHT Button
			else if((x >= RIGHT_BUTTON_X)&&(x <= (RIGHT_BUTTON_X+RIGHT_BUTTON_W))&&
					(y >= RIGHT_BUTTON_Y)&&(y <= (RIGHT_BUTTON_Y + RIGHT_BUTTON_H)))
			{
				State = MENUTFT_SWITCH;
				StateChangeFlag = 1;
			}
			TimerTouch = HAL_GetTick();
		}
	}
}

void TouchSwitchActivity(void)
{
	// Check if screen was touched
	if(XPT2046_IsTouched())
	{
		if(HAL_GetTick() - TimerTouch >= SWITCH_DEBOUNCING_TIME_MS) // If pass 1000ms from last change State
		{
			uint16_t x, y; // Touch points
			XPT2046_GetTouchPoint(&x, &y); // Get the current couched point

			//
			// Check if it is button to change screen
			//
			// Check if that point is inside the LEFT Button
			if((x >= LEFT_BUTTON_X)&&(x <= (LEFT_BUTTON_X+LEFT_BUTTON_W))&&
					(y >= LEFT_BUTTON_Y)&&(y <= (LEFT_BUTTON_Y + LEFT_BUTTON_H)))
			{
				State = MENUTFT_PARAMETERS;
				StateChangeFlag = 1;
			}

			// Check if that point is inside the RIGHT Button
			else if((x >= RIGHT_BUTTON_X)&&(x <= (RIGHT_BUTTON_X+RIGHT_BUTTON_W))&&
					(y >= RIGHT_BUTTON_Y)&&(y <= (RIGHT_BUTTON_Y + RIGHT_BUTTON_H)))
			{
				State = MENUTFT_LIGHTS;
				StateChangeFlag = 1;
			}
			//
			// Check if it is button to change SWITCH status
			//
			else if((x >= SWITCH_BUTTON_X)&&(x <= (SWITCH_BUTTON_X + SWITCH_BUTTON_W)))
			{
				if((y >= SWITCH_1_POZ_Y)&&(y <= (SWITCH_1_POZ_Y + SWITCH_BUTTON_H)))
				{
					//TODO
				}
				else if((y >= SWITCH_2_POZ_Y)&&(y <= (SWITCH_2_POZ_Y + SWITCH_BUTTON_H)))
				{
					//TODO
				}
				else if((y >= SWITCH_3_POZ_Y)&&(y <= (SWITCH_3_POZ_Y + SWITCH_BUTTON_H)))
				{
					//TODO
				}
				else if((y >= SWITCH_4_POZ_Y)&&(y <= (SWITCH_4_POZ_Y + SWITCH_BUTTON_H)))
				{
					//TODO
				}
			}
			TimerTouch = HAL_GetTick();
		}
	}
}

void TouchLightsActivity(void)
{
	// Check if screen was touched
	if(XPT2046_IsTouched())
	{
		if(HAL_GetTick() - TimerTouch >= SWITCH_DEBOUNCING_TIME_MS) // If pass 1000ms from last change State
		{
			uint16_t x, y; // Touch points
			XPT2046_GetTouchPoint(&x, &y); // Get the current couched point

			//
			// Check if it is button to change screen
			//
			// Check if that point is inside the LEFT Button
			if((x >= LEFT_BUTTON_X)&&(x <= (LEFT_BUTTON_X+LEFT_BUTTON_W))&&
					(y >= LEFT_BUTTON_Y)&&(y <= (LEFT_BUTTON_Y + LEFT_BUTTON_H)))
			{
				State = MENUTFT_SWITCH;
				StateChangeFlag = 1;
			}

			// Check if that point is inside the RIGHT Button
			else if((x >= RIGHT_BUTTON_X)&&(x <= (RIGHT_BUTTON_X+RIGHT_BUTTON_W))&&
					(y >= RIGHT_BUTTON_Y)&&(y <= (RIGHT_BUTTON_Y + RIGHT_BUTTON_H)))
			{
				State = MENUTFT_PARAMETERS;
				StateChangeFlag = 1;
			}

			//
			// Check if it is button to change LIGHTS status
			//
			else if((x >= LIGHTS_BUTTON_X)&&(x <= (LIGHTS_BUTTON_X + LIGHTS_BUTTON_W)))
			{
				if((y >= LIGHT_B_1_POZ_Y)&&(y <= (LIGHT_B_1_POZ_Y + LIGHTS_BUTTON_H)))
				{
					//TODO
				}
				else if((y >= LIGHT_B_2_POZ_Y)&&(y <= (LIGHT_B_2_POZ_Y + LIGHTS_BUTTON_H)))
				{
					//TODO
				}
				else if((y >= LIGHT_B_3_POZ_Y)&&(y <= (LIGHT_B_3_POZ_Y + LIGHTS_BUTTON_H)))
				{
					//TODO
				}
				else if((y >= LIGHT_B_4_POZ_Y)&&(y <= (LIGHT_B_4_POZ_Y + LIGHTS_BUTTON_H)))
				{
					//TODO
				}
			}

			TimerTouch = HAL_GetTick();
		}
	}
}

