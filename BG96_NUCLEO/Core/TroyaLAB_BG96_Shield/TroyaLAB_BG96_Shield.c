/***************************
 * TroyaLAB_BG96_Shield.c  *
 *                         *
 *                         *
 * Date   : 01/11/2023     *
 * Author : Fatih Furkan   *
 *                         *
 *                         *
 ***************************/


/*************************************  INCLUDE  *************************************/

#include "TroyaLAB_BG96_Shield.h"


/*************************************  DEFINITON  *************************************/

TRYLAB  TRYLAB_st;



/*************************************  FUNCTIONS  *************************************/


/*
# Date   : 01/11/2023
# Author : Fatih Furkan
# INIT
*/
void troyalab_Stm_Shield_BG96_init(UART_HandleTypeDef *uart_module_t)
{
  TRYLAB_st.BG96_uart_st.uart_handle = uart_module_t               ;
  TRYLAB_st.timeout_st.TRY_LAB_MAX_DELAY_ms_u32     = 300          ; //default
  TRYLAB_st.timeout_st.MAX_ATTEMPT                  = 3            ; //default
  TRYLAB_st.data_transfer_st.transfer_starting_u8   = TRYLAB_FALSE ; //default
  TRYLAB_st.data_transfer_st.transfer_continues_u8  = 0            ; //default


  TRYLAB_st.timeout_st.tick_freq_hz_u32 = 0;
  TRYLAB_st.timeout_st.time_past_ms_u32 = 0;

  HAL_Delay(100);
}


/*
# Date   : 01/11/2023
# Author : Fatih Furkan
# Set Delay
*/
void set_MAX_DELAY_TIME( uint32_t MAX_DELAY)
{
  TRYLAB_st.timeout_st.TRY_LAB_MAX_DELAY_ms_u32 = MAX_DELAY;
}


/*
# Date   : 01/11/2023
# Author : Fatih Furkan
#
*/
void set_MAX_ATTEMPT( uint32_t MAX_ATTEMPT)
{
  TRYLAB_st.timeout_st.MAX_ATTEMPT = MAX_ATTEMPT;
}


/*
# Date   : 01/11/2023
# Author : Fatih Furkan
# send data
*/
void sendATCommOnce(char *user_data_u8)
{
  HAL_UART_Transmit(TRYLAB_st.BG96_uart_st.uart_handle, (uint8_t*)user_data_u8, strlen(user_data_u8), 10); // Sending in normal mode
}


/*
# Date   : 01/11/2023
# Author : Fatih Furkan
# sendATComm
*/
uint32_t sendATComm(char *user_data_u8, char *response_data_u8)
{
  TRYLAB_st.data_transfer_st.transfer_starting_u8 = TRYLAB_TRUE;
  sendATCommOnce(user_data_u8);
  HAL_UART_Receive_IT (TRYLAB_st.BG96_uart_st.uart_handle, &TRYLAB_st.data_transfer_st.alinan_data_u8, 1);
  TRYLAB_st.timeout_st.time_past_ms_u32  = HAL_GetTick();


  while(1)
  {
    if( HAL_GetTick() - TRYLAB_st.timeout_st.time_past_ms_u32 > TRYLAB_st.timeout_st.TRY_LAB_MAX_DELAY_ms_u32 )
    {
      sendATCommOnce(user_data_u8);
      TRYLAB_st.timeout_st.time_past_ms_u32 = HAL_GetTick();

      TRYLAB_st.timeout_st.attemp_time_u8 += 1;
      if(TRYLAB_st.timeout_st.attemp_time_u8 > TRYLAB_st.timeout_st.MAX_ATTEMPT)
      {
        TRYLAB_st.data_transfer_st.transfer_starting_u8 = TRYLAB_FALSE;
        TRYLAB_st.data_transfer_st.transfer_continues_u8 = 0;
        TRYLAB_st.data_transfer_st.buffer_size_u16 = 0;

        return TRYLAB_TIMEOUT;
      }
    }

    if(TRYLAB_st.data_transfer_st.transfer_continues_u8 > 0)
    {
      char *result = strstr(TRYLAB_st.data_transfer_st.alinan_data_buffer_a8, response_data_u8);

      if (result != NULL)
      {
        char  temp[BUFFER_SIZE] = {0};
        strcpy(temp, TRYLAB_st.data_transfer_st.alinan_data_buffer_a8);

        uint8_t sifirla = 0;
        for( sifirla = 0 ; sifirla < 250; sifirla++)
        {
          TRYLAB_st.data_transfer_st.alinan_data_buffer_a8[sifirla] = 0;
        }

        TRYLAB_st.data_transfer_st.transfer_starting_u8 = TRYLAB_FALSE;
        TRYLAB_st.data_transfer_st.transfer_continues_u8 = 0;
        TRYLAB_st.data_transfer_st.buffer_size_u16 = 0;

        TRYLAB_st.data_transfer_st.sayac_u8++; //for test
        return TRYLAB_OK;
      }
    }
  }
}


/*
# Date   : 01/11/2023
# Author : Fatih Furkan
#
*/
void Int_Func_for_sendATComm(UART_HandleTypeDef *huart)
{

  if (huart == TRYLAB_st.BG96_uart_st.uart_handle)
  {
    if(TRYLAB_st.data_transfer_st.transfer_starting_u8)
    {
      TRYLAB_st.data_transfer_st.transfer_continues_u8++;

      if (TRYLAB_st.data_transfer_st.buffer_size_u16 < BUFFER_SIZE - 1)
      {
        TRYLAB_st.data_transfer_st.alinan_data_buffer_a8[TRYLAB_st.data_transfer_st.buffer_size_u16++] = (char)TRYLAB_st.data_transfer_st.alinan_data_u8; // receivedData, UART verisi
        HAL_UART_Receive_IT (huart, &TRYLAB_st.data_transfer_st.alinan_data_u8, 1); //receive data from data buffer interrupt mode
      }

    }

  }

}
