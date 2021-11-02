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
char Message[BUFFOR_SIZE]; // Transmit buffer
char MyName[32] = {"No Name"}; // Name string
uint8_t ChangingStateFlag;


/*
 * Parsing headers:
 * 		LED=1\n 		// LED On
 * 		LED=0\n 		// LED Off
 * 		STATE=?\n		// Jaki jest stan uC
 * 		TEMP=1?\n		// Jaka jest temperatura 1 czujnika
 * 		PRES=1?\n		// Jakie jest cisnienie 1 czujnika
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
	  else if(strcmp(ParsePointer, "STATE") == 0)
	  {
		  UART_ParseStatus();
	  }
	  else if(strcmp(ParsePointer, "TEMP") == 0)
	  {
		  UART_ParseTemp();
	  }
	  else if(strcmp(ParsePointer, "PRES") == 0)
	  {
	  	  UART_ParsePres();
	  }
	  else if(strcmp(ParsePointer, "CHSTATE") == 0)
	  {
	  	  UART_ParseChangeRelayState();
	  }
	}
}




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
			HAL_GPIO_WritePin(USER_BRD_LED1_GPIO_Port, USER_BRD_LED1_Pin, GPIO_PIN_RESET);
			UARTDMA_Print(&huartdma2, "LED On\r\n");

		}
		else if(LedState == 0) // LED OFF
		{
			HAL_GPIO_WritePin(USER_BRD_LED1_GPIO_Port, USER_BRD_LED1_Pin, GPIO_PIN_SET);
			UARTDMA_Print(&huartdma2, "LED Off\r\n");
		}
		else // Wrong state number
		{
			UARTDMA_Print(&huartdma2, "LED wrong value. Use 0 or 1.\r\n");
		}
	}
}


///////////////////////////////////

void UART_ParseStatus()
{
	char* ParsePointer = strtok(NULL, ",");
	char SourceState[SOURCE_STATE_LENGTH] = {0};

	if(strlen(ParsePointer) > 0) // If string exists
		{
			if(ParsePointer[0] == '?') // jesli to zapytanie o stan
			{
				PodajStatusRoutine();
			}
			else //jesli nie ma '?' tzn, ze podaje swoj stan
			{
				for(uint8_t i = 0 ; i < SOURCE_STATE_LENGTH ; i++)
				{
					SourceState[i] = ParsePointer[i];
				}
			}
			SourceState[1] = SourceState[1];


}
}

void UART_ParseTemp()
{

}

void UART_ParsePres()
{

}

void UART_ParseChangeRelayState()
{

}

//////////////////////////////////////

void IdleRoutine()
{

}

void PodajStatusRoutine()
{

}

void PodajTemperatureRoutine(uint8_t NrCzujnika)
{

}

void PodajCisnienieRoutine()
{

}

void ZmienStanPrzekRoutine(uint8_t NrPrzekaznika, uint8_t Stan)
{

}
