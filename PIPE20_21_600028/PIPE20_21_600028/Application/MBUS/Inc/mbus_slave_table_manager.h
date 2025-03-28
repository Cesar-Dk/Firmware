3xx_hal_uart.c ****   * @retval HAL status
1162:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****   */
1163:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c **** HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32
1164:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c **** {
1165:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****   uint8_t  *pdata8bits;
1166:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****   uint16_t *pdata16bits;
1167:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****   uint16_t uhMask;
1168:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****   uint32_t tickstart;
1169:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c **** 
1170:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****   /* Check that a Rx process is not already ongoing */
ARM GAS  C:\Users\DANIEL~1\AppData\Local\Temp\cc0KSo6Z.s 			page 22


1171:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****   if (huart->RxState == HAL_UART_STATE_READY)
1172:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****   {
1173:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****     if ((pData == NULL) || (Size == 0U))
1174:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****     {
1175:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****       return  HAL_ERROR;
1176:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c ****     }
1177:Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c **** 
1178:Drivers/STM32F3xx_HAL_Driver/Src/