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
#include "menuTFT.h"

extern UARTDMA_HandleTypeDef huartdma2;
char Message[BUFFOR_SIZE]; // Transmit buffer
char MyName[32] = {"SLAVE1"}; // Name string
uint8_t ChangingStateFlag;
extern struct Measurements BMPResults;

extern MenuTFTState State;

float CTemp = 0.0;
float CPres = 0.0;
float CTempWew = 0.0;
uint8_t CWaterLvl = 0;
uint8_t Time[3] = {0,0,0};

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
		  UART_ParseAnswPres();
	  }
	  else if (strcmp(ParsePointer, "ACHSTATE") == 0)
	  {
		  UART_ParseAnswChangeRelayState();
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


void UART_ParseAnswTemp()
{
	char* ParsePointer = strtok(NULL, ",");
	uint8_t Len;
	if(strlen(ParsePointer) > 0) // If string exists
	{
		CTemp = atof(ParsePointer); // If there are no chars, change string to integer

		//Only if on the screen are Parameters, update current Temp
		if(State == MENUTFT_PARAMETERS)
		{
			Len = sprintf((char*)Msg, "Temp. zewn: %.2f`C", CTemp);
			EF_PutString(Msg, TEMP_ZEW_POZ_X, TEMP_ZEW_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);
		}
		UARTDMA_Print(&huartdma2, "TEMPUPSUC\n");
		Len++;
	}
}

void UART_ParseAnswPres()
{
	char* ParsePointer = strtok(NULL, ",");
	uint8_t Len;
	if(strlen(ParsePointer) > 0) // If string exists
	{
		CPres = atof(ParsePointer); // If there are no chars, change string to integer

		//Only if on the screen are Parameters, update current Presure
		if(State == MENUTFT_PARAMETERS)
		{
			Len = sprintf((char*)Msg, "Ciśnienie: %.1fhPa", CPres);
			EF_PutString(Msg, CISN_POZ_X, CISN_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);
		}
		UARTDMA_Print(&huartdma2, "PRESUPSUC\n");
		Len++;
	}
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


