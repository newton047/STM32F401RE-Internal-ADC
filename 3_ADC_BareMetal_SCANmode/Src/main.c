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
/*Note this code is still need improvement and hence it is not working
 *
 *
 * */


/*Using GPIOA0  ADC1_IN0
 * Using GPIOA1 (ADC1_IN1)as input to ADC
 * GPIO A4 ADC1_IN4
 * GPIO B0 ADC1_IN8
 *
 * Following conversion sequence A0-B0 -A1-A4
 * */
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

typedef struct{
	float AN[4];
}ADC_Vals_t;
uint16_t data2[10];

int main(void)
{
	uint16_t data;
	float  ADC_volt;
	ADC_Vals_t ADCVal;
	int i=0,j=0;
	/*Enable clock to GPIO peripheral*/

	RCC->AHB1ENR|= (0x1<<RCC_AHB1ENR_GPIOAEN_Pos);  //Enable GPIOA
	RCC->AHB1ENR |= (0x1<<RCC_AHB1ENR_GPIOBEN_Pos);  //Enable GPIOB
	/*Set GPIO to Analog Mode*/
	GPIOA->MODER |= (0x3<<GPIO_MODER_MODER0_Pos); // GPIO A0
	GPIOA->MODER |= (0x3<<GPIO_MODER_MODER1_Pos); //GPIO A1
	GPIOA->MODER |= (0x3<<GPIO_MODER_MODER4_Pos); //GPIO A4
	GPIOB->MODER |= (0x3<<GPIO_MODER_MODER0_Pos); //GPIO B0

	/*Enable clock to ADC peripheral*/
	RCC->APB2ENR |=(0x1<<RCC_APB2ENR_ADC1EN_Pos);

	/*Configure ADC trigerring and resolution*/
	ADC1->CR2=0;




	/*Set conversion sequence and length*/
	ADC1->SQR1 |= (0x3<<ADC_SQR1_L_Pos); //Set length of sequence

	ADC1->SQR3 |= (0x0 <<  ADC_SQR3_SQ1_Pos);     //Set Sequence number ADC1_IN0
	ADC1->SQR3 |= (0x8<<ADC_SQR3_SQ2_Pos);  //ADC1_IN8
	ADC1->SQR3 |= (0x1<<ADC_SQR3_SQ3_Pos);    //ADC1_IN1
	ADC1->SQR3 |= (0x4<<ADC_SQR3_SQ4_Pos);   //ADC1_IN4


	/*SCAN mode*/
	ADC1->CR1 |= (1<<ADC_CR1_SCAN_Pos);


	//Enable COntinous Mode
	ADC1->CR2 |= (0x1<<ADC_CR2_CONT_Pos);

	//Enable EOCS Mode
	ADC1->CR2 |= ADC_CR2_EOCS_Msk;
	/*Enable ADC*/
	ADC1->CR2 |=(0x1<<ADC_CR2_ADON_Pos);

	/*Start conversion*/
	ADC1->CR2 |= (1<<ADC_CR2_SWSTART_Pos);



	for(;;){



		/*Wait for conversion to end*/
		while(!(ADC1->SR & ADC_SR_EOC));


		/*REad Data*/
		data = ADC1->DR;
		data2[j] =data;
		(j==10)?j=0:j++;
		/*Multiply with prescaler
		 * data is 12Bit resolution
		 *
		 * */
		ADC_volt = ((3.3/4095)*data);
		ADCVal.AN[i++] =ADC_volt;
		if(i==4){
			i=0;
		}

}



}
