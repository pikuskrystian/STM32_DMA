#include <stdio.h>

#include <stdint.h>

#include "stm32f10x.h"

#define		BUFFER_SIZE					4096

volatile uint32_t 	timer_ms = 0;

uint8_t				src_buffer[BUFFER_SIZE];

uint8_t				dst_buffer[BUFFER_SIZE];

void copy_cpu()

{

	int i;

	for (i = 0; i < BUFFER_SIZE;i++)

		dst_buffer[i] = src_buffer[i];

}

void copy_dma()

{

	DMA_Cmd(DMA1_Channel1, DISABLE);

	DMA_ClearFlag(DMA_ISR_TCIF1);

	DMA_SetCurrDataCounter(DMA1_Channel1, BUFFER_SIZE);

	DMA_Cmd(DMA1_Channel1, ENABLE);

	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);

}

void SysTick_Handler()

{

	timer_ms++;

}

void send_char(char c)

{

	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

	USART_SendData(USART2, c);

}

int __io_putchar(int c)

{

	if (c=='\n')

		send_char('\r');

	send_char(c);

	return c;

}

int main(void)

{

	int i;

	GPIO_InitTypeDef gpio;

	USART_InitTypeDef uart;

	DMA_InitTypeDef dma;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	GPIO_StructInit(&gpio);

	gpio.GPIO_Pin = GPIO_Pin_2;

	gpio.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_3;

	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(GPIOA, &gpio);

	USART_StructInit(&uart);

	uart.USART_BaudRate = 115200;

	USART_Init(USART2, &uart);

	USART_Cmd(USART2, ENABLE);

	DMA_StructInit(&dma);

	dma.DMA_PeripheralBaseAddr = (uint32_t)src_buffer;

	dma.DMA_PeripheralInc = DMA_PeripheralInc_Enable;

	dma.DMA_MemoryBaseAddr = (uint32_t)dst_buffer;

	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;

	dma.DMA_BufferSize = BUFFER_SIZE;

	dma.DMA_M2M = DMA_M2M_Enable;

	DMA_Init(DMA1_Channel1, &dma);

	SysTick_Config(SystemCoreClock / 1000);

	timer_ms = 0;

	for (i = 0; i < 100; i++)

		copy_cpu();

	uint32_t cpu_ms = timer_ms;

	timer_ms = 0;

	for (i = 0; i < 100; i++)

		copy_dma();

	uint32_t dma_ms = timer_ms;

	printf("CPU copy: %ld ms\n", cpu_ms);

	printf("DMA copy: %ld ms\n", dma_ms);

	while (1) {

	}

}
