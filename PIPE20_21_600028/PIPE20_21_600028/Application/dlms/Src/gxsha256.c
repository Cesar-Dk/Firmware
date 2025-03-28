xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         break;
 797:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** 
 798:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****       case HAL_I2C_MSPDEINIT_CB_ID :
 799:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         hi2c->MspDeInitCallback = pCallback;
 800:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         break;
 801:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** 
 802:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****       default :
 803:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         /* Update the error code */
 804:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;
 805:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** 
 806:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         /* Return error status */
 807:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         status =  HAL_ERROR;
 808:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         break;
 809:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****     }
 810:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   }
 811:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   else if (HAL_I2C_STATE_RESET == hi2c->State)
 812:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   {
 813:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****     switch (CallbackID)
 814:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****     {
 815:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****       case HAL_I2C_MSPINIT_CB_ID :
 816:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         hi2c->MspInitCallback = pCallback;
 817:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         break;
 818:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** 
 819:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****       case HAL_I2C_MSPDEINIT_CB_ID :
 820:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         hi2c->MspDeInitCallback = pCallback;
 821:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         break;
 822:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** 
 823:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****       default :
 824:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         /* Update the error code */
 825:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;
 826:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** 
 827:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         /* Return error status */
 828:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         status =  HAL_ERROR;
ARM GAS  C:\Users\DANIEL~1\AppData\Local\Temp\ccBxXN5X.s 			page 16


 829:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****         break;
 830:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****     }
 831:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   }
 832:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   else
 833:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   {
 834:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****     /* Update the error code */
 835:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****     hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;
 836:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** 
 837:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****     /* Return error status */
 838:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****     status =  HAL_ERROR;
 839:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   }
 840:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** 
 841:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   return status;
 842:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** }
 843:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** 
 844:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c **** /**
 845:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   * @brief  Unregister an I2C Callback
 846:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *         I2C callback is redirected to the weak predefined callback
 847:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   * @note   The HAL_I2C_UnRegisterCallback() may be called before HAL_I2C_Init() in HAL_I2C_STATE_R
 848:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *         to un-register callbacks for HAL_I2C_MSPINIT_CB_ID and HAL_I2C_MSPDEINIT_CB_ID.
 849:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
 850:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *                the configuration information for the specified I2C.
 851:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   * @param  CallbackID ID of the callback to be unregistered
 852:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *         This parameter can be one of the following values:
 853:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *         This parameter can be one of the following values:
 854:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *          @arg @ref HAL_I2C_MASTER_TX_COMPLETE_CB_ID Master Tx Transfer completed callback ID
 855:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *          @arg @ref HAL_I2C_MASTER_RX_COMPLETE_CB_ID Master Rx Transfer completed callback ID
 856:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *          @arg @ref HAL_I2C_SLAVE_TX_COMPLETE_CB_ID Slave Tx Transfer completed callback ID
 857:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *          @arg @ref HAL_I2C_SLAVE_RX_COMPLETE_CB_ID Slave Rx Transfer completed callback ID
 858:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *          @arg @ref HAL_I2C_LISTEN_COMPLETE_CB_ID Listen Complete callback ID
 859:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c ****   *          @arg @ref HAL_I2C_MEM_TX_COMPLETE_CB_ID Memory Tx Transfer callbac