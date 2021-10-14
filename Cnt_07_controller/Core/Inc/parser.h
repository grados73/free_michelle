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
#define DATA_SIZE_FR 4

void UART_ParseLine(UARTDMA_HandleTypeDef *huartdma);
void UART_ParseLED();
void UART_ParseMotor();

typedef uint8_t preamb_t;
typedef uint8_t source_adress_t;
typedef uint8_t destination_adress_t;
typedef uint8_t message_type_t;
typedef uint16_t id_message_t;
typedef uint8_t size_data_t;
typedef uint8_t crc_header_t;
typedef uint16_t reserved_t;
typedef uint8_t crc_data_t;
typedef uint8_t end_bit_t;

union comm_frame_union
{
	uint8_t bytes[FRAME_SIZE];

	//anonimowa struktura do rozszyfrowywania ramki
	struct __attribute__((packed))
		{
		preamb_t preamb;
		source_adress_t source_adress;
		destination_adress_t destination_adress;
		message_type_t message_type;
		id_message_t id_message;
		size_data_t size_data;
		crc_header_t crc_header;
		uint8_t data[DATA_SIZE_FR];
		reserved_t reserved;
		crc_data_t crc_data;
		end_bit_t end_bit;
		};
};



typedef enum
{
	IDLE = 0, 				//0
	AUTONOMOUS  			// 9 THE VEHICLE IS SELF-DRIVING CAR
} CONTROLLER_STATE;







//typedef struct motors_struct
//{
//	MOTION_STATE	State;
//	uint8_t			LeftPWM;
//	uint8_t			RightPWM;
//	uint8_t			AIN1;
//	uint8_t			AIN2;
//	uint8_t			BIN1;
//	uint8_t			BIN2;
//	uint8_t			STBY;
//}HBridge;

void SwitchMotorRegular();

void IdleRoutine(uint8_t * MotorParameters);
void ConstGo9Routine(uint8_t * MotorParameters);
void ConstGo6Routine(uint8_t * MotorParameters);
void ConstBack13Routine(uint8_t * MotorParameters);
void Constback16Routine(uint8_t * MotorParameters);
void GoAndTurningLeftRoutine(uint8_t * MotorParameters);
void GoAndTurningRightRoutine(uint8_t * MotorParameters);
void TurningLeftRoutine(uint8_t * MotorParameters);
void TurningRightRoutine(uint8_t * MotorParameters);
void AutonomousRoutine(uint8_t * MotorParameters);
#endif /* INC_PARSER_H_ */
