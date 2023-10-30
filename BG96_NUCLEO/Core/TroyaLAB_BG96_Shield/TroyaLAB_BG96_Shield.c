/*
 * TroyaLAB_BG96_Shield.c
 *
 *  Created on: Oct 23, 2023
 *      Author: fatih
 */

#include "TroyaLAB_BG96_Shield.h"

alinan_veriler_t  alinan_veriler_st;



void sendATComm(UART_HandleTypeDef uart_module_t, char *user_data_u8)
{

  HAL_UART_Transmit(&uart_module_t, (uint8_t*)user_data_u8, strlen(user_data_u8),10); // Sending in normal mode
  HAL_Delay(2000);

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    if (huart->Instance == USART1) {
        if (alinan_veriler_st.buffer_size_u16 < BUFFER_SIZE - 1) {

          alinan_veriler_st.alinan_data_buffer_a8[alinan_veriler_st.buffer_size_u16++] = alinan_veriler_st.alinan_data_u8; // receivedData, UART verisi
          HAL_UART_Receive_IT (huart, &alinan_veriler_st.alinan_data_u8, 1); //receive data from data buffer interrupt mode

        }
    }
    // Başka UART'lar için gerekirse benzer işlemleri yapabilirsiniz
}

void set_bg96_receivedData(uint8_t receivedData)
{
  alinan_veriler_st.alinan_data_u8 = receivedData;
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//
//   if(recvd_data == '\n') //when enter is pressed go to this condition
//   {
//     data_buffer[count++]='\n';
//
//     if(data_buffer[count-2] == '\r') //when enter is pressed go to this condition
//     {
//       if(data_buffer[count-3] == '\r')
//       {
//         // gonderilen mesaj
//       }
//       else // alinan mesaj
//       {
//         komut_gonder_devam_flag = 1;
//       }
//       HAL_UART_Receive_IT(&huart1, &recvd_data, 1); //start next data receive interrupt
//     }
//     HAL_UART_Receive_IT(&huart1, &recvd_data, 1); //start next data receive interrupt
//
//     //HAL_UART_Transmit(&huart1,data_buffer,count,HAL_MAX_DELAY); //transmit the full sentence again
//     //memset(data_buffer, 0, count); // enpty the data buffer
//   }
//   else
//   {
//     data_buffer[count++] = recvd_data; // every time when interrput is happen, received 1 byte of data
//     //return TROYALAB_ERROR;
//   }
//
//   HAL_UART_Receive_IT(&huart1, &recvd_data, 1); //start next data receive interrupt
//
//}


