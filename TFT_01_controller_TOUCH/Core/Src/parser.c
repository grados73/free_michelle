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
char MyName[32] = {"MASTER1"}; // Name string
uint8_t ChangingStateFlag;
extern struct Measurements BMPResults;

extern MenuTFTState State;

float CTemp = 0.0;
float CPres = 0.0;
float CTempWew = 0.0;
uint8_t CWaterLvl = 0;
uint8_t Time[3] = {0,0,0};
uint8_t SwitchesButtonState[4] = {0,0,0,0};
uint8_t LightsButtonState[4] = {0,0,0,0};
uint8_t ActivityButtonState[2] = {0,0};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// MAIN PARSING FUNCTION //////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Parsing headers:
 * 		LED=1\n 			// LED On
 * 		LED=0\n 			// LED Off
 * 		STATE=?\n			// Jaki jest stan uC
 * 		TEMP=1\n			// Jaka jest temperatura 1 czujnika
 * 		PRES=1\n			// Jakie jest cisnienie 1 czujnika
 * 		CHSTATE=1,0\n		// Zmien stan przekaznika 1 na wylaczony
 * 		CHSTATE=2,1\n		// Zmien stan przekaznika 2 na wlaczony
 * 		ASTATESTATUS=?\n	// Podaj stan wszystkich przekaznikow
 *
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
	  else if (strcmp(ParsePointer, "ATEMP") == 0) // Answear about current Temperature
	  {
		  UART_ParseAnswTemp();
	  }
	  else if (strcmp(ParsePointer, "APRES") == 0) // Answear about current Presure
	  {
		  UART_ParseAnswPres();
	  }
	  else if (strcmp(ParsePointer, "ACHSTATE") == 0) // Answear on change status order
	  {
		  UART_ParseAnswChangeRelayState();
	  }
	  else if (strcmp(ParsePointer, "ACHLIGHT") == 0) // Answear on change status order
	  {
		  UART_ParseAnswChangeLightState();
	  }
	  else if (strcmp(ParsePointer, "ASTATESTATUS") == 0) // Answear about current Switch Status
	  {
		  UART_ParseAnswRelayStateStatus();
	  }
	  else if (strcmp(ParsePointer, "ALIGHTSSTATUS=?\n") == 0) // Answear about current Switch Status
	  {
		  UART_ParseAnswLightsStateStatus();
	  }

	  //TODO: DODAC OBSLUGE PARSOWANIA BLEDOW
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// HANDLING PARSING FUNCTION //////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Parsowanie testowej funkcji od LED
// "LED=1\n"
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

//
// Parsing information about current second uC state
//"ASTATE=1\n"
void UART_ParseAnswStatus()
{
	//TODO: Dodac obsluge statusu urzadzenia
}

//
// Parsing information about current temperature
//"ATEMP=23.45000"
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
			Len = sprintf((char*)Msg, "Temp. zewn: %.2f`C ", CTemp);
			EF_PutString(Msg, TEMP_ZEW_POZ_X, TEMP_ZEW_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);
		}
		UARTDMA_Print(&huartdma2, "TEMPUPSUC\n");
		Len++;
	}
}

//
// Parsing information about current presure
//"APRES=1014.200\n"
void UART_ParseAnswPres()
{
	char* ParsePointer = strtok(NULL, ",");
	uint8_t Len;
	if(strlen(ParsePointer) > 0) // If string exists
	{
		CPres = atof(ParsePointer); // If there are no chars, change string to integer

		//Only if on the screen are Parameters, update current Pressure
		if(State == MENUTFT_PARAMETERS)
		{
			Len = sprintf((char*)Msg, "Ciśnienie: %.1fhPa ", CPres);
			EF_PutString(Msg, CISN_POZ_X, CISN_POZ_Y, ILI9341_BLACK, BG_COLOR, ILI9341_LIGHTGREY);
		}
		UARTDMA_Print(&huartdma2, "PRESUPSUC\n");
		Len++;
	}
}



void UART_ParseAnswChangeRelayState()
{
	//TODO!
}

void UART_ParseAnswChangeLightState()
{
	//TODO!
}

//
// Parsing information about current state of switch
// "ASTATESTATUS=0,1,1,0\n" // Switch1-> 0, Switch2 -> 1, Switch3 -> 1, Switch4 -> 0
void UART_ParseAnswRelayStateStatus()
{
	uint8_t i,j; // Iterators

		for(i = 0; i<4; i++) // 4 parameters are expected
		{
			char* ParsePointer = strtok(NULL, ","); // Look for next token or end of string

			if(strlen(ParsePointer) > 0) // If string exists
			{
				for(j=0; ParsePointer[j] != 0; j++) // Loop over all chars in current strong-block
				{
					if((ParsePointer[j] < '0' || ParsePointer[j] > '9') && ParsePointer[j] != '.' ) // Check if there are only numbers or dot sign
					{
						sprintf(Message, "ERROR_WRONG_VALUE\n"); // If not, Error message
						UARTDMA_Print(&huartdma2, Message); // Print message
						return;	// And exit parsing
					}

					SwitchesButtonState[i] = atof(ParsePointer); // If there are no chars, change string to integer
				}
			}
			else
			{
				sprintf(Message, "ERROR_TOO_LESS_PARAMETERS\n"); // If not, Error message
				UARTDMA_Print(&huartdma2, Message); // Print message
				return;	// And exit parsing
			}
		}
}

