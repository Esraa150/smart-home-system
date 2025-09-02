/*
 * ADC_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


/* Enum for Reference Voltage */
typedef enum
{
	ADC_REFERENCE_AVCC = 0,   
	ADC_REFERENCE_AREF,  
	ADC_REFERENCE_INTRNAL,
}ADC_refVolt_t;

/* Enum for Channel Number as Single Ended Input */
typedef enum
{
	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
}ADC_channelIds_t;

                 /*************** APIS PROTOTYPES ***************/
				
void ADC_voidInit           (ADC_refVolt_t copy_tReferenceVoltage);
void ADC_voidGetDigitalValue(ADC_channelIds_t copy_tChannelId, u16* copy_pu16DigitalValue);


#endif /* ADC_INTERFACE_H_ */
