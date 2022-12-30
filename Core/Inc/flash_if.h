/* ------------------------------------------------------------ *
 * 																*
 * file:        flash_if.h	                                    *
 * purpose:     Provides high level flash interface to user		*
 * 				applications								    *
 * author:      Sachin Rajput, Harsh Dave                       *
 *                                                              *
 * ------------------------------------------------------------ */
#ifndef INC_FLASH_IF_H_
#define INC_FLASH_IF_H_
#include "stm32f7xx_hal.h"


struct flash_write_config{
	uint32_t address;
	uint8_t *data;
	uint32_t data_length;
};

HAL_StatusTypeDef Write_To_Flash(struct flash_write_config * configuration);
HAL_StatusTypeDef Erase_Flash(void);
void SetupBootAddress(int addr);
int ImageThereorNot(void);

#endif /* INC_FLASH_IF_H_ */
