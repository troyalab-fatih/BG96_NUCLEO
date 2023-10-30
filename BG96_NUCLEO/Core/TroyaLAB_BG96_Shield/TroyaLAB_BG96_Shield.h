/*
 * TroyaLAB_BG96_Shield.h
 *
 *  Created on: Oct 23, 2023
 *      Author: fatih
 */

#ifndef TROYALAB_BG96_SHIELD_TROYALAB_BG96_SHIELD_H_
#define TROYALAB_BG96_SHIELD_TROYALAB_BG96_SHIELD_H_


#include "main.h"


#define BUFFER_SIZE 100


typedef struct{

  uint8_t     alinan_data_buffer_a8[BUFFER_SIZE];
  uint16_t    buffer_size_u16;
  uint8_t     alinan_data_u8;

}alinan_veriler_t;


void sendATComm(UART_HandleTypeDef uart_module_t, char *user_data_u8);
void set_bg96_receivedData(uint8_t receivedData);

#endif /* TROYALAB_BG96_SHIELD_TROYALAB_BG96_SHIELD_H_ */
