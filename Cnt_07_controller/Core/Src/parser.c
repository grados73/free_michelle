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


/////////////////////////////////////////// FUNKCJA PARSOWANIA STATUSU /////////////////////////////////////////////////////////////////////////////

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


/////////////////////////////////////////// FUNKCJA PARSOWANIA TEMPERATURY /////////////////////////////////////////////////////////////////////////

void UART_ParseTemp()
{
	uint8_t NrCzujnika; // Received state variable

	char* ParsePointer = strtok(NULL, ","); // Look for next token or end of string
	// Should be now: ParsePointer == 1'\0'

	if(strlen(ParsePointer) > 0) // If string exists
	{
		if(ParsePointer[0] < '0' || ParsePointer[0] > '9') // Chceck if there are only numbers
		{
			UARTDMA_Print(&huartdma2, "TEMPFormatErr\n"); // Print message
			return;	// And exit parsing
		}

		NrCzujnika = atoi(ParsePointer); // If there are no chars, change string to integer
		PodajTemperatureRoutine(NrCzujnika);

	}
}


/////////////////////////////////////////// FUNKCJA PARSOWANIA CISNIENIA ///////////////////////////////////////////////////////////////////////////

void UART_ParsePres()
{

	uint8_t NrCzujnika; // Received state variable

	char* ParsePointer = strtok(NULL, ","); // Look for next token or end of string
	// Should be now: ParsePointer == 1'\0'

	if(strlen(ParsePointer) > 0) // If string exists
	{
		if(ParsePointer[0] < '0' || ParsePointer[0] > '9') // Chceck if there are only numbers
		{
			UARTDMA_Print(&huartdma2, "PRESFormatErr\n"); // Print message
			return;	// And exit parsing
		}

		NrCzujnika = atoi(ParsePointer); // If there are no chars, change string to integer
		PodajCisnienieRoutine(NrCzujnika);


	}
}


/////////////////////////////////////////// FUNKCJA PARSOWANIA PRZEKAZNIKOW ////////////////////////////////////////////////////////////////////////

void UART_ParseChangeRelayState()
{
		uint8_t i,j; // Iterators
		float RelayParameters[2]; // Numer Przekaznika, Stan

		for(i = 0; i<2; i++) // 2 parametry sa oczekiwane - numer przekaznika i stan
		{
			char* ParsePointer = strtok(NULL, ","); // Look for next token or end of string

			if(strlen(ParsePointer) > 0) // If string exists
			{
				for(j=0; ParsePointer[j] != 0; j++) // Loop over all chars in current strong-block
				{
					if((ParsePointer[j] < '0' || ParsePointer[j] > '9') && ParsePointer[j] != '.' ) // Check if there are only numbers or dot sign
					{
						sprintf(Message, "CHSTATEFormatErr\n"); // If not, Error message
						UARTDMA_Print(&huartdma2, Message); // Print message
						return;	// And exit parsing
					}

					RelayParameters[i] = atof(ParsePointer); // If there are no chars, change string to integer
				}
			}
			else
			{
				sprintf(Message, "CHSTATEFormatErr\n"); // If not, Error message
				UARTDMA_Print(&huartdma2, Message); // Print message
				return;	// And exit parsing
			}
		}
		ZmienStanPrzekRoutine(RelayParameters[0], RelayParameters[1]);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// FUNKCJE WYKONAWCZE ODPOWIEDZI ////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PodajStatusRoutine()
{
	UARTDMA_Print(&huartdma2, "uC=READY\n");	// TODO: dodac kontrole wszystkich peryferiow i raportowanie o gotowosci
}

void PodajTemperatureRoutine(uint8_t NrCzujnika)
{
	float aktualna_temperatura = 0;

	if(NrCzujnika == 1)
	{
		aktualna_temperatura = BMPResults.Temp;
	}
	sprintf(Message, "ATEMP=%f\n", aktualna_temperatura);
	UARTDMA_Print(&huartdma2, Message);
}

void PodajCisnienieRoutine(uint8_t NrCzujnika)
{
	float aktualne_cisnienie = 0;

	if(NrCzujnika == 1)
	{
		aktualne_cisnienie = BMPResults.Pressure;
	}
	sprintf(Message, "APRES=%f\n", aktualne_cisnienie);
	UARTDMA_Print(&huartdma2, Message);
}

void ZmienStanPrzekRoutine(uint8_t NrPrzekaznika, uint8_t Stan)
{
	uint8_t Przekaznik;
	uint8_t NowyStan;
	Przekaznik = NrPrzekaznika;
	NowyStan = Stan;

	if(NrPrzekaznika == 1)
	{
		if(Stan == 1) HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(RELAY_1_GPIO_Port, RELAY_1_Pin, GPIO_PIN_SET);
	}
	else if(NrPrzekaznika == 2)
	{
		if(Stan == 1) HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(RELAY_2_GPIO_Port, RELAY_2_Pin, GPIO_PIN_SET);
	}
	else if(NrPrzekaznika == 3)
	{
		if(Stan == 1) HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(RELAY_3_GPIO_Port, RELAY_3_Pin, GPIO_PIN_SET);
	}
	else if(NrPrzekaznika == 4)
	{
		if(Stan == 1) HAL_GPIO_WritePin(RELAY_4_GPIO_Port, RELAY_4_Pin, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin(RELAY_4_GPIO_Port, RELAY_4_Pin, GPIO_PIN_SET);
	}
	else
	{
		sprintf(Message, "CHSTATENRErr\n"); // Potwierdzenie wykonania polecenia
		UARTDMA_Print(&huartdma2, Message); // Print message
		return;	// And exit parsing
	}

	sprintf(Message, "CHSTATEDONE=%d,%d\n", Przekaznik, NowyStan); // Potwierdzenie wykonania polecenia
	UARTDMA_Print(&huartdma2, Message); // Print message
}
