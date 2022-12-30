#include "flash_if.h"
#include "Config.h"
#include <stdio.h>
#include <string.h>


HAL_StatusTypeDef Erase_Flash(void)
{
	uint32_t FirstSector = 0, NbOfSectors = 0;
	uint32_t SECTORError = 0;

	FLASH_EraseInitTypeDef EraseInitStruct;

	FirstSector = APPLICATION_START_SECTOR;
	NbOfSectors = TOTAL_APPLICATION_SECTOR;
	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector        = FirstSector;
	EraseInitStruct.NbSectors     = NbOfSectors;
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	{
	   ;
	}

	HAL_FLASH_Lock();
	return HAL_OK;
}


HAL_StatusTypeDef Write_To_Flash(struct flash_write_config * configuration)
{
	HAL_StatusTypeDef flashRetStatus = HAL_OK;
	uint32_t len = 0;
	uint32_t data = 0;
	if(configuration)
	{
		if(Erase_Flash() == HAL_OK)
		{
			HAL_FLASH_Unlock();
			while(len < configuration->data_length)
			{
				memcpy(&data, configuration->data, WORD_SIZE);

				len += sizeof(uint32_t);
				configuration->data = configuration->data + WORD_SIZE;
				if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, configuration->address, data) == HAL_OK)
				{
					configuration->address += WORD_SIZE;
				}
				else
				{
					printf("flash write error\r\n");
					flashRetStatus = HAL_ERROR;
				}
			}
		}
		else
		{
			flashRetStatus = HAL_ERROR;
		}
	}
	else
	{
		flashRetStatus = HAL_ERROR;
	}

	HAL_FLASH_Lock();
	return flashRetStatus;
}
