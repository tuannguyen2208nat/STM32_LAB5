/*
 * fsm_uart.c
 *
 *  Created on: Dec 20, 2023
 *      Author: tuann
 */

#include "main.h"
#include "fsm_uart.h"
#include "global.h"
#include "software_timer.h"

#include <stdio.h>

uint32_t ADC_value = 0;
char response[RESPONSE_LENGTH];
uint8_t data[] = "HELLO WORLD \r\n";
void uart_communiation_fsm(){
	switch(uartState){
	case UART_IDLE:
		//HAL_UART_Transmit(&huart2, (void *)response, sprintf(response, "HELLO WORLD\r\n"), 1000);

		break;
	case UART_RST:
//		HAL_UART_Transmit(&huart2, (void *)response, sprintf(response, "HELLO WORLD\r\n"), 1000);
//		HAL_UART_Transmit(&huart2, data, sizeof(data), 1000);
		uartState = UART_RESPONSE;
		break;
	case UART_RESPONSE:
		ADC_value = HAL_ADC_GetValue(&hadc1);
		HAL_UART_Transmit(&huart2, (void *)response, sprintf(response, "!ADC%ld#\r", ADC_value), 1000);
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		settimer1(TIME_FOR_3S);
		uartState = UART_WAIT_OK;
		//cmd_content_index = 0;
		break;
	case UART_WAIT_OK:
		if(timer1_flag == 1) {
			uartState = UART_END;
		}

		break;
	case UART_END:
		if(isOK == 1) isOK = 0;
		HAL_UART_Transmit(&huart2, (void *)response, sprintf(response, "END RST\r\n"), 1000);
		uartState = UART_IDLE;
		break;
	case UART_ERROR:
		HAL_UART_Transmit(&huart2, (void *)response, sprintf(response, "OH NO! STH WRONG HAPPENNED\r\n"), 1000);
		uartState = UART_IDLE;
		break;
	default:
		break;
	}
}

void command_parser_fsm(){
	switch(cmdState){
	case CMD_IDLE:
		if(cmdBuffer[cmd_content_index] == '!'){
			cmdState = CMD_EXCLAMATION;
		}
		else if(cmdBuffer[cmd_content_index] == '\r' || cmdBuffer[cmd_content_index] == '\n'){
			cmdState = CMD_IDLE;
			//cmd_content_index = 0;
		}
		break;
	case CMD_EXCLAMATION:
		if(cmdBuffer[cmd_content_index] == 'R'){
			cmdState = CMD_R;
		}
		else if(cmdBuffer[cmd_content_index] == 'O'){
			cmdState = CMD_O;
		}
		else if(cmdBuffer[cmd_content_index] == '\r' || cmdBuffer[cmd_content_index] == '\n'){
			cmdState = CMD_IDLE;
			cmd_content_index = 0;
			uartState = UART_ERROR;
		}
		break;
	case CMD_R:
		if(cmdBuffer[cmd_content_index] == 'S'){
			cmdState = CMD_S;
		}
		else if(cmdBuffer[cmd_content_index] == '\r' || cmdBuffer[cmd_content_index] == '\n'){
			cmdState = CMD_IDLE;
			cmd_content_index = 0;
			uartState = UART_ERROR;
		}
		break;
	case CMD_S:
		if(cmdBuffer[cmd_content_index] == 'T'){
			cmdState = CMD_T;
		}
		else if(cmdBuffer[cmd_content_index] == '\r' || cmdBuffer[cmd_content_index] == '\n'){
			cmdState = CMD_IDLE;
			cmd_content_index = 0;
			uartState = UART_ERROR;
		}
		break;
	case CMD_T:
		if(cmdBuffer[cmd_content_index] == '#'){
			cmdState = CMD_HASTAG_T;
			isRST = 1;
		}
		else if(cmdBuffer[cmd_content_index] == '\r' || cmdBuffer[cmd_content_index] == '\n'){
			cmdState = CMD_IDLE;
			cmd_content_index = 0;
			uartState = UART_ERROR;
		}
		break;
	case CMD_O:
		if(cmdBuffer[cmd_content_index] == 'K'){
			cmdState = CMD_K;
		}
		else if(cmdBuffer[cmd_content_index] == '\r' || cmdBuffer[cmd_content_index] == '\n'){
			cmdState = CMD_IDLE;
			cmd_content_index = 0;
			uartState = UART_ERROR;
		}
		break;
	case CMD_K:
		if(cmdBuffer[cmd_content_index] == '#'){
			cmdState = CMD_HASTAG_K;
		}
		else if(cmdBuffer[cmd_content_index] == '\r' || cmdBuffer[cmd_content_index] == '\n'){
			cmdState = CMD_IDLE;
			cmd_content_index = 0;
			uartState = UART_ERROR;
		}
		break;
	case CMD_HASTAG_K:
		if(cmdBuffer[cmd_content_index] == '\r' || cmdBuffer[cmd_content_index] == '\n'){
			isOK = 1;
			uartState = UART_END;
			cmd_content_index = 0;
			cmdState = CMD_IDLE;
		}
		break;
	case CMD_HASTAG_T:
		if(cmdBuffer[cmd_content_index] == '\r' || cmdBuffer[cmd_content_index] == '\n'){
			uartState = UART_RST;
			cmdState = CMD_IDLE;
			cmd_content_index = 0;
		}
	default:
		break;
	}
}
