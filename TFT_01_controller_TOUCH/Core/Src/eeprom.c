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

//
// Basic function to work with I2C EEPROM
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to Read, Update and Restore from EEPROM memory last state of Relay and Lights after lack of energy
//
// Function to update in EEPROM current state of all Relay
void EEPROM_RelayStateUpdate(uint8_t RelayNumber, uint8_t NewState)
{
	uint8_t State = NewState;
	if(RelayNumber == 1) eeprom_write(EEPROM_ADR_RELAY_1_STATE, &State, sizeof(State));
	else if(RelayNumber == 2) eeprom_write(EEPROM_ADR_RELAY_2_STATE, &State, sizeof(State));
	else if(RelayNumber == 3) eeprom_write(EEPROM_ADR_RELAY_3_STATE, &State, sizeof(State));
	else if(RelayNumber == 4) eeprom_write(EEPROM_ADR_RELAY_4_STATE, &State, sizeof(State));
}

//
// Function to update in EEPROM current state of all Lights
void EEPROM_LightStateUpdate(uint8_t LightNumber, uint8_t NewState)
{
	uint8_t State = NewState;
	if(LightNumber == 1) eeprom_write(EEPROM_ADR_LIGHT_1_STATE, &State, sizeof(State));
	else if(LightNumber == 2) eeprom_write(EEPROM_ADR_LIGHT_2_STATE, &State, sizeof(State));
	else if(LightNumber == 3) eeprom_write(EEPROM_ADR_LIGHT_3_STATE, &State, sizeof(State));
	else if(LightNumber == 4) eeprom_write(EEPROM_ADR_LIGHT_4_STATE, &State, sizeof(State));
}

//
// Function to read in EEPROM current state of all Relay
uint8_t EEPROM_RelayStateRead(uint8_t RelayNumber)
{
	uint8_t RelayStan = 0;
	if(RelayNumber == 1) eeprom_read(EEPROM_ADR_RELAY_1_STATE, &RelayStan, sizeof(RelayStan));
	else if(RelayNumber == 2) eeprom_read(EEPROM_ADR_RELAY_2_STATE, &RelayStan, sizeof(RelayStan));
	else if(RelayNumber == 3) eeprom_read(EEPROM_ADR_RELAY_3_STATE, &RelayStan, sizeof(RelayStan));
	else if(RelayNumber == 4) eeprom_read(EEPROM_ADR_RELAY_4_STATE, &RelayStan, sizeof(RelayStan));

	return RelayStan;
}

//
// Function to read in EEPROM current state of all Lights
uint8_t EEPROM_LightStateRead(uint8_t LightNumber)
{
	uint8_t AktualnyStan = 0;
	if(LightNumber == 1) eeprom_read(EEPROM_ADR_LIGHT_1_STATE, &AktualnyStan, sizeof(AktualnyStan));
	else if(LightNumber == 2) eeprom_read(EEPROM_ADR_LIGHT_2_STATE, &AktualnyStan, sizeof(AktualnyStan));
	else if(LightNumber == 3) eeprom_read(EEPROM_ADR_LIGHT_3_STATE, &AktualnyStan, sizeof(AktualnyStan));
	else if(LightNumber == 4) eeprom_read(EEPROM_ADR_LIGHT_4_STATE, &AktualnyStan, sizeof(AktualnyStan));

	return AktualnyStan;
}

//
// Function to restore from EEPROM memory last state of all Relay
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

