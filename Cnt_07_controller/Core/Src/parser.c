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

union comm_frame_union frame_current;

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
//			switch(frame_current.message_type){
//				case 0:
//					IdleRoutine();
//					break;
//				case 1://Podaj swój status
//					PodajStatusRoutine();
//					break;
//				case 2://Podaj aktualną temperaturę czujnik 1
//					PodajTemperatureRoutine(1);
//					break;
//				case 3://Podaj aktualną temperaturę czujnik 2
//					PodajTemperatureRoutine(2);
//					break;
//				case 4://Podaj aktualne ciśnienie atmosferyczne.
//					PodajCisnienieRoutine();
//					break;
//				case 10://Włącz przekaźnik 1
//					ZmienStanPrzekRoutine(1, 1);
//					break;
//				case 11://Wyłącz przekaźnik 1
//					ZmienStanPrzekRoutine(1, 0);
//					break;
//				case 12://Włącz przekaźnik 2
//					ZmienStanPrzekRoutine(2, 1);
//					break;
//				case 13://Wyłącz przekaźnik 2
//					ZmienStanPrzekRoutine(2, 0);
//					break;
//				default:
//					break;




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
			//TO DO! dodać zmianę stanu diody
			UARTDMA_Print(&huartdma2, "LED On\r\n");

		}
		else if(LedState == 0) // LED OFF
		{
			//TO DO! dodać zmianę stanu diody
			UARTDMA_Print(&huartdma2, "LED Off\r\n");
		}
		else // Wrong state number
		{
			UARTDMA_Print(&huartdma2, "LED wrong value. Use 0 or 1.\r\n");
		}
	}
}


///////////////////////////////////
void UART_ParseLED()
{

}

void UART_ParseStatus()
{

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
