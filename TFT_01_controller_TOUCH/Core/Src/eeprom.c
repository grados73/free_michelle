/*
 * eeprom.c
 *
 *  Created on: Dec 21, 2021
 *      Author: grad_
 */

#include "eeprom.h"
#include "i2c.h"

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

