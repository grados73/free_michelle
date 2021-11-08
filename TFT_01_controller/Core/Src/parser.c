/**
  ******************************************************************************
  * @file           : parser.c
  * @project		: free_michelle
  * @author			: grados73 - https://github.com/grados73
  * @purpose		: plik z funkcjami parsowania wiadomosci przychodzacych z UART
  ******************************************************************************
  **/
#include "main.h"
#include "parser.h"
#include "string.h"
#include "uartdma.h"
#include "stdlib.h"
#include "stdio.h"
#include "functions.h"

extern UARTDMA_HandleTypeDef huartdma2;
char Message[BUFFOR_SIZE]; // Transmit buffer
char MyName[32] = {"SLAVE1"}; // Name string
uint8_t ChangingStateFlag;
extern struct Measurements BMPResults;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// GLOWNA FUNKCJA PARSOWANIA //////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Parsing headers:
 * 		LED=1\n 		// LED On
 * 		LED=0\n 		// LED Off
 * 		STATE=?\n		// Jaki jest stan uC
 * 		TEMP=1\n		// Jaka jest temperatura 1 czujnika
 * 		PRES=1\n		// Jakie jest cisnienie 1 czujnika
 * 		CHSTATE=1,0\n	// Zmien stan przekaznika 1 na wylaczony
 * 		CHSTATE=2,1\n	// Zmien stan przekaznika 2 na wlaczony
 */

void UART_ParseLine(UARTDMA_HandleTypeDef *huartdma)
{
	char BufferReceive[BUFFOR_SIZE];

	if(!UARTDMA_GetLineFromReceiveBuffer(huartdma, BufferReceive))
	{
		// Header
		char* ParsePointer = strtok(BufferReceive, "="); // LED\0   1\0
		// ParsePointer == LED\0

	  if(strcmp(ParsePointer, "LED") == 0)
	  {
		  UART_ParseLED();
	  }
	  else if (strcmp(ParsePointer, "ASTATE") == 0)
	  {
		  UART_ParseAnswStatus();
	  }
	  else if (strcmp(ParsePointer, "ATEMP") == 0)
	  {
		  UART_ParseAnswTemp();
	  }
	  else if (strcmp(ParsePointer, "APRES") == 0)
	  {
		  void UART_ParseAnswPres();
	  }
	  else if (strcmp(ParsePointer, "ACHSTATE") == 0)
	  {
		  void UART_ParseAnswChangeRelayState();
	  }
	  //TODO: DODAC OBSLUGE PARSOWANIA BLEDOW
	}
}


/////////////////////////////////////////// FUNKCJA PARSOWANIA USER LED ////////////////////////////////////////////////////////////////////////////

void UART_ParseLED()
{
	uint8_t LedState; // Received state variable

	char* ParsePointer = strtok(NULL, ","); // Look for next token or end of string
	// Should be now: ParsePointer == 1'\0'

	if(strlen(ParsePointer) > 0) // If string exists
	{
		if(ParsePointer[0] < '0' || ParsePointer[0] > '9') // Chceck if there are only numbers
		{
			UARTDMA_Print(&huartdma2, LED_FORMAT_ERROR); // Print message
			return;	// And exit parsing
		}

		LedState = atoi(ParsePointer); // If there are no chars, change string to integer

		if(LedState == 1) // LED ON
		{
			HAL_GPIO_WritePin(BP_USER_LED_GPIO_Port, BP_USER_LED_Pin, GPIO_PIN_RESET);
			UARTDMA_Print(&huartdma2, "LED=On\r\n");

		}
		else if(LedState == 0) // LED OFF
		{
			HAL_GPIO_WritePin(BP_USER_LED_GPIO_Port, BP_USER_LED_Pin, GPIO_PIN_SET);
			UARTDMA_Print(&huartdma2, "LED=Off\r\n");
		}
		else // Wrong state number
		{
			UARTDMA_Print(&huartdma2, LED_FORMAT_ERROR);
		}
	}
}

void UART_ParseAnswStatus()
{
	//TODO: Dodac obsluge statusu urzadzenia
}


void UART_ParseAnswTemp(second_uc_data *dane)
{

}

void UART_ParseAnswPres()
{

}

void UART_ParseAnswChangeRelayState()
{

}







///////////////////////////////////////////// MASZYNA STANOW ////////////////////////////////

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


