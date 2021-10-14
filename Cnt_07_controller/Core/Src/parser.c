/*
 * parser.c
 *
 *  Created on: Jan 25, 2021
 *      Author: grad_
 */


#include "main.h"
#include "parser.h"
#include "string.h"
#include "uartdma.h"
#include "stdlib.h"
#include "stdio.h"
#include "motion.h"

extern UARTDMA_HandleTypeDef huartdma2;
char Message[64]; // Transmit buffer
char MyName[32] = {"No Name"}; // Name string
MOTION_STATE MotorRegulator;
uint8_t MotorParameters[3];	 // Left motor, Right motor, Direction of movement
uint8_t ChangingStateFlag;

/*
 * Parsing headers:
 * 		LED=1\n 	// LED On
 * 		LED=0\n 	// LED Off
 * 		ENV=X,Y,Z\n // X - temperature, Y - humidity, Z - pressure
 * 		NAME=X\n	// Change name for X
 * 		NAME=?\n	// introduce yourself
 */
void UART_ParseLine(UARTDMA_HandleTypeDef *huartdma)
{
	char BufferReceive[64];

	if(!UARTDMA_GetLineFromReceiveBuffer(huartdma, BufferReceive))
	{
		// Header
		char* ParsePointer = strtok(BufferReceive, "="); // LED\0   1\0
		// ParsePointer == LED\0

	  if(strcmp(ParsePointer, "LED") == 0)
	  {
		  UART_ParseLED();
	  }
	  else if(strcmp(ParsePointer, "MOTOR") == 0)
	  {
		  UART_ParseMotor();
		  ChangingStateFlag = 1;
	  }
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// TURNING ON / OFF TESTING LED ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * 		LED=1\n 	// LED On
 * 		LED=0\n 	// LED Off
 */
void UART_ParseLED()
{
	uint8_t LedState; // Received state variable

	char* ParsePointer = strtok(NULL, ","); // Look for next token or end of string
	// Should be now: ParsePointer == 1'\0'

	if(strlen(ParsePointer) > 0) // If string exists
	{
		if(ParsePointer[0] < '0' || ParsePointer[0] > '9') // Chceck if there are only numbers
		{
			UARTDMA_Print(&huartdma2, "LED wrong value. Don't use letters dude!\r\n"); // Print message
			return;	// And exit parsing
		}

		LedState = atoi(ParsePointer); // If there are no chars, change string to integer

		if(LedState == 1) // LED ON
		{
			ToggleUserLed(1);
			UARTDMA_Print(&huartdma2, "LED On\r\n");

		}
		else if(LedState == 0) // LED OFF
		{
			ToggleUserLed(0);
			UARTDMA_Print(&huartdma2, "LED Off\r\n");
		}
		else // Wrong state number
		{
			UARTDMA_Print(&huartdma2, "LED wrong value. Use 0 or 1.\r\n");
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// CHANGING SPEED OF MOTOR ///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * MOTOR=L,R,D\0 // L - left motor speed, R - right motor speed, D - direction of motor movement
 */
void UART_ParseMotor()
{
	uint8_t i,j; // Iterators


	for(i = 0; i<3; i++) // 3 parameters are expected
	{
		char* ParsePointer = strtok(NULL, ","); // Look for next token or end of string

		if(strlen(ParsePointer) > 0) // If string exists
		{
			for(j=0; ParsePointer[j] != 0; j++) // Loop over all chars in current strong-block
			{
				MotorParameters[i] = atoi(ParsePointer); // If there are no chars, change string to integer
			}
		}
		else
		{
			sprintf(Message, "Motor too less values. MOTOR=L,R,D\\n\r\n"); // If not, Error message
			UARTDMA_Print(&huartdma2, Message); // Print message
			return;	// And exit parsing
		}
	}


//	// Print back received data
//	sprintf(Message, "Left Motor: %d\r\n", MotorParameters[0]);
//	UARTDMA_Print(&huartdma2, Message);
//
//	sprintf(Message, "Right Motor: %d\r\n", MotorParameters[1]);
//	UARTDMA_Print(&huartdma2, Message);
//
//	sprintf(Message, "Direction: %d\r\n", MotorParameters[2]);
//	UARTDMA_Print(&huartdma2, Message);

	SwitchMotorRegular();


}

void SwitchMotorRegular()
{
	switch(MotorRegulator){
	case IDLE:
		IdleRoutine(MotorParameters);
		break;
	case CONSTGO9:
		ConstGo9Routine(MotorParameters);
		break;
	case CONSTGO6:
		ConstGo6Routine(MotorParameters);
		break;
	case CONSTBACK13:
		ConstBack13Routine(MotorParameters);
		break;
	case CONSTBACK16:
		Constback16Routine(MotorParameters);
		break;
	case GOANDTURNINGLEFT:
		GoAndTurningLeftRoutine(MotorParameters);
		break;
	case GOANDTURNINGRIGHT:
		GoAndTurningRightRoutine(MotorParameters);
		break;
	case TURNINGLEFT:
		TurningLeftRoutine(MotorParameters);
		break;
	case TURNINGRIGHT:
		TurningRightRoutine(MotorParameters);
		break;
	case AUTONOMOUS:
		AutonomousRoutine(MotorParameters);
		break;
	default:
		break;

	}
}

void IdleRoutine(uint8_t * MotorParameters)
{
	// Control signals for motors
	LeftMotorMotion(0,1);
	RightMotorMotion(0,1);

	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "IDLE State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO9;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 6)) // go forward with medium speed - "MOTOR=0,0,6"
	{
		MotorRegulator = CONSTGO6;
	}

	else if((MotorParameters[0] == 1) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=1,0,0"
	{
		MotorRegulator = TURNINGLEFT;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 1) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,1,0"
	{
		MotorRegulator = TURNINGRIGHT;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 16)) // go back with max speed - "MOTOR=0,0,16"
	{
		MotorRegulator = CONSTBACK16;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 13)) // go back with medium speed - "MOTOR=0,0,13"
	{
		MotorRegulator = CONSTBACK13;
	}
	if((MotorParameters[0] == 9) & (MotorParameters[1] == 9) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = AUTONOMOUS;
	}

}

void ConstGo9Routine(uint8_t * MotorParameters)
{
	// Control signals for motors
	LeftMotorMotion(100,1);
	RightMotorMotion(100,1);
	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "CONST Vmax GO State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,0,0"
	{
		MotorRegulator = IDLE;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 6)) // go forward with slower speed - "MOTOR=0,0,6"
	{
		MotorRegulator = CONSTGO6;
	}
	else if((MotorParameters[0] == 1) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=1,0,0"
	{
		MotorRegulator = GOANDTURNINGLEFT;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 1) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,1,0"
	{
		MotorRegulator = GOANDTURNINGRIGHT;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 16)) // go back with max speed - "MOTOR=0,0,16"
	{
		MotorRegulator = CONSTBACK16;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 13)) // go back with medium speed - "MOTOR=0,0,13"
	{
		MotorRegulator = CONSTBACK13;
	}

	else if((MotorParameters[0] == 1) & (MotorParameters[1] == 0) & ((MotorParameters[2] == 6) | (MotorParameters[2] == 9)))
	{																				// go forward with medium speed and turning left - "MOTOR=1,0,9"
		MotorRegulator = GOANDTURNINGLEFT;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 1) & ((MotorParameters[2] == 6) | (MotorParameters[2] == 9)))
	{																				// go forward with medium speed and turning right - "MOTOR=1,0,9"
		MotorRegulator = GOANDTURNINGRIGHT;
	}
	if((MotorParameters[0] == 9) & (MotorParameters[1] == 9) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = AUTONOMOUS;
	}

}

void ConstGo6Routine(uint8_t * MotorParameters)
{
	// Control signals for motors
	LeftMotorMotion(50,1);
	RightMotorMotion(50,1);

	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "CONST Vmed GO State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,0,0"
	{
		MotorRegulator = IDLE;
	}
	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 9)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO9;
	}

	else if((MotorParameters[0] == 1) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=1,0,0"
	{
		MotorRegulator = GOANDTURNINGLEFT;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 1) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,1,0"
	{
		MotorRegulator = GOANDTURNINGRIGHT;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 16)) // go back with max speed - "MOTOR=0,0,16"
	{
		MotorRegulator = CONSTBACK16;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 13)) // go back with medium speed - "MOTOR=0,0,13"
	{
		MotorRegulator = CONSTBACK13;
	}
	else if((MotorParameters[0] == 1) & (MotorParameters[1] == 0) & ((MotorParameters[2] == 6) | (MotorParameters[2] == 9)))
	{																				// go forward with medium speed and turning left - "MOTOR=1,0,9"
		MotorRegulator = GOANDTURNINGLEFT;
	}
	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 1) & ((MotorParameters[2] == 6) | (MotorParameters[2] == 9)))
	{																				// go forward with medium speed and turning right - "MOTOR=1,0,9"
		MotorRegulator = GOANDTURNINGRIGHT;
	}
	if((MotorParameters[0] == 9) & (MotorParameters[1] == 9) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = AUTONOMOUS;
	}

}

