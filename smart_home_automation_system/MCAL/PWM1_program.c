/*
 * PWM1_program.c
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "PWM1_interface.h"
#include "PWM1_config.h"
#include "PWM1_private.h"
#include "PWM1_register.h"


void PWM1_voidInitChannel1A(void)
{
	// Select Mode = Fast PWM Mode(14)	
	CLR_BIT(TCCR1A_REG, WGM10);
	SET_BIT(TCCR1A_REG, WGM11);
	SET_BIT(TCCR1B_REG, WGM12);
	SET_BIT(TCCR1B_REG, WGM13);

	// Select Non Inverting Mode
	CLR_BIT(TCCR1A_REG, COM1A0);
	SET_BIT(TCCR1A_REG, COM1A1);
}


void PWM1_voidGeneratePWM_channel1A(u16 copy_u16FrequencyHz, f32 copy_f32DutyCycle)
{
	if(copy_f32DutyCycle <= 100)
	{
		// under condition tick time 4 MS by setting prescaller 64
		ICR1_u16_REG = ((1000000UL/copy_u16FrequencyHz)/4)-1;

		OCR1A_u16_REG = ((copy_f32DutyCycle * (ICR1_u16_REG+1)) / 100) - 1;

		//Select Prescaler Value = 64
		SET_BIT(TCCR1B_REG, CS10);
		SET_BIT(TCCR1B_REG, CS11);
		CLR_BIT(TCCR1B_REG, CS12);
	}
	else
	{
		//return Error State
	}
}


void PWM1_voidStopChannel1A(void)
{
	CLR_BIT(TCCR1B_REG, CS10);
	CLR_BIT(TCCR1B_REG, CS11);
	CLR_BIT(TCCR1B_REG, CS12);
}
