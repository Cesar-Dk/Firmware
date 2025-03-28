/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "icache.h"
#include "iwdg.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "params.h"
#include "crc32.h"
#include "lz.h"
#include "spi_flash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef void (*pFunction)( void );
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
static uint8_t EraseFlash( void );
unsigned char  Validate( void );
static uint8_t FillFlash( void );
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern struct params param2;
extern char _main_app_start_address[], _logger_start_address[], _main_app_size[], _logger_size[];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int updater_main(void)
{
	/* USER CODE BEGIN 1 */
	pFunction jump_to_app = NULL;
	uint32_t jump_addr    = 0;

	__disable_irq();

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* Configure the System Power */
	SystemPower_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ICACHE_Init();
	MX_IWDG_Init();
	MX_SPI2_Init();
	/* USER CODE BEGIN 2 */
	MX_IWDG_Init();
	sFLASH_Init();
	sFLASH_initSST26V();
	crc32_init_table();
	params_init();

	HAL_IWDG_Refresh(&hiwdg);

	if ( param2.version.size && (param2.version.size != 0xFFFFFFFF)) {
		if ( Validate() ) {
			// TODO simular descompresi�n para comprobar q no superamos el valor max de PROG MEM
			// ANTES del borrado
			while (1) {
				if (EraseFlash()) {
					if (FillFlash()) {
						// TODO check CRC
						// Aunque por ahora no tengo CRC del firmware descomprimido
						// Y si hay fallo en la escritura flash, FillFlash devuelve 0
						param2.version.major = param2.version.to_major;
						param2.version.minor = param2.version.to_minor;
						param2.version.size = 0;
						param2.version.crc = 0;
						param2.version.to_major = 0;
						param2.version.to_minor = 0;
						params_check_for_changes();
						break;
					}
				}
			}
		}
	}

	HAL_IWDG_Refresh(&hiwdg);

	if ((*(__IO uint32_t *) _main_app_start_address) == 0x200C0000)
	{
		jump_addr   = (uint32_t) *((__IO uint32_t*) _main_app_start_address);
		jump_to_app = (pFunction) *(__IO uint32_t*) ((uint32_t) _main_app_start_address + 4);
		SCB->VTOR   = 0x08008000;
		__set_MSP(jump_addr);
		jump_to_app();
	}
	else
	{
		NVIC_SystemReset();
	}
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Power Configuration
  * @retval None
  */
static void SystemPower_Config(void)
{

  /*
   * Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
   */
  HAL_PWREx_DisableUCPDDeadBattery();
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t Addr)
{
  uint32_t page = 0;

  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
  }

  return page;
}

/**
  * @brief  Gets the bank of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The bank of a given address
  */
static uint32_t GetBank(uint32_t Addr)
{
	uint32_t bank = 0;
	if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
	{
		/* Bank 1 */
		bank = FLASH_BANK_1;
	}
	else
	{
		/* Bank 2 */
		bank = FLASH_BANK_2;
	}
	return bank;
}

static uint8_t EraseFlash()
{
    uint32_t pages_n, page_i, flash_page;
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PAGEError = 0;

    pages_n = (uint32_t) _main_app_size / FLASH_PAGE_SIZE;

	/* Unlock the Flash to enable the flash control register access *************/
	HAL_FLASH_Unlock();
	/* Clear OPTVERR bit set on virgin samples */
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_SR_ERRORS);

    /* Get the 1st page to erase */
    flash_page = GetPage((uint32_t) _main_app_start_address + FLASH_PAGE_SIZE);
    /* Fill EraseInit structure*/
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.Banks     = GetBank((uint32_t) _main_app_start_address + FLASH_PAGE_SIZE);//FLASH_BANK_1;
    EraseInitStruct.Page      = flash_page;
    EraseInitStruct.NbPages   = 1;
    HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);

    for( page_i = 0; page_i < pages_n; page_i++ ) {
        flash_page                = GetPage((uint32_t) _main_app_start_address + FLASH_PAGE_SIZE * page_i);
    	/* Fill EraseInit structure*/
        EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
        EraseInitStruct.Banks     = GetBank((uint32_t) _main_app_start_address + FLASH_PAGE_SIZE * page_i);//FLASH_BANK_1;
        EraseInitStruct.Page      = flash_page;

        if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK) {
    		HAL_FLASH_Lock();
    		return 0;
    	}
    }

    HAL_FLASH_Lock();
	return 1;
}

unsigned char Validate( void )
{
	uint32_t i, addr, crc;
	char     page[sFLASH_SPI_PAGESIZE];

	i = param2.version.size;
	addr = sFLASH_SPI_SECTOR_SIZE*2;
	crc = 0x00000000;

	while( i > sizeof(page) )
	{
		sFLASH_ReadBuffer( (unsigned char *) page, addr, sFLASH_SPI_PAGESIZE );
		crc = crc32( page, sizeof(page), ~crc );

		addr += sFLASH_SPI_PAGESIZE;
		i    -= sizeof(page);
	}
	if( i )
	{
		sFLASH_ReadBuffer( (unsigned char *) page, addr, i );
		crc = crc32( page, i, ~crc );
	}

	if ( crc == param2.version.crc )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static uint8_t FillFlash( void )
{
	uint32_t src, dst, len, i, k, addr_MAX;
	uint16_t input_block_size;
    uint8_t input_data[8225], output_data[8192];
    static uint32_t counter = 0;

	/* Unlock the Flash to enable the flash control register access *************/
	HAL_FLASH_Unlock();
	/* Clear OPTVERR bit set on virgin samples */
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_SR_ERRORS);

//    src = (uint32_t) _logger_start_address;
	src      = sFLASH_SPI_SECTOR_SIZE * 2;
	addr_MAX = src + param2.version.size;
    dst = (uint32_t) _main_app_start_address;

//    while( src < (uint32_t) _logger_start_address + param2.version.size )
    while ( src < addr_MAX )
    {
    	HAL_IWDG_Refresh(&hiwdg);
    	// leo tama�o bloque
//        memcpy( (void *) &input_block_size, (uint32_t *) src, sizeof( input_block_size ));
    	sFLASH_ReadBuffer( (unsigned char *) &input_block_size, src, sizeof(input_block_size) );
        src += sizeof(input_block_size);
        // leo bloque
//        memcpy( (void *) input_data, (uint32_t *) src, input_block_size );
        sFLASH_ReadBuffer( input_data, src, input_block_size );
        src += input_block_size;
        // descomprimo bloque
        memset( (void *) output_data, '\0', sizeof( output_data ));
        len = LZ_Uncompress( input_data, output_data, input_block_size );
//    	uint64_t *data = (uint64_t *) &output_data;
//    	uint64_t tosave;
        uint8_t *data = (uint8_t *) &output_data;
    	FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);
        for( i = 0, k = 0; i < len; i+=16, k++ )
        {
//        	memcpy( &data, &output_data[ i ], sizeof( data ) );
//        	tosave = data[k];
			if ( HAL_FLASH_Program( FLASH_TYPEPROGRAM_QUADWORD, dst,  (uint32_t)(data + i) ) != HAL_OK ) {
				HAL_FLASH_Lock();
        		return 0;
			}
        	dst += 16;
        }
        counter++;
    }

    HAL_FLASH_Lock();
    return 1;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
