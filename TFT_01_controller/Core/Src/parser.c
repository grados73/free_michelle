/*
 * parser.c
 *
 *  Created on: Jul 7, 2021
 *      Author: grad_
 */
#include "main.h"
#include "parser.h"
#include "functions.h"

CONTROLLER_STATE ControlerRegulator;
uint8_t AqaParameters[3];

void SwitchControllerState()
{
	switch(ControlerRegulator){
		case IDLE:
			IdleRoutine(AqaParameters);
			break;
		case INITIALIZATION:
			InitializationRoutine(AqaParameters);
			break;
		case PARAMETERS:
			ParametersRoutine(AqaParameters);
			break;
		case SW_CONTROLLING:
			SwitchControlingRoutine(AqaParameters);
			break;
		case LIGHT_CONTROLLING:
			LightControllingRoutine(AqaParameters);
			break;
		case LIGHT_TIMERS:
			LightTimersRoutine(AqaParameters);
			break;
		case CONNECTION_ERROR:
			ConnectionErrorRoutine(AqaParameters);
			break;
		default:
			break;

		}
}

void IdleRoutine(uint8_t * AqaParameters)
{

}

void InitializationRoutine(uint8_t * AqaParameters)
{
	// TODO - DODAĆ OBSŁUGĘ RETURNA, JAK ZWRACA 1 TO PRZECHODZI DO PARAMETERS A JAK NIE TO DO ERRORS
	system_init();
}

void ParametersRoutine(uint8_t * AqaParameters)
{

}

void SwitchControlingRoutine(uint8_t * AqaParameters)
{

}

void LightControllingRoutine(uint8_t * AqaParameters)
{

}

void LightTimersRoutine(uint8_t * AqaParameters)
{

}

void ConnectionErrorRoutine(uint8_t * AqaParameters)
{

}


