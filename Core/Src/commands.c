#include "commands.h"
#include "fatfs.h"
#include "log.h"
#include "main.h"
#include "bootloader.h"
#include "Config.h"

extern char USBH_Path[4];
static uint8_t RAM_Buf[BUFFER_SIZE] =
{
		0x00
};

static char rwtext[100];

unsigned char COMMAND_Test_Write(void);
unsigned char COMMAND_Test_Read(void);

extern unsigned short overflow;
static unsigned char detetcted_flag;
FATFS myUsbFatFS;
FIL myFile;
FIL fileR;
FRESULT res;
UINT byteswritten, bytesread;
extern FATFS fatfs;
extern FIL file;
extern FIL fileR;
extern DIR dir;
extern FILINFO fno;

/**
  * @brief  Timer to check for USB detection
  * @param  None
  * @retval 1 if timer expires
  * 		0 if timer not expired
  */
unsigned char no_usb_detected(void)
{
	if((overflow >= USB_WAIT_PERIOD) && (detetcted_flag == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief  Mounts Fat filsystem on USB
  * @param  None
  * @retval 0 success
  * 		1 fail
  */
char COMMAND_PREPARE_USB(void)
{
	if(f_mount(&myUsbFatFS, (TCHAR const*)USBH_Path, 0) == FR_OK)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/**
  * @brief  Downloads the user application from USB to internal flash
  * @param  None
  * @retval None
  */
void COMMAND_DOWNLOAD(void)
{
	FILINFO file_info;
	if (f_open(&fileR, DOWNLOAD_FILENAME, FA_READ) == FR_OK)
	{
		detetcted_flag = 1;
		memset(&file_info, 0 , sizeof(file_info));
		if(f_stat(DOWNLOAD_FILENAME, &file_info) == FR_OK)
		{
			if (file_info.fsize > (FLASH_END_ADDRESS - APPLICATION_START_ADDRESS))
			{
				;
			}
			else
			{
				Erase_Flash();
				COMMAND_ProgramFlashMemory();
				printf("Flashing completed..\r\nPlease remove the USB stick\r\n");
				BootAppImage();
				f_close (&fileR);
				HAL_Delay(1000);
				f_mount(NULL, (TCHAR const*)USBH_Path, 0);
			}
		}
		else
		{
			;
		}
	}

	return;

}

/**
  * @brief  Jumps to app
  * @param  None
  * @retval None
  */
void COMMAND_JUMP(void)
{
  /* Software reset */
  NVIC_SystemReset();
}

/**
  * @brief  Programs the internal Flash memory
  * @param  None
  * @retval None
  */
void COMMAND_ProgramFlashMemory(void)
{
	uint16_t BytesRead;

	struct flash_write_config wconfig;
    f_read (&fileR, RAM_Buf, BUFFER_SIZE, (void *)&BytesRead);
    if (BytesRead < BUFFER_SIZE)
    {
    		BOOT_LOG("TRANSFERING APPLICATION IMAGE\r\n");
			memset(&wconfig, 0, sizeof(wconfig));
			wconfig.address = APPLICATION_START_ADDRESS;
			wconfig.data = RAM_Buf;
			wconfig.data_length = BytesRead;
			Write_To_Flash(&wconfig);
    }
}
