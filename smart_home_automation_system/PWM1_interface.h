/*
 * PWM1_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

#ifndef PWM1_INTERFACE_H_
#define PWM1_INTERFACE_H_


                /*************** APIS PROTOTYPES ***************/

void PWM1_voidInitChannel1A        (void);
void PWM1_voidGeneratePWM_channel1A(u16 copy_u16FrequencyHz, f32 copy_f32DutyCycle);
void PWM1_voidStopChannel1A        (void);


#endif /* PWM1_INTERFACE_H_ */