//
// Function to restore from EEPROM memory last state of all Lights
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to Read, Update and Restore from EEPROM memory day of week which schedule apply
//
// Function to read saved day which apply this schedule
void EEPROM_ScheduleDayInWeekRead(uint8_t NrOfSchedule, uint8_t * scheduleDayInWeekTab)
{
	uint8_t TempDayInWeek = 0;

	if(1 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_1_DAYS, &TempDayInWeek, sizeof(TempDayInWeek));
	}
	else if(2 == NrOfSchedule)
	{
		eeprom_read(EEPROM_ADR_SHEDULE_2_DAYS, &TempDayInWeek, sizeof(TempDayInWeek));
	}

	//PON-1
	if(TempDayInWeek & 0x01)  scheduleDayInWeekTab[0] = 1;
	else  scheduleDayInWeekTab[0] = 0;
	//WT-2
	if(TempDayInWeek & 0x02)  scheduleDayInWeekTab[1] = 1;
	else  scheduleDayInWeekTab[1] = 0;
	//SR-3
	if(TempDayInWeek & 0x04)  scheduleDayInWeekTab[2] = 1;
	else  scheduleDayInWeekTab[2] = 0;
	//CZW-4
	if(TempDayInWeek & 0x08)  scheduleDayInWeekTab[3] = 1;
	else scheduleDayInWeekTab[3] = 0;
	//PT-5
	if(TempDayInWeek & 0x10)  scheduleDayInWeekTab[4] = 1;
	else  scheduleDayInWeekTab[4] = 0;
	//SB-6
	if(TempDayInWeek & 0x20)  scheduleDayInWeekTab[5] = 1;
	else  scheduleDayInWeekTab[5] = 0;
	//ND-7
	if(TempDayInWeek & 0x40)  scheduleDayInWeekTab[6] = 1;
	else  scheduleDayInWeekTab[6] = 0;
}

//
// Function to update from EEPROM saved day which apply this schedule
void EEPROM_ScheduleDayInWeekUpdate(uint8_t NrOfSchedule, uint8_t * scheduleDayInWeekTab)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to Read, Update and Restore from EEPROM memory Relays and Lights which schedule apply
//
// Function to read saved day which apply this schedule
void EEPROM_ScheduleRelayAndSwitchTabRead(uint8_t NrOfSchedule, uint8_t * scheduleRelayAndSwitchTab)
{

}
//
// Function to update saved day which apply this schedule
void EEPROM_ScheduleRelayAndSwitchTabUpdate(uint8_t NrOfSchedule, uint8_t * scheduleRelayAndSwitchTab)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function to Read and Update from EEPROM memory Hours and Minutes ON / OFF which schedule apply
//
// ON READ
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

//
// OFF READ
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

//
// ON UPDATE
void EEPROM_ScheduleHourOnUpdate(uint8_t NrOfSchedule, uint8_t hourOn)
{
	uint8_t NewHour = hourOn;
	if(1 == NrOfSchedule) eeprom_write(EEPROM_ADR_SHEDULE_1_HOUR_ON, &NewHour, sizeof(NewHour));
	else if(2 == NrOfSchedule) eeprom_write(EEPROM_ADR_SHEDULE_2_HOUR_ON, &NewHour, sizeof(NewHour));
}
void EEPROM_ScheduleMinuteOnUpdate(uint8_t NrOfSchedule, uint8_t minuteOn)
{
	uint8_t NewMinute = minuteOn;
	if(1 == NrOfSchedule) eeprom_write(EEPROM_ADR_SHEDULE_1_MINUTE_ON, &NewMinute, sizeof(NewMinute));
	else if(2 == NrOfSchedule) eeprom_write(EEPROM_ADR_SHEDULE_2_MINUTE_ON, &NewMinute, sizeof(NewMinute));
}

//
// OFF UPDATE
void EEPROM_ScheduleHourOffUpdate(uint8_t NrOfSchedule, uint8_t hourOff)
{
	uint8_t NewHour = hourOff;
	if(1 == NrOfSchedule) eeprom_write(EEPROM_ADR_SHEDULE_1_HOUR_OFF, &NewHour, sizeof(NewHour));
	else if(2 == NrOfSchedule) eeprom_write(EEPROM_ADR_SHEDULE_2_HOUR_OFF, &NewHour, sizeof(NewHour));

}
void EEPROM_ScheduleMinuteOffUpdate(uint8_t NrOfSchedule, uint8_t minuteOff)
{
	uint8_t NewMinute = minuteOff;
	if(1 == NrOfSchedule) eeprom_write(EEPROM_ADR_SHEDULE_1_MINUTE_OFF, &NewMinute, sizeof(NewMinute));
	else if(2 == NrOfSchedule) eeprom_write(EEPROM_ADR_SHEDULE_2_MINUTE_OFF, &NewMinute, sizeof(NewMinute));

}
