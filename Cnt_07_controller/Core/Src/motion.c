/*
 * motion.c
 *
 *  Created on: Feb 2, 2021
 *      Author: grad_
 */
#include "motion.h"

extern UARTDMA_HandleTypeDef huartdma2;
extern char Message[64]; // Transmit buffer
extern uint8_t OdlegloscCm;
uint8_t ObstacleFlag = 0;
AUTONOMOUS_STATE SelfDriveStatus = GOFORWARD;
uint32_t CurrentTime = 0;
uint32_t TurningStartTime = 0;

#define ODLEGLOSCODBICIOWA 8
#define ODLEGLOSCCOFANIA 12
#define CZASSKRECANIA 1000

void ToggleUserLed(uint8_t State)
{
	uint8_t LedStatus = State;
	if(LedStatus == 0)
	{
	}
	else if(LedStatus == 1)
	{
//		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
	}
}

void LeftMotorMotion(uint8_t MotorSpeed, uint8_t MotorDirection)
{
	if(MotorDirection == 1) // go forward
	{

	}
	else if(MotorDirection == 0) //go back
	{
//		HAL_GPIO_WritePin(BIN1_HBridge_GPIO_Port, BIN1_HBridge_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(BIN2_HBridge_GPIO_Port, BIN2_HBridge_Pin, GPIO_PIN_SET);
	}

	if(MotorSpeed > 100) MotorSpeed = 100;
}

void RightMotorMotion(uint8_t MotorSpeed, uint8_t MotorDirection)
{
	if(MotorDirection == 1) // go forward
	{

	}
	else if(MotorDirection == 0) //go back
	{
//		HAL_GPIO_WritePin(AIN1_HBridge_GPIO_Port, AIN1_HBridge_Pin, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(AIN2_HBridge_GPIO_Port, AIN2_HBridge_Pin, GPIO_PIN_SET);
	}

	if(MotorSpeed > 100) MotorSpeed = 100;
//	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, (MotorSpeed)); // ADD CALIBRATION SOMEDAY !

}

void AutonomousMode()
{
	switch(SelfDriveStatus){
		case GOFORWARD:
			GoForwardRoutine();
			break;
		case GOBACK:
			GoBackRoutine();
			break;
		case TURNING:
			TurningRoutine();
			break;
		default:
			break;
		}
}

void GoForwardRoutine()
{
	//
	//ROUTINE
	//
	LeftMotorMotion(80,1);
	RightMotorMotion(80,1);

	//
	//CHANGINT SeldDriveStatus
	//
	if(OdlegloscCm <= ODLEGLOSCODBICIOWA)
	{
		SelfDriveStatus = GOBACK;
	}

}

void GoBackRoutine()
{
	//
	//ROUTINE
	//
	LeftMotorMotion(40,0);
	RightMotorMotion(40,0);

	//
	//CHANGINT SeldDriveStatus
	//
	if(OdlegloscCm >= ODLEGLOSCCOFANIA)
	{
		SelfDriveStatus = TURNING;
		TurningStartTime = HAL_GetTick();
	}

}

void TurningRoutine()
{
	//
	//ROUTINE
	//
	CurrentTime = HAL_GetTick();
	LeftMotorMotion(50,1);
	RightMotorMotion(50,0);

	//
	//CHANGINT SeldDriveStatus
	//
	if((CurrentTime - TurningStartTime) >= CZASSKRECANIA)
	{
		SelfDriveStatus = GOFORWARD;
	}


}
