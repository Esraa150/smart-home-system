/*
 * PWM0_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

#ifndef MCAL_PWM0_INC_PWM0_INTERFACE_H_
#define MCAL_PWM0_INC_PWM0_INTERFACE_H_


                /*************** APIS PROTOTYPES ***************/

void PWM0_voidInit       (void);
void PWM0_voidGeneratePWM(u8 copy_u8DutyCycle);
void PWM0_voidStop       (void);


#endif /* MCAL_PWM0_INC_PWM0_INTERFACE_H_ */