//
// Parsing information about current state of lights
// "ALIGHTSSTATUS=0,1,1,0\n" // Light1-> 0, Light2 -> 1, Light3 -> 1, Light4 -> 0
void UART_ParseAnswLightsStateStatus()
{
	uint8_t i,j; // Iterators

			for(i = 0; i<4; i++) // 4 parameters are expected
			{
				char* ParsePointer = strtok(NULL, ","); // Look for next token or end of string

				if(strlen(ParsePointer) > 0) // If string exists
				{
					for(j=0; ParsePointer[j] != 0; j++) // Loop over all chars in current strong-block
					{
						if((ParsePointer[j] < '0' || ParsePointer[j] > '9') && ParsePointer[j] != '.' ) // Check if there are only numbers or dot sign
						{
							sprintf(Message, "ERROR_WRONG_VALUE\n"); // If not, Error message
							UARTDMA_Print(&huartdma2, Message); // Print message
							return;	// And exit parsing
						}

						LightsButtonState[i] = atof(ParsePointer); // If there are no chars, change string to integer
					}
				}
				else
				{
					sprintf(Message, "ERROR_TOO_LESS_PARAMETERS\n"); // If not, Error message
					UARTDMA_Print(&huartdma2, Message); // Print message
					return;	// And exit parsing
				}
			}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////// ASK FOR INFORMATION //////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t SendComand(uint8_t Command)
{
	uint8_t SW_Command = Command;

	switch(SW_Command)
		{
		case UCMD_LED_ON:
			UARTDMA_Print(&huartdma2, "LED=1\n");
			break;
		case UCMD_LED_OFF:
			UARTDMA_Print(&huartdma2, "LED=0\n");
			break;
		case UCMD_STATE_ASK:
			UARTDMA_Print(&huartdma2, "STATE=?\n");
			break;
		case UCMD_TEMP_1:
			UARTDMA_Print(&huartdma2, "TEMP=1\n");
			break;
		case UCMD_PRES_1:
			UARTDMA_Print(&huartdma2, "PRES=1\n");
			break;
		case UCMD_RELAY_1_ON:
			UARTDMA_Print(&huartdma2, "CHSTATE=1,1\n");
			break;
		case UCMD_RELAY_1_OFF:
			UARTDMA_Print(&huartdma2, "CHSTATE=1,0\n");
			break;
		case UCMD_RELAY_2_ON:
			UARTDMA_Print(&huartdma2, "CHSTATE=2,1\n");
			break;
		case UCMD_RELAY_2_OFF:
			UARTDMA_Print(&huartdma2, "CHSTATE=2,0\n");
			break;
		case UCMD_RELAY_3_ON:
			UARTDMA_Print(&huartdma2, "CHSTATE=3,1\n");
			break;
		case UCMD_RELAY_3_OFF:
			UARTDMA_Print(&huartdma2, "CHSTATE=3,0\n");
			break;
		case UCMD_RELAY_4_ON:
			UARTDMA_Print(&huartdma2, "CHSTATE=4,1\n");
			break;
		case UCMD_RELAY_4_OFF:
			UARTDMA_Print(&huartdma2, "CHSTATE=4,0\n");
			break;
		case UCMD_RELAY_SCHOW_ALL:
			UARTDMA_Print(&huartdma2, "STATESTATUS=?\n");
			break;
		case UCMD_LIGHT_1_ON:
			UARTDMA_Print(&huartdma2, "CHLIGHT=1,1\n");
			break;
		case UCMD_LIGHT_1_OFF:
			UARTDMA_Print(&huartdma2, "CHLIGHT=1,0\n");
			break;
		case UCMD_LIGHT_2_ON:
			UARTDMA_Print(&huartdma2, "CHLIGHT=2,1\n");
			break;
		case UCMD_LIGHT_2_OFF:
			UARTDMA_Print(&huartdma2, "CHLIGHT=2,0\n");
			break;
		case UCMD_LIGHT_3_ON:
			UARTDMA_Print(&huartdma2, "CHLIGHT=3,1\n");
			break;
		case UCMD_LIGHT_3_OFF:
			UARTDMA_Print(&huartdma2, "CHLIGHT=3,0\n");
			break;
		case UCMD_LIGHT_4_ON:
			UARTDMA_Print(&huartdma2, "CHLIGHT=4,1\n");
			break;
		case UCMD_LIGHT_4_OFF:
			UARTDMA_Print(&huartdma2, "CHLIGHT=4,0\n");
			break;
		case UCMD_LIGHT_SCHOW_ALL:
			UARTDMA_Print(&huartdma2, "LIGHTSSTATUS=?\n");
			break;
		}

	return 1;
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

/*
 * Parsing headers:
 * 		LED=1\n 		// LED On
 * 		LED=0\n 		// LED Off
 * 		STATE=?\n		// Jaki jest stan uC
 * 		TEMP=1\n		// Jaka jest temperatura 1 czujnika
 * 		PRES=1\n		// Jakie jest cisnienie 1 czujnika
 * 		CHSTATE=1,0\n	// Zmien stan przekaznika 1 na wylaczony
 * 		CHSTATE=2,1\n	// Zmien stan przekaznika 2 na wlaczony
 * 		ASTATESTATUS\n	// Podaj stan wszystkich przekaznikow
 *
 */
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


