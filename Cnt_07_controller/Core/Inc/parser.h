/*
 * parser.h
 *
 *  Created on: Jan 25, 2021
 *      Author: grad_
 */


#ifndef INC_PARSER_H_
#define INC_PARSER_H_
#include "uartdma.h"

#define BUFFOR_SIZE 65
#define FRAME_SIZE 16
#define SOURCE_STATE_LENGTH 10

#define DATA_SIZE_FR 4

#define MY_ADRESS 2 //Adres danego urządzenia

void UART_ParseLine(UARTDMA_HandleTypeDef *huartdma);
void UART_ParseLED();
void UART_ParseStatus();
void UART_ParseTemp();
void UART_ParsePres();
void UART_ParseChangeRelayState();


void SwitchMotorRegular();

void PodajStatusRoutine();
void PodajTemperatureRoutine(uint8_t NrCzujnika);
void PodajCisnienieRoutine(uint8_t NrCzujnika);
void ZmienStanPrzekRoutine(uint8_t NrPrzekaznika, uint8_t Stan);



#endif /* INC_PARSER_H_ */