void ConstBack13Routine(uint8_t * MotorParameters)
{
	// Control signals for motors
	LeftMotorMotion(40,0);
	RightMotorMotion(40,0);

	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "CONST Vmed GoBack State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,0,0"
	{
		MotorRegulator = IDLE;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 16)) // go back with max speed - "MOTOR=0,0,16"
	{
		MotorRegulator = CONSTBACK16;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 6)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO6;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 9)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO9;
	}

	if((MotorParameters[0] == 9) & (MotorParameters[1] == 9) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = AUTONOMOUS;
	}

}

void Constback16Routine(uint8_t * MotorParameters)
{
	// Control signals for motors
	LeftMotorMotion(80,0);
	RightMotorMotion(80,0);

	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "CONST Vmax GoBack State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,0,0"
	{
		MotorRegulator = IDLE;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 13)) // go back with max speed - "MOTOR=0,0,16"
	{
		MotorRegulator = CONSTBACK13;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 6)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO6;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 9)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO9;
	}

	if((MotorParameters[0] == 9) & (MotorParameters[1] == 9) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = AUTONOMOUS;
	}
}

void GoAndTurningLeftRoutine(uint8_t * MotorParameters)
{
	// Control signals for motors
	LeftMotorMotion(10,1);
	RightMotorMotion(100,1);

	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "GO and Turning Left State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,0,0"
	{
		MotorRegulator = IDLE;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 6)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO6;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 9)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO9;
	}


	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 13)) // go back with max speed - "MOTOR=0,0,13"
	{
		MotorRegulator = CONSTBACK13;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 1) & ((MotorParameters[2] == 6) | (MotorParameters[2] == 9)))
	{																				// go forward with medium speed and turning right - "MOTOR=1,0,9"
		MotorRegulator = GOANDTURNINGRIGHT;
	}

	if((MotorParameters[0] == 9) & (MotorParameters[1] == 9) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = AUTONOMOUS;
	}
}

