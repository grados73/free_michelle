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
	}
}

void LeftMotorMotion(uint8_t MotorSpeed, uint8_t MotorDirection)
{
	if(MotorDirection == 1) // go forward
	{

	}
	else if(MotorDirection == 0) //go back
	{
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
	}

	if(MotorSpeed > 100) ;

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


}

void GoBackRoutine()
{
	//
	//ROUTINE
	//


	//
	//CHANGINT SeldDriveStatus
	//

}
void TurningRoutine()
{
	//
	//ROUTINE
	//


	//
	//CHANGINT SeldDriveStatus
	//



}
