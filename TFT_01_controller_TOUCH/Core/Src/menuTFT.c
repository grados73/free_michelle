/**
  ******************************************************************************
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
#include "parser.h"
#include "ds3231_for_stm32_hal.h"

extern float CTemp;
extern float CPres;
extern uint8_t SwitchesButtonState[4];
extern uint8_t LightsButtonState[4];
extern uint8_t ActivityButtonState[2];
uint8_t StateChangeFlag = 0; // using to indicate change screen activity
uint8_t ClockChangeFlag = 0; // using to indicate change screen to Clock Set
uint8_t WSLedChangeFlag = 0; // using to indicate change screen to WS LEDs Set
uint8_t Hours = 15;
uint8_t Minutes = 5;
uint8_t NrOfLeds = 15;

uint32_t TimerTouch = 0; // Timer to debouncing function

MenuTFTState State = MENUTFT_INIT; // Initialization state for MenuTFT State Machine

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	MAIN FUNCTION TO HANDLING STAND MACHINE OF SCREEN
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		if(StateChangeFlag == 1) // make only one time
		{
			showCurrentParameters(CTemp, 0, 0, 0, CPres);
			StateChangeFlag = 0;
		}
		TouchParametersActivity();
		break;
	case MENUTFT_SWITCH:
		if(StateChangeFlag == 1) // make only one time
		{
			showControlPanel();
			StateChangeFlag = 0;
		}
		TouchSwitchActivity();
		break;
	case MENUTFT_LIGHTS:
		if(StateChangeFlag == 1) // make only one time
		{
			showLightsControlPanel();
			StateChangeFlag = 0;
		}
		TouchLightsActivity();
		break;
	case MENUTFT_CLOCK:
		if(StateChangeFlag == 1) // make only one time
		{
			showClockSetPanel();
			ClockChangeFlag = 1;
			StateChangeFlag = 0;
		}
		TouchClockActivity();
		break;
	case MENUTFT_ACTIVITIES:
		if(StateChangeFlag == 1) // make only one time
		{
			showPreparedActivitiesPanel();
			StateChangeFlag = 0;
		}
		TouchPredefinedActivityActivity();
		break;
	case MENUTFT_WS_LED:
		if(StateChangeFlag == 1) // make only one time
		{
			showWSLedPanel();
			WSLedChangeFlag = 1;
			StateChangeFlag = 0;
		}
		TouchWSLedActivity();
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to handling touch on Parameters Screen
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

			// Check if that point is inside the MEDIUM Button
			else if((x >= MEDIUM_BUTTON_X)&&(x <= (MEDIUM_BUTTON_X+MEDIUM_BUTTON_W))&&
					(y >= MEDIUM_BUTTON_Y)&&(y <= (MEDIUM_BUTTON_Y + MEDIUM_BUTTON_H)))
			{
				State = MENUTFT_CLOCK;
				StateChangeFlag = 1;
			}
			TimerTouch = HAL_GetTick();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to handling touch on Switches Screen
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

			// Check if that point is inside the MEDIUM Button
			else if((x >= MEDIUM_BUTTON_X)&&(x <= (MEDIUM_BUTTON_X+MEDIUM_BUTTON_W))&&
					(y >= MEDIUM_BUTTON_Y)&&(y <= (MEDIUM_BUTTON_Y + MEDIUM_BUTTON_H)))
			{
				State = MENUTFT_ACTIVITIES;
				StateChangeFlag = 1;
			}

			//
			// Check if it is button to change SWITCH status
			//
			//TODO: POTWIERDZENIE WYKONANIA POLECENIA!!!
			else if((x >= SWITCH_BUTTON_X)&&(x <= (SWITCH_BUTTON_X + SWITCH_BUTTON_W)))
			{
				EF_SetFont(&arial_11ptFontInfo);
				//
				// FIRST SWITCH
				if((y >= SWITCH_1_POZ_Y)&&(y <= (SWITCH_1_POZ_Y + SWITCH_BUTTON_H)))
				{
					if(SwitchesButtonState[0] >= 1) // if is ON
					{
						SendComand(UCMD_RELAY_1_OFF); // Send comannd to OFF
						GFX_DrawFillRoundRectangle(SWITCH_BUTTON_X, SWITCH_1_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (SWITCH_BUTTON_X+STRING_ERRATA_X), (SWITCH_1_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						SwitchesButtonState[0] = 0;
					}
					else // if is OFF
					{
						SendComand(UCMD_RELAY_1_ON); // Send comannd to ON
						GFX_DrawFillRoundRectangle(SWITCH_BUTTON_X, SWITCH_1_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_ON_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (SWITCH_BUTTON_X+STRING_ERRATA_X), (SWITCH_1_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_ON_BUTTON_COLOR);
						SwitchesButtonState[0] = 1;
					}

				}
				//
				// SECOND SWITCH
				else if((y >= SWITCH_2_POZ_Y)&&(y <= (SWITCH_2_POZ_Y + SWITCH_BUTTON_H)))
				{
					if(SwitchesButtonState[1] >= 1) // if is ON
					{
						SendComand(UCMD_RELAY_2_OFF); // Send comannd to OFF
						GFX_DrawFillRoundRectangle(SWITCH_BUTTON_X, SWITCH_2_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (SWITCH_BUTTON_X+STRING_ERRATA_X), (SWITCH_2_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						SwitchesButtonState[1] = 0;
					}
					else // if is OFF
					{
						SendComand(UCMD_RELAY_2_ON); // Send comannd to ON
						GFX_DrawFillRoundRectangle(SWITCH_BUTTON_X, SWITCH_2_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_ON_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (SWITCH_BUTTON_X+STRING_ERRATA_X), (SWITCH_2_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_ON_BUTTON_COLOR);
						SwitchesButtonState[1] = 1;
					}
				}
				//
				// THIRD SWITCH
				else if((y >= SWITCH_3_POZ_Y)&&(y <= (SWITCH_3_POZ_Y + SWITCH_BUTTON_H)))
				{
					if(SwitchesButtonState[2] >= 1) // if is ON
					{
						SendComand(UCMD_RELAY_3_OFF); // Send comannd to OFF
						GFX_DrawFillRoundRectangle(SWITCH_BUTTON_X, SWITCH_3_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (SWITCH_BUTTON_X+STRING_ERRATA_X), (SWITCH_3_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						SwitchesButtonState[2] = 0;
					}
					else // if is OFF
					{
						SendComand(UCMD_RELAY_3_ON); // Send comannd to ON
						GFX_DrawFillRoundRectangle(SWITCH_BUTTON_X, SWITCH_3_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_ON_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (SWITCH_BUTTON_X+STRING_ERRATA_X), (SWITCH_3_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_ON_BUTTON_COLOR);
						SwitchesButtonState[2] = 1;
					}
				}
				//
				// FOURTH SWITCH
				else if((y >= SWITCH_4_POZ_Y)&&(y <= (SWITCH_4_POZ_Y + SWITCH_BUTTON_H)))
				{
					if(SwitchesButtonState[3] >= 1) // if is ON
					{
						SendComand(UCMD_RELAY_4_OFF); // Send comannd to OFF
						GFX_DrawFillRoundRectangle(SWITCH_BUTTON_X, SWITCH_4_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (SWITCH_BUTTON_X+STRING_ERRATA_X), (SWITCH_4_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						SwitchesButtonState[3] = 0;
					}
					else // if is OFF
					{
						SendComand(UCMD_RELAY_4_ON); // Send comannd to ON
						GFX_DrawFillRoundRectangle(SWITCH_BUTTON_X, SWITCH_4_POZ_Y, SWITCH_BUTTON_W, SWITCH_BUTTON_H, SWITCH_BUTTON_R, SWITCH_ON_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (SWITCH_BUTTON_X+STRING_ERRATA_X), (SWITCH_4_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_ON_BUTTON_COLOR);
						SwitchesButtonState[3] = 1;
					}
				}
				EF_SetFont(&arialBlack_20ptFontInfo);
			}
			TimerTouch = HAL_GetTick();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to handling touch on Lights Screen
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

			// Check if that point is inside the MEDIUM Button
			else if((x >= MEDIUM_BUTTON_X)&&(x <= (MEDIUM_BUTTON_X+MEDIUM_BUTTON_W))&&
					(y >= MEDIUM_BUTTON_Y)&&(y <= (MEDIUM_BUTTON_Y + MEDIUM_BUTTON_H)))
			{
				State = MENUTFT_WS_LED;
				StateChangeFlag = 1;
			}

			//
			// Check if it is button to change LIGHTS status
			//
			//TODO: POWIERDZENIA WYKONANIA KOMENDY
			else if((x >= LIGHTS_BUTTON_X)&&(x <= (LIGHTS_BUTTON_X + LIGHTS_BUTTON_W)))
			{
				EF_SetFont(&arial_11ptFontInfo);

				//
				// FIRST LIGHT
				if((y >= LIGHT_B_1_POZ_Y)&&(y <= (LIGHT_B_1_POZ_Y + LIGHTS_BUTTON_H)))
				{
					if(LightsButtonState[0] >= 1) // if is ON
					{
						SendComand(UCMD_LIGHT_1_OFF); // Send comannd to OFF
						GFX_DrawFillRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_1_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (LIGHTS_BUTTON_X+STRING_ERRATA_X), (LIGHT_B_1_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						LightsButtonState[0] = 0;
					}
					else // if is OFF
					{
						SendComand(UCMD_LIGHT_1_ON); // Send comannd to ON
						GFX_DrawFillRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_1_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_ON_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (LIGHTS_BUTTON_X+STRING_ERRATA_X), (LIGHT_B_1_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						LightsButtonState[0] = 1;
					}
				}
				//
				// SECOND LIGHT
				else if((y >= LIGHT_B_2_POZ_Y)&&(y <= (LIGHT_B_2_POZ_Y + LIGHTS_BUTTON_H)))
				{
					if(LightsButtonState[1] >= 1) // if is ON
					{
						SendComand(UCMD_LIGHT_2_OFF); // Send comannd to OFF
						GFX_DrawFillRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_2_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (LIGHTS_BUTTON_X+STRING_ERRATA_X), (LIGHT_B_2_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						LightsButtonState[1] = 0;
					}
					else // if is OFF
					{
						SendComand(UCMD_LIGHT_2_ON); // Send comannd to ON
						GFX_DrawFillRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_2_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_ON_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (LIGHTS_BUTTON_X+STRING_ERRATA_X), (LIGHT_B_2_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						LightsButtonState[1] = 1;
					}
				}

				//
				// THIRD LIGHT
				else if((y >= LIGHT_B_3_POZ_Y)&&(y <= (LIGHT_B_3_POZ_Y + LIGHTS_BUTTON_H)))
				{
					if(LightsButtonState[2] >= 1) // if is ON
					{
						SendComand(UCMD_LIGHT_3_OFF); // Send comannd to OFF
						GFX_DrawFillRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_3_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (LIGHTS_BUTTON_X+STRING_ERRATA_X), (LIGHT_B_3_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						LightsButtonState[2] = 0;
					}
					else // if is OFF
					{
						SendComand(UCMD_LIGHT_3_ON); // Send comannd to ON
						GFX_DrawFillRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_3_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_ON_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (LIGHTS_BUTTON_X+STRING_ERRATA_X), (LIGHT_B_3_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						LightsButtonState[2] = 1;
					}
				}

				//
				// FOURTH LIGHT
				else if((y >= LIGHT_B_4_POZ_Y)&&(y <= (LIGHT_B_4_POZ_Y + LIGHTS_BUTTON_H)))
				{
					if(LightsButtonState[3] >= 1) // if is ON
					{
						SendComand(UCMD_LIGHT_4_OFF); // Send comannd to OFF
						GFX_DrawFillRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_4_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (LIGHTS_BUTTON_X+STRING_ERRATA_X), (LIGHT_B_4_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						LightsButtonState[3] = 0;
					}
					else // if is OFF
					{
						SendComand(UCMD_LIGHT_4_ON); // Send comannd to ON
						GFX_DrawFillRoundRectangle(LIGHTS_BUTTON_X, LIGHT_B_4_POZ_Y, LIGHTS_BUTTON_W, LIGHTS_BUTTON_H, LIGHTS_BUTTON_R, SWITCH_ON_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (LIGHTS_BUTTON_X+STRING_ERRATA_X), (LIGHT_B_4_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						LightsButtonState[3] = 1;
					}
				}
				EF_SetFont(&arialBlack_20ptFontInfo);
			}

			TimerTouch = HAL_GetTick();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to handling touch on Set CLOCK Screen
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TouchClockActivity(void)
{
	// Check if screen was touched
		if(XPT2046_IsTouched())
		{
			EF_SetFont(&arialBlack_20ptFontInfo);
			if(HAL_GetTick() - TimerTouch >= SWITCH_DEBOUNCING_TIME_MS) // If pass 1000ms from last change State
			{
				uint16_t x, y; // Touch points

				XPT2046_GetTouchPoint(&x, &y); // Get the current couched point

				if( 1 == ClockChangeFlag) // If we just get inside this screen we must get current Hour and Minutes to easier change them, but only once
				{
					Hours = DS3231_GetHour();
					Minutes = DS3231_GetMinute();
					ClockChangeFlag = 0;
				}

				//
				// Check if it is button to change screen
				//
				// Check if that point is inside the LEFT Button - back to Parameters
				if((x >= LEFT_BUTTON_X)&&(x <= (LEFT_BUTTON_X+LEFT_BUTTON_W))&&
						(y >= LEFT_BUTTON_Y)&&(y <= (LEFT_BUTTON_Y + LEFT_BUTTON_H)))
				{
					State = MENUTFT_PARAMETERS;
					StateChangeFlag = 1;
				}

				// Check if that point is inside the RIGHT Button - Confirmed changed clock
				else if((x >= RIGHT_BUTTON_X)&&(x <= (RIGHT_BUTTON_X+RIGHT_BUTTON_W))&&
						(y >= RIGHT_BUTTON_Y)&&(y <= (RIGHT_BUTTON_Y + RIGHT_BUTTON_H)))
				{
					DS3231_SetHour(Hours);
					DS3231_SetMinute(Minutes);
					DS3231_SetSecond(50);
					sprintf((char*)Msg, "-Time Changed-");
					EF_PutString(Msg, CLOCK_STRING_POZ_X, CLOCK_STRING_POZ_Y, ILI9341_GREEN, BG_COLOR, ILI9341_LIGHTGREY);
				}

				//
				// Check if it is button to increase by an ONE (1) HOUR / MINUT - first ROW
				//
				else if((x >= CLOCK_BUTTON_X)&&(x <= (CLOCK_BUTTON_X + CLOCK_BUTTON_W)))
				{

					if((y >= CLOCK_B_1_POZ_Y)&&(y <= (CLOCK_B_1_POZ_Y + CLOCK_BUTTON_H))) // Add 1 Hour
					{
						if(Hours < 24)
						{
							Hours++;
						}
						else
						{
							Hours = 1;
						}
						sprintf((char*)Msg, " %d  ", Hours);
						EF_PutString(Msg, STRING_H_M_NUMBER_POZ_X, STRING_HOUR_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);

					}
					else if((y >= CLOCK_B_2_POZ_Y)&&(y <= (CLOCK_B_2_POZ_Y + CLOCK_BUTTON_H))) // Add 1 Minute
					{
						if(Minutes < 59)
						{
							Minutes++;
						}
						else
						{
							Minutes = 0;
						}
						sprintf((char*)Msg, " %d  ", Minutes);
						EF_PutString(Msg, STRING_H_M_NUMBER_POZ_X, STRING_MINUTE_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);
					}

				}

				//
				// Check if it is button to increase by an 6 HOURS / 10 MINUTS - second ROW
				//
				else if((x >= (CLOCK_BUTTON2_X))&&(x <= (CLOCK_BUTTON2_X + CLOCK_BUTTON_W)))
				{
					if((y >= CLOCK_B_1_POZ_Y)&&(y <= (CLOCK_B_1_POZ_Y + CLOCK_BUTTON_H))) // Add 6 Hour
					{

						if(Hours < 19)
						{
							Hours = Hours + 6;
						}
						else
						{
							Hours = 1;
						}
						sprintf((char*)Msg, " %d  ", Hours);
						EF_PutString(Msg, (STRING_H_M_NUMBER_POZ_X-3), STRING_HOUR_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);

					}
					else if((y >= CLOCK_B_2_POZ_Y)&&(y <= (CLOCK_B_2_POZ_Y + CLOCK_BUTTON_H))) // Add 10 Minute
					{
						if(Minutes < 49)
						{
							Minutes = Minutes +10;
						}
						else
						{
							Minutes = (Minutes + 10) % 60;
						}
						sprintf((char*)Msg, " %d  ", Minutes);
						EF_PutString(Msg, (STRING_H_M_NUMBER_POZ_X-4), STRING_MINUTE_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);

					}
					EF_SetFont(&arialBlack_20ptFontInfo);
				}
				TimerTouch = HAL_GetTick();
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to handling touch on Predefined Activity Screen
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TouchPredefinedActivityActivity()
{
	if(XPT2046_IsTouched())
	{

		if(HAL_GetTick() - TimerTouch >= SWITCH_DEBOUNCING_TIME_MS) // If pass 1000ms from last change State
		{
			uint16_t x, y; // Touch points
			XPT2046_GetTouchPoint(&x, &y); // Get the current couched point

			EF_SetFont(&arial_11ptFontInfo);
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

			//
			// Check if that point is in row where are button to Predefined Activity
			//
			else if((x >= ACTIVITY_BUTTON_X)&&(x <= (ACTIVITY_BUTTON_X + ACTIVITY_BUTTON_W)))
			{
				if((y >= ACTIVITY_BUTTON_1_Y)&&(y<= (ACTIVITY_BUTTON_1_Y + ACTIVITY_BUTTON_H))) // First predefined activity button
				{
					if(ActivityButtonState[0] >= 1) // if is ON
					{
						ActivityButtonState[0] = 0;
						GFX_DrawFillRoundRectangle(ACTIVITY_BUTTON_X, ACTIVITY_BUTTON_1_Y, ACTIVITY_BUTTON_W, ACTIVITY_BUTTON_H, ACTIVITY_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "KARMIENIE");
						EF_PutString(Msg, (ACTIVITY_BUTTON_X+STRING_ACTIVITIES_1_X_ERRATA), (ACTIVITY_BUTTON_1_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (ACTIVITY_BUTTON_X+STRING_ACTIVITIES_ON_OFF_X_ERRATA), (ACTIVITY_BUTTON_1_Y+STRING_ACTIVITIES_Y_INTER), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						predefinedActivityKarmienie(0); // Turn Activity OFF
					}
					else // if is OFF
					{
						ActivityButtonState[0] = 1;
						GFX_DrawFillRoundRectangle(ACTIVITY_BUTTON_X, ACTIVITY_BUTTON_1_Y, ACTIVITY_BUTTON_W, ACTIVITY_BUTTON_H, ACTIVITY_BUTTON_R, SWITCH_ON_ACTIVITY_BUTTON_COLOR);
						sprintf((char*)Msg, "KARMIENIE");
						EF_PutString(Msg, (ACTIVITY_BUTTON_X+STRING_ACTIVITIES_1_X_ERRATA), (ACTIVITY_BUTTON_1_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_ON_ACTIVITY_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (ACTIVITY_BUTTON_X+STRING_ACTIVITIES_ON_OFF_X_ERRATA), (ACTIVITY_BUTTON_1_Y+STRING_ACTIVITIES_Y_INTER), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_ON_ACTIVITY_BUTTON_COLOR);
						predefinedActivityKarmienie(1);
					}

				}

				else if((y >= ACTIVITY_BUTTON_2_Y)&&(y<= (ACTIVITY_BUTTON_2_Y + ACTIVITY_BUTTON_H))) // Second predefined activity button
				{
					if(ActivityButtonState[1] >= 1) // if is ON
					{
						ActivityButtonState[1] = 0;
						GFX_DrawFillRoundRectangle(ACTIVITY_BUTTON_X, ACTIVITY_BUTTON_2_Y, ACTIVITY_BUTTON_W, ACTIVITY_BUTTON_H, ACTIVITY_BUTTON_R, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "CZYSZCZENIE");
						EF_PutString(Msg, (ACTIVITY_BUTTON_X+STRING_ACTIVITIES_2_X_ERRATA), (ACTIVITY_BUTTON_2_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						sprintf((char*)Msg, "OFF");
						EF_PutString(Msg, (ACTIVITY_BUTTON_X+STRING_ACTIVITIES_ON_OFF_X_ERRATA), (ACTIVITY_BUTTON_2_Y+STRING_ACTIVITIES_Y_INTER), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_OFF_BUTTON_COLOR);
						predefinedActivityCzyszczenie(0);
					}
					else // if is OFF
					{
						ActivityButtonState[1] = 1;
						GFX_DrawFillRoundRectangle(ACTIVITY_BUTTON_X, ACTIVITY_BUTTON_2_Y, ACTIVITY_BUTTON_W, ACTIVITY_BUTTON_H, ACTIVITY_BUTTON_R, SWITCH_ON_ACTIVITY_BUTTON_COLOR);
						sprintf((char*)Msg, "CZYSZCZENIE");
						EF_PutString(Msg, (ACTIVITY_BUTTON_X+STRING_ACTIVITIES_2_X_ERRATA), (ACTIVITY_BUTTON_2_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_ON_ACTIVITY_BUTTON_COLOR);
						sprintf((char*)Msg, "ON");
						EF_PutString(Msg, (ACTIVITY_BUTTON_X+STRING_ACTIVITIES_ON_OFF_X_ERRATA), (ACTIVITY_BUTTON_2_Y+STRING_ACTIVITIES_Y_INTER), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_ON_ACTIVITY_BUTTON_COLOR);
						predefinedActivityCzyszczenie(1);
					}
				}
			}
			TimerTouch = HAL_GetTick();
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to handling touch on LEDs WS2812b controlling screen
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TouchWSLedActivity(void)
{
	// Check if screen was touched
		if(XPT2046_IsTouched())
		{
			EF_SetFont(&arialBlack_20ptFontInfo);
			if(HAL_GetTick() - TimerTouch >= SWITCH_DEBOUNCING_TIME_MS) // If pass 1000ms from last change State
			{
				uint16_t x, y; // Touch points

				XPT2046_GetTouchPoint(&x, &y); // Get the current couched point

				if( 1 == ClockChangeFlag) // If we just get inside this screen we must get number of LEDs, but we do it only once
				{
					//TODO! Przeczytac ilosc diod z EEPROMu
					WSLedChangeFlag = 0;
				}

				//
				// Check if it is button to change screen
				//
				// Check if that point is inside the LEFT Button - back to Parameters
				if((x >= LEFT_BUTTON_X)&&(x <= (LEFT_BUTTON_X+LEFT_BUTTON_W))&&
						(y >= LEFT_BUTTON_Y)&&(y <= (LEFT_BUTTON_Y + LEFT_BUTTON_H)))
				{
					State = MENUTFT_LIGHTS;
					StateChangeFlag = 1;
				}


				//
				// Check if it is button to increase number of LEDs - first line
				//
				else if((y >= WS_B_1_POZ_Y)&&(y <= (WS_B_1_POZ_Y + WS_LED_BUTTON_H)))
				{

					if((x >= WS_LED_BUTTON_1_X)&&(x <= (WS_LED_BUTTON_1_X + WS_LED_BUTTON_W))) // Add +1 LED
					{
						if(NrOfLeds < 98)
						{
							NrOfLeds++;
						}
						else
						{
							NrOfLeds = 1;
						}
						if(NrOfLeds < 10)sprintf((char*)Msg, "  %d ", NrOfLeds);
						else sprintf((char*)Msg, " %d", NrOfLeds);
						EF_PutString(Msg, STRING_WS_LED_POZ_NUMBER_X, STRING_WS_LED_ILOSC_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);
					}
					else if((x >= WS_LED_BUTTON_2_X)&&(x <= (WS_LED_BUTTON_2_X + WS_LED_BUTTON_W))) // Add +10 LED
					{
						if(NrOfLeds < 90)
						{
							NrOfLeds = NrOfLeds + 10;
						}
						else
						{
							NrOfLeds = (NrOfLeds + 10) % 99;
						}
					// Display String
					if(NrOfLeds < 10)sprintf((char*)Msg, "  %d ", NrOfLeds);
					else sprintf((char*)Msg, " %d", NrOfLeds);
					EF_PutString(Msg, STRING_WS_LED_POZ_NUMBER_X, STRING_WS_LED_ILOSC_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);
					}


					else if((x >= WS_LED_BUTTON_3_X)&&(x <= (WS_LED_BUTTON_3_X + WS_LED_BUTTON_W))) // OK - confirm and send number of LEDs
					{
						SendComand(UCMD_WS_NUMBER_LED);
						EF_SetFont(&arial_11ptFontInfo);
						GFX_DrawFillRoundRectangle(WS_LED_BUTTON_3_X, WS_B_1_POZ_Y, WS_LED_BUTTON_W, WS_LED_BUTTON_H, WS_LED_BUTTON_R, SWITCH_ON_BUTTON_COLOR);
						sprintf((char*)Msg, "OK");
						EF_PutString(Msg, (WS_LED_BUTTON_3_X+STRING_ERRATA_X+1), (WS_B_1_POZ_Y+STRING_ERRATA_Y), ILI9341_BLACK, BG_TRANSPARENT, SWITCH_ON_BUTTON_COLOR);
						//TODO! Dodać zapis do EEPROM!
					}
				}

				//
				// Check if it is second line button to change LEDs to WHITE
				//
				else if((y >= WS_B_2_POZ_Y)&&(y <= (WS_B_2_POZ_Y + WS_LED_BUTTON_H)))
				{
					if((x >= WS_WHITE_BUTTON_1_X)&&(x <= (WS_WHITE_BUTTON_1_X + WS_COLOR_BUTTON_W))) // MAX
					{
						SendComand(UCMD_WS_LED_WHITE_MAX);
					}
					else if((x >= WS_WHITE_BUTTON_2_X)&&(x <= (WS_WHITE_BUTTON_2_X + WS_COLOR_BUTTON_W))) // MID
					{
						SendComand(UCMD_WS_LED_WHITE_MID);
					}
					else if((x >= WS_WHITE_BUTTON_3_X)&&(x <= (WS_WHITE_BUTTON_3_X + WS_COLOR_BUTTON_W))) // MIN
					{
						SendComand(UCMD_WS_LED_WHITE_MIN);
					}
				}

				//
				// Check if it is third line button to change LEDs to BLUE
				//
				else if((y >= WS_B_3_POZ_Y)&&(y <= (WS_B_3_POZ_Y + WS_LED_BUTTON_H)))
				{
					if((x >= WS_WHITE_BUTTON_1_X)&&(x <= (WS_WHITE_BUTTON_1_X + WS_COLOR_BUTTON_W))) // MAX
					{
						SendComand(UCMD_WS_LED_BLUE_MAX);
					}
					else if((x >= WS_WHITE_BUTTON_2_X)&&(x <= (WS_WHITE_BUTTON_2_X + WS_COLOR_BUTTON_W))) // MID
					{
						SendComand(UCMD_WS_LED_BLUE_MID);
					}
					else if((x >= WS_WHITE_BUTTON_3_X)&&(x <= (WS_WHITE_BUTTON_3_X + WS_COLOR_BUTTON_W))) // MIN
					{
						SendComand(UCMD_WS_LED_BLUE_MIN);
					}
				}

				//
				// Check if it is fourth line button to change LEDs to Predefined
				//
				else if((y >= WS_B_4_POZ_Y)&&(y <= (WS_B_4_POZ_Y + WS_LED_BUTTON_H)))
				{
					if((x >= WS_PREDEFINED_BUTTON_1_X)&&(x <= (WS_PREDEFINED_BUTTON_1_X + WS_PREDEFINED_BUTTON_W))) // MAX
					{
						SendComand(UCMD_WS_LED_DAILY);
					}
					else if((x >= WS_PREDEFINED_BUTTON_2_X)&&(x <= (WS_PREDEFINED_BUTTON_2_X + WS_PREDEFINED_BUTTON_W))) // MID
					{
						SendComand(UCMD_WS_LED_WHITE_OFF);
					}
					else if((x >= WS_PREDEFINED_BUTTON_3_X)&&(x <= (WS_PREDEFINED_BUTTON_3_X + WS_PREDEFINED_BUTTON_W))) // MIN
					{
						SendComand(UCMD_WS_LED_NIGHT);
					}
				}

				//
				// Check if it is fifth line button to change LEDs to Predefined animations
				//
				else if((y >= WS_B_5_POZ_Y)&&(y <= (WS_B_5_POZ_Y + WS_LED_BUTTON_H)))
				{
					if((x >= WS_PREDEFINED_ACT_BUTTON_1_X)&&(x <= (WS_PREDEFINED_ACT_BUTTON_1_X + WS_PREDEFINED_BUTTON_W))) // MAX
					{
						SendComand(UCMD_WS_ANIMATION_SUNRISE);
					}
					else if((x >= WS_PREDEFINED_ACT_BUTTON_2_X)&&(x <= (WS_PREDEFINED_ACT_BUTTON_2_X + WS_PREDEFINED_BUTTON_W))) // MID
					{
						SendComand(UCMD_WS_ANIMATION_SUNSET);
					}
				}
				TimerTouch = HAL_GetTick();
			}
		}
}


