/*
 * UART_interface.h
 *
 *  Created on: ???/???/????
 *      Author: Kareem Hussein
 */

#ifndef MCAL_UART_INC_UART_INTERFACE_H_
#define MCAL_UART_INC_UART_INTERFACE_H_


                 /*************** APIS PROTO TYPES ***************/
				 
void UART_voidInit    (void);
void UART_voidTxChar  (u8  copy_u8TxData);
void UART_voidRxChar  (u8* copy_pu8RxData);
void UART_voidTxString(u8* copy_pu8TxString);
void UART_voidRxString(u8* copy_pu8RxString);


#endif /* MCAL_UART_INC_UART_INTERFACE_H_ */
