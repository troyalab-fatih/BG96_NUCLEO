/*
 * TroyaLAB_BG96_Shield.h
 *
 *  Created on: Oct 23, 2023
 *      Author: fatih
 */

#ifndef TROYALAB_BG96_SHIELD_TROYALAB_BG96_SHIELD_H_
#define TROYALAB_BG96_SHIELD_TROYALAB_BG96_SHIELD_H_


#include "main.h"


/*************************************  DEFINE  *************************************/


#define BUFFER_SIZE   250
#define TRYLAB_TRUE   1
#define TRYLAB_FALSE  0


/*************************************  DECLARATION  *************************************/


typedef enum
{
  TRYLAB_OK       = 0x00U,
  TRYLAB_ERROR    = 0x01U,
  TRYLAB_BUSY     = 0x02U,
  TRYLAB_TIMEOUT  = 0x03U
} TRYLAB_Status_t;


typedef struct{
  UART_HandleTypeDef       *uart_handle;
}BG96_uart_t;


typedef struct{
  uint32_t                 tick_freq_hz_u32;
  uint32_t                 time_past_ms_u32;
  uint32_t                 TRY_LAB_MAX_DELAY_ms_u32;
  uint8_t                  attemp_time_u8;
  uint8_t                  MAX_ATTEMPT;
}timeout_t;


typedef struct{
  uint8_t                  transfer_starting_u8;
  uint32_t                 transfer_continues_u8;

  char                     alinan_data_buffer_a8[BUFFER_SIZE];
  uint16_t                 buffer_size_u16;
  uint8_t                  alinan_data_u8;
  char                     BG96_reponse_char[BUFFER_SIZE];
}data_transfer_t;


typedef struct{
  timeout_t                timeout_st;
  BG96_uart_t              BG96_uart_st;
  data_transfer_t          data_transfer_st;
}TRYLAB;


/*************************************  FUNCTIONS PROTOTYPE  *************************************/

void troyalab_Stm_Shield_BG96_init(UART_HandleTypeDef *uart_module_t);

uint32_t sendATComm(char *user_data_u8, char *response_data_u8);

void set_bg96_receivedData(uint8_t receivedData);

void set_MAX_ATTEMPT( uint32_t MAX_ATTEMPT);

void set_MAX_DELAY_TIME( uint32_t MAX_DELAY);


#endif /* TROYALAB_BG96_SHIELD_TROYALAB_BG96_SHIELD_H_ */
