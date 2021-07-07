/*
 * parser.h
 *
 *  Created on: Jul 7, 2021
 *      Author: grad_
 */

#ifndef INC_PARSER_H_
#define INC_PARSER_H_

typedef enum
{
	IDLE = 0, 				//0
	INITIALIZATION,			//initializacja systemu, stan po restarcie lub włączeniu
	PARAMETERS,				//wyswietla aktualne parametry wody i powietrza
	SW_CONTROLING,			//ekran z ręcznym włączaniem i wyłączaniem przerzutników
	LIGHT_CONTROLLING, 		//ekran z ręcznym sterowaniem światłami
	LIGHT_TIMERS,			//ustawianie czasu włłączania i wyłączania świateł
	CONNECTION_ERROR		//błąd połączenia UART z drugim uC

} CONTROLLER_STATE;

#endif /* INC_PARSER_H_ */
