/*
 * parser.h
 *
 *  Created on: Jan 25, 2021
 *      Author: grad_
 */


#ifndef INC_PARSER_H_
#define INC_PARSER_H_
#include "uartdma.h"

void UART_ParseLine(UARTDMA_HandleTypeDef *huartdma);
void UART_ParseLED();
void UART_ParseMotor();

typedef enum
{
	IDLE = 0, 				//0
	CONSTGO9, 				// 1 THE VEHICLE IS GOING FORWARD 9
	CONSTGO6, 				// 2 THE VEHICLE IS GOING FORWARD 9
	CONSTBACK13, 			// 3 THE VEHICLE IS GOING BACK 13
	CONSTBACK16, 			// 4 THE VEHICLE IS GOING BACK 16
	GOANDTURNINGLEFT, 		// 5
	GOANDTURNINGRIGHT,	    // 6
	TURNINGLEFT,   			// 7
	TURNINGRIGHT,  		    // 8
	AUTONOMOUS  			// 9 THE VEHICLE IS SELF-DRIVING CAR
} MOTION_STATE;

typedef struct motors_struct
{
	MOTION_STATE	State;
	uint8_t			LeftPWM;
	uint8_t			RightPWM;
	uint8_t			AIN1;
	uint8_t			AIN2;
	uint8_t			BIN1;
	uint8_t			BIN2;
	uint8_t			STBY;
}HBridge;

void SwitchMotorRegular();

void IdleRoutine(uint8_t * MotorParameters);
void ConstGo9Routine(uint8_t * MotorParameters);
void ConstGo6Routine(uint8_t * MotorParameters);
void ConstBack13Routine(uint8_t * MotorParameters);
void Constback16Routine(uint8_t * MotorParameters);
void GoAndTurningLeftRoutine(uint8_t * MotorParameters);
void GoAndTurningRightRoutine(uint8_t * MotorParameters);
void TurningLeftRoutine(uint8_t * MotorParameters);
void TurningRightRoutine(uint8_t * MotorParameters);
void AutonomousRoutine(uint8_t * MotorParameters);
#endif /* INC_PARSER_H_ */