void GoAndTurningRightRoutine(uint8_t * MotorParameters)
{
	// Control signals for motors
	LeftMotorMotion(100,1);
	RightMotorMotion(10,1);

	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "GO and Turning Right State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,0,0"
	{
		MotorRegulator = IDLE;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 6)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO6;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 9)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO9;
	}


	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 13)) // go back with max speed - "MOTOR=0,0,13"
	{
		MotorRegulator = CONSTBACK13;
	}

	else if((MotorParameters[0] == 1) & (MotorParameters[1] == 0) & ((MotorParameters[2] == 6) | (MotorParameters[2] == 9)))
	{																				// go forward with medium speed and turning left - "MOTOR=1,0,9"
		MotorRegulator = GOANDTURNINGLEFT;
	}

	if((MotorParameters[0] == 9) & (MotorParameters[1] == 9) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = AUTONOMOUS;
	}

}

void TurningLeftRoutine(uint8_t * MotorParameters)
{
	// Control signals for motors
	LeftMotorMotion(100,0);
	RightMotorMotion(100,1);

	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "Turning Left State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,0,0"
	{
		MotorRegulator = IDLE;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 6)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO6;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 9)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO9;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 1) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,1,0"
	{
		MotorRegulator = TURNINGRIGHT;
	}

	if((MotorParameters[0] == 9) & (MotorParameters[1] == 9) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = AUTONOMOUS;
	}

}

void TurningRightRoutine(uint8_t * MotorParameters)
{
	// Control signals for motors
	LeftMotorMotion(100,1);
	RightMotorMotion(100,0);

	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "Turning Right State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,0,0"
	{
		MotorRegulator = IDLE;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 6)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO6;
	}

	else if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 9)) // go forward with faster speed - "MOTOR=0,0,9"
	{
		MotorRegulator = CONSTGO9;
	}

	else if((MotorParameters[0] == 1) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,1,0"
	{
		MotorRegulator = TURNINGLEFT;
	}

	if((MotorParameters[0] == 9) & (MotorParameters[1] == 9) & (MotorParameters[2] == 9)) // go forward with max speed - "MOTOR=0,0,9"
	{
		MotorRegulator = AUTONOMOUS;
	}
}

void AutonomousRoutine(uint8_t * MotorParameters)
{
	AutonomousMode();
	if(ChangingStateFlag)
	{
		UARTDMA_Print(&huartdma2, "Self-Driving State\r\n");
		ChangingStateFlag = 0;
	}

	if((MotorParameters[0] == 0) & (MotorParameters[1] == 0) & (MotorParameters[2] == 0)) // go forward with max speed - "MOTOR=0,0,0"
	{
		MotorRegulator = IDLE;
	}

}
