/*
 * eeprom.c
 *
 *  Created on: Dec 21, 2021
 *      Author: grad_
 */

#include "eeprom.h"
#include "i2c.h"
#include "parser.h"

#define EEPROM_ADDR     0xA0
#define WRITE_TIMEOUT   6

static uint32_t last_write;

void eeprom_wait(void)
{
    while (HAL_GetTick() - last_write <= WRITE_TIMEOUT)
    {
    }
}

HAL_StatusTypeDef eeprom_read(uint32_t addr, void* data, uint32_t size)
{
    eeprom_wait();
    return HAL_I2C_Mem_Read(&hi2c3, EEPROM_ADDR, addr, 1, data, size, HAL_MAX_DELAY);
}

HAL_StatusTypeDef eeprom_write(uint32_t addr, const void* data, uint32_t size)
{
    HAL_StatusTypeDef rc;

    eeprom_wait();
    rc = HAL_I2C_Mem_Write(&hi2c3, EEPROM_ADDR, addr, 1, (void*)data, size, HAL_MAX_DELAY);
    last_write = HAL_GetTick();

    return rc;
}

void EEPROM_RelayStateUpdate(uint8_t RelayNumber, uint8_t NewState)
{
	uint8_t State = NewState;
	if(RelayNumber == 1) eeprom_write(EEPROM_ADR_RELAY_1_STATE, &State, sizeof(State));
	else if(RelayNumber == 2) eeprom_write(EEPROM_ADR_RELAY_2_STATE, &State, sizeof(State));
	else if(RelayNumber == 3) eeprom_write(EEPROM_ADR_RELAY_3_STATE, &State, sizeof(State));
	else if(RelayNumber == 4) eeprom_write(EEPROM_ADR_RELAY_4_STATE, &State, sizeof(State));
}

void EEPROM_LightStateUpdate(uint8_t LightNumber, uint8_t NewState)
{
	uint8_t State = NewState;
	if(LightNumber == 1) eeprom_write(EEPROM_ADR_LIGHT_1_STATE, &State, sizeof(State));
	else if(LightNumber == 2) eeprom_write(EEPROM_ADR_LIGHT_2_STATE, &State, sizeof(State));
	else if(LightNumber == 3) eeprom_write(EEPROM_ADR_LIGHT_3_STATE, &State, sizeof(State));
	else if(LightNumber == 4) eeprom_write(EEPROM_ADR_LIGHT_4_STATE, &State, sizeof(State));
}

uint8_t EEPROM_RelayStateRead(uint8_t RelayNumber)
{
	uint8_t RelayStan = 0;
	if(RelayNumber == 1) eeprom_read(EEPROM_ADR_RELAY_1_STATE, &RelayStan, sizeof(RelayStan));
	else if(RelayNumber == 2) eeprom_read(EEPROM_ADR_RELAY_2_STATE, &RelayStan, sizeof(RelayStan));
	else if(RelayNumber == 3) eeprom_read(EEPROM_ADR_RELAY_3_STATE, &RelayStan, sizeof(RelayStan));
	else if(RelayNumber == 4) eeprom_read(EEPROM_ADR_RELAY_4_STATE, &RelayStan, sizeof(RelayStan));

	return RelayStan;
}

uint8_t EEPROM_LightStateRead(uint8_t LightNumber)
{
	uint8_t AktualnyStan = 0;
	if(LightNumber == 1) eeprom_read(EEPROM_ADR_LIGHT_1_STATE, &AktualnyStan, sizeof(AktualnyStan));
	else if(LightNumber == 2) eeprom_read(EEPROM_ADR_LIGHT_2_STATE, &AktualnyStan, sizeof(AktualnyStan));
	else if(LightNumber == 3) eeprom_read(EEPROM_ADR_LIGHT_3_STATE, &AktualnyStan, sizeof(AktualnyStan));
	else if(LightNumber == 4) eeprom_read(EEPROM_ADR_LIGHT_4_STATE, &AktualnyStan, sizeof(AktualnyStan));

	return AktualnyStan;
}

void EEPROM_RelayStateRestore(void)
{
	if(EEPROM_RelayStateRead(1)) SendComand(UCMD_RELAY_1_ON);
	else SendComand(UCMD_RELAY_1_OFF);
	if(EEPROM_RelayStateRead(2)) SendComand(UCMD_RELAY_2_ON);
	else SendComand(UCMD_RELAY_2_OFF);
	if(EEPROM_RelayStateRead(3)) SendComand(UCMD_RELAY_3_ON);
	else SendComand(UCMD_RELAY_3_OFF);
	if(EEPROM_RelayStateRead(4)) SendComand(UCMD_RELAY_4_ON);
	else SendComand(UCMD_RELAY_4_OFF);

}

void EEPROM_LightStateRestore(void)
{
	if(EEPROM_LightStateRead(1)) SendComand(UCMD_LIGHT_1_ON);
	else SendComand(UCMD_LIGHT_1_OFF);
	if(EEPROM_LightStateRead(2)) SendComand(UCMD_LIGHT_2_ON);
	else SendComand(UCMD_LIGHT_2_OFF);
	if(EEPROM_LightStateRead(3)) SendComand(UCMD_LIGHT_3_ON);
	else SendComand(UCMD_LIGHT_3_OFF);
	if(EEPROM_LightStateRead(4)) SendComand(UCMD_LIGHT_4_ON);
	else SendComand(UCMD_LIGHT_4_OFF);
}

void EEPROM_ScheduleDayInWeekRead(uint8_t NrOfSchedule, uint8_t * scheduleDayInWeekTab)
{

}
void EEPROM_ScheduleRelayAndSwitchTabRead(uint8_t NrOfSchedule, uint8_t * scheduleRelayAndSwitchTab)
{

}

void EEPROM_ScheduleHourOnRead(uint8_t NrOfSchedule, uint8_t * hourOn)
{
	uint8_t TempHour = 0;

	if(1 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_1_HOUR_ON, &TempHour, sizeof(TempHour));
	}
	else if (2 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_2_HOUR_ON, &TempHour, sizeof(TempHour));
	}

	*hourOn = TempHour;

}
void EEPROM_ScheduleMinuteOnRead(uint8_t NrOfSchedule, uint8_t * minuteOn)
{
	uint8_t TempMinute = 0;

	if(1 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_1_MINUTE_ON, &TempMinute, sizeof(TempMinute));
	}
	else if (2 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_2_MINUTE_ON, &TempMinute, sizeof(TempMinute));
	}
	*minuteOn = TempMinute;

}
void EEPROM_ScheduleHourOffRead(uint8_t NrOfSchedule, uint8_t * hourOff)
{
	uint8_t TempHour = 0;

	if(1 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_1_HOUR_OFF, &TempHour, sizeof(TempHour));
	}
	else if (2 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_2_HOUR_OFF, &TempHour, sizeof(TempHour));
	}

	*hourOff = TempHour;

}
void EEPROM_ScheduleMinuteOffRead(uint8_t NrOfSchedule, uint8_t * minuteOff)
{
	uint8_t TempMinute = 0;

	if(1 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_1_MINUTE_OFF, &TempMinute, sizeof(TempMinute));
	}
	else if (2 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_2_MINUTE_OFF, &TempMinute, sizeof(TempMinute));
	}
	*minuteOff = TempMinute;

}
