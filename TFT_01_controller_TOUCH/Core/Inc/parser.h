/*
 * parser.h
 *
 *  Created on: Jul 7, 2021
 *      Author: grad_
 */

#ifndef INC_PARSER_H_
#define INC_PARSER_H_

#define NUMBER_OF_RELAY 4

typedef enum
{
	IDLE = 0, 				//0
	INITIALIZATION,			//initializacja systemu, stan po restarcie lub włączeniu
	PARAMETERS,				//wyswietla aktualne parametry wody i powietrza
	SW_CONTROLLING,			//ekran z ręcznym włączaniem i wyłączaniem przerzutników
	LIGHT_CONTROLLING, 		//ekran z ręcznym sterowaniem światłami
	LIGHT_TIMERS,			//ustawianie czasu włłączania i wyłączania świateł
	CONNECTION_ERROR		//błąd połączenia UART z drugim uC

} CONTROLLER_STATE;

typedef struct
{
	char status[24];
	float temperatura1;
	float cisnienie1;
	uint8_t przekazniki[NUMBER_OF_RELAY];

} second_uc_data;





//////////////////////////////////////// ERRORS //////////////////////////////////////////////////////////////////////////////////////////////////////
#define LED_FORMAT_ERROR "LED=ERR_FORMAT\n"
#define TEMPERATURE_FORMAT_ERROR "ATEMP=ERR_FORMAT\n"
#define PRESURE_FORMAT_ERROR "APRES=ERR_FORMAT\n"
#define CHANGE_RELAY_STATE_FORMAT_ERROR "ACHSTATE=ERR_FORMAT\n"
#define CHANGE_RELAY_STATE_NUMBER_ERROR "ACHSTATE=ERR_NUMBER\n"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void SwitchControllerState();
void IdleRoutine(uint8_t * AqaParameters);
void InitializationRoutine(uint8_t * AqaParameters);
void ParametersRoutine(uint8_t * AqaParameters);
void SwitchControlingRoutine(uint8_t * AqaParameters);
void LightControllingRoutine(uint8_t * AqaParameters);
void LightTimersRoutine(uint8_t * AqaParameters);
void ConnectionErrorRoutine(uint8_t * AqaParameters);

#include "uartdma.h"
#include "TFT_ILI9341.h"
#include "GFX_Color.h"
#include "GFX_EnhancedFonts.h"
#include "EnhancedFonts/arialBlack_20ptFontInfo.h"
#include "EnhancedFonts/ArialBlack_28pts_bold.h"
#include "string.h"
#include "stdio.h"
#include "functions.h"

#define BUFFOR_SIZE 65
#define FRAME_SIZE 16
#define SOURCE_STATE_LENGTH 10

#define DATA_SIZE_FR 4

#define MY_ADRESS 2 //Adres danego urządzenia

void UART_ParseLine(UARTDMA_HandleTypeDef *huartdma);
void UART_ParseLED();
void UART_ParseAnswStatus();
void UART_ParseAnswTemp();
void UART_ParseAnswPres();
void UART_ParseAnswChangeRelayState();
void UART_ParseAnswRelayStateStatus();
void UART_ParseAnswLightsStateStatus();


void SwitchMotorRegular();

void PodajStatusRoutine();
void PodajTemperatureRoutine(uint8_t NrCzujnika);
void PodajCisnienieRoutine(uint8_t NrCzujnika);
void ZmienStanPrzekRoutine(uint8_t NrPrzekaznika, uint8_t Stan);

/*
 * SENDING COMAND ID NUMBER
 *	0 	=>	LED=1\n 			// LED On
 * 	1	=>	LED=0\n 			// LED Off
 * 	2	=>	STATE=?\n			// Jaki jest stan uC
 * 	3	=>	TEMP=1\n			// Jaka jest temperatura 1 czujnika
 * 	4	=>	PRES=1\n			// Jakie jest cisnienie 1 czujnika
 * 	5	=>	CHSTATE=1,0\n		// Zmien stan przekaznika 1 na wylaczony
 * 	6	=>	CHSTATE=2,1\n		// Zmien stan przekaznika 2 na wlaczony
 * 	21	=>	STATESTATUS=?\n		// Podaj stan wszystkich przekaznikow
 * 	13  =>	CHLIGHT=1,0\n		// Zmien stan swiatla 1 na wylaczony
 * 	15  =>  CHLIGHT=2,1\n		// Zmien stan swiatla 2 na wlaczony
 * 	22	=>	LIGHTSSTATUS=?\n	// Podaj stan wszytskich swiatel
 *
 */

#define UCMD_LED_ON 0
#define UCMD_LED_OFF 1
#define UCMD_STATE_ASK 2
#define UCMD_TEMP_1 3
#define UCMD_PRES_1 4
//***********************//
#define UCMD_RELAY_1_ON 5
#define UCMD_RELAY_1_OFF 6
#define UCMD_RELAY_2_ON 7
#define UCMD_RELAY_2_OFF 8
#define UCMD_RELAY_3_ON 9
#define UCMD_RELAY_3_OFF 10
#define UCMD_RELAY_4_ON 11
#define UCMD_RELAY_4_OFF 12
#define UCMD_RELAY_SCHOW_ALL 21
//***********************//
#define UCMD_LIGHT_1_ON 13
#define UCMD_LIGHT_1_OFF 14
#define UCMD_LIGHT_2_ON 15
#define UCMD_LIGHT_2_OFF 16
#define UCMD_LIGHT_3_ON 17
#define UCMD_LIGHT_3_OFF 18
#define UCMD_LIGHT_4_ON 19
#define UCMD_LIGHT_4_OFF 20
#define UCMD_LIGHT_SCHOW_ALL 22


uint8_t SendComand(uint8_t Command);

#endif /* INC_PARSER_H_ */
