/*
 * menuTFT.h
 *
 *  Created on: Nov 29, 2021
 *      Author: grad_
 */

#ifndef INC_MENUTFT_H_
#define INC_MENUTFT_H_

#define SWITCH_DEBOUNCING_TIME_MS 1000

//
// Define position and size of button
//
#define RIGHT_LEFT_BUTTON_R 5 //Rounding of button
#define SWITCH_ON_BUTTON_COLOR ILI9341_GREENYELLOW
#define SWITCH_OFF_BUTTON_COLOR ILI9341_RED

//define position and size of button to change menu screen to RIGHT
#define RIGHT_BUTTON_X 220
#define RIGHT_BUTTON_Y 216
#define RIGHT_BUTTON_W 100
#define RIGHT_BUTTON_H 20
//define position and size of button to change menu screen to LEFT
#define LEFT_BUTTON_X 10
#define LEFT_BUTTON_Y 216
#define LEFT_BUTTON_W 100
#define LEFT_BUTTON_H 20

//
//define position and size of button to change state of EVERY switch in showControlPanel()
#define SWITCH_BUTTON_X 270
#define SWITCH_BUTTON_W 33
#define SWITCH_BUTTON_H 21
#define SWITCH_BUTTON_R 5
//define position of EACH ONE switch in showControlPanel()
#define SWITCH_1_POZ_Y (STRING_SWITCH_1_POZ_Y+5)
#define SWITCH_2_POZ_Y (STRING_SWITCH_2_POZ_Y+5)
#define SWITCH_3_POZ_Y (STRING_SWITCH_3_POZ_Y+5)
#define SWITCH_4_POZ_Y (STRING_SWITCH_4_POZ_Y+5)

//
//define position and size of button to change state of EVERY switch in showLightsControlPanel()
#define LIGHTS_BUTTON_X 200
#define LIGHTS_BUTTON_W 33
#define LIGHTS_BUTTON_H 21
#define LIGHTS_BUTTON_R 5
//define position of EACH ONE switch in showLightsControlPanel()
#define LIGHT_B_1_POZ_Y (STRING_LIGHTS_1_POZ_Y+5)
#define LIGHT_B_2_POZ_Y (STRING_LIGHTS_2_POZ_Y+5)
#define LIGHT_B_3_POZ_Y (STRING_LIGHTS_3_POZ_Y+5)
#define LIGHT_B_4_POZ_Y (STRING_LIGHTS_4_POZ_Y+5)


//
// Variables
//

// Structure of MenuTFT current state
typedef enum
{
	MENUTFT_INIT, 			// Build GUI
	MENUTFT_PARAMETERS, 	// Read parameters
	MENUTFT_SWITCH,			// Show current switch state, and possibility to change them
	MENUTFT_LIGHTS 			// Show current lights state, and possibility to change them
} MenuTFTState;

void MenuTFT(void);
void TouchParametersActivity(void);
void TouchSwitchActivity(void);
void TouchLightsActivity(void);

#endif /* INC_MENUTFT_H_ */
