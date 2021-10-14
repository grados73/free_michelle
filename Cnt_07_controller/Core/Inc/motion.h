/*
 * motion.h
 *
 *  Created on: Feb 2, 2021
 *      Author: grad_
 */
#include "main.h"
#include "string.h"
#include "uartdma.h"
#include "stdlib.h"
#include "stdio.h"
#include "tim.h"


#ifndef INC_MOTION_H_
#define INC_MOTION_H_

typedef enum
{
	GOFORWARD, 				// 1 THE VEHICLE IS GOING FORWARD 9
	GOBACK, 				// 2 THE VEHICLE IS GOING BACK
	TURNING 				// 3 THE VEHICLE IS TURNING

} AUTONOMOUS_STATE;

void ToggleUserLed(uint8_t State);
void LeftMotorMotion(uint8_t MotorSpeed, uint8_t MotorDirection);
void RightMotorMotion(uint8_t MotorSpeed, uint8_t MotorDirection);
void GoForwardRoutine();
void GoBackRoutine();
void TurningRoutine();
void AutonomousMode();



#endif /* INC_MOTION_H_ */
