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


void SwitchMotorRegular();

void PodajStatusRoutine();
void PodajTemperatureRoutine(uint8_t NrCzujnika);
void PodajCisnienieRoutine(uint8_t NrCzujnika);
void ZmienStanPrzekRoutine(uint8_t NrPrzekaznika, uint8_t Stan);

#endif /* INC_PARSER_H_ */
