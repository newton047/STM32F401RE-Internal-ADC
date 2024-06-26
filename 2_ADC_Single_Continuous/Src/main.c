/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f4xx.h"

/*Using GPIOA1 (ADC1_IN1)as input to ADC*/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	uint16_t data;
	float  ADC_volt;

	RCC->AHB1ENR|= (1<<RCC_AHB1ENR_GPIOAEN_Pos);   	/*Enable clock to GPIO peripheral*/

	GPIOA->MODER |= (0x3<<GPIO_MODER_MODER1_Pos);	/*Set GPIO to Analog Mode*/


	RCC->APB2ENR |=(1<<RCC_APB2ENR_ADC1EN_Pos);		/*Enable clock to ADC peripheral*/


	ADC1->CR2=0;									/*Configure ADC trigerring and resolution*/


	/*Set conversion sequence and length*/

	ADC1->SQR1 &= ~(0xF<<ADC_SQR1_L_Pos); 					/*Set length of sequence*/
	ADC1->SQR3 |= (1<<ADC_SQR3_SQ1_Pos);     				 /*Set Sequence number*/


	ADC1->CR2 |= (ADC_CR2_CONT_Msk);                         /*Enable continous conversion*/
	ADC1->CR2 |=(1<<ADC_CR2_ADON_Pos);						/*Enable ADC*/

	ADC1->CR2 |= (1<<ADC_CR2_SWSTART_Pos);				/*Start conversion*/

	for(;;){



 		while(!(ADC1->SR & ADC_SR_EOC_Msk));				/*Wait for conversion to end*/
		/*REad Data*/
		data = ADC1->DR;
		/*Multiply with prescaler
		 * data is 12Bit resolution
		 *
		 * */
		ADC_volt = ((3.3/4095)*data);

	}
}
