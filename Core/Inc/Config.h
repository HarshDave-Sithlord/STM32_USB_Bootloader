/* ------------------------------------------------------------ *
 * 																*
 * file:        Config.h	                                    *
 * purpose:     Provides high level system configuration	    *
 * author:      Sachin Rajput, Harsh Dave                       *
 *                                                              *
 * ------------------------------------------------------------ */
#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#define USB_WAIT_PERIOD 10000U      //10 seconds as per systick timer
#define DOWNLOAD_FILENAME          "0:image.bin"

/**
 * Advisable not to change following addresses.
 * It well calculates based on bootloader's memory footprint.
 * User application gets to use 3 sectors each of size 128KB starting from address 0x08020000U
 */

#define FLASH_END_ADDRESS			0x0807FFFFU
#define APPLICATION_START_ADDRESS	0x08020000U
#define WORD_SIZE					0x04U
#define APPLICATION_START_SECTOR	0x05U
#define TOTAL_APPLICATION_SECTOR	0x03U  //Each sector of 128KB

#endif /* INC_CONFIG_H_ */
