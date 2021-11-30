/*
 * menuTFT.h
 *
 *  Created on: Nov 29, 2021
 *      Author: grad_
 */

#ifndef INC_MENUTFT_H_
#define INC_MENUTFT_H_

#define RIGHT_BUTTON_X 220
#define RIGHT_BUTTON_Y 216
#define RIGHT_BUTTON_W 100
#define RIGHT_BUTTON_H 20

#define LEFT_BUTTON_X 10
#define LEFT_BUTTON_Y 216
#define LEFT_BUTTON_W 100
#define LEFT_BUTTON_H 20

#define RIGHT_LEFT_BUTTON_R 5

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
