/*
 * smart_home_automation_system.c
 *
 * Created: 8/16/2025 7:32:24 PM
 * Author : Adminz
 */ 

#include <avr/io.h>
#define F_CPU 16000000ul
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "LCD_interface.h"
#include "UART_interface.h"
#include "KPD_interface.h"
#include "PWM1_interface.h"
#include "PWM0_interface.h"
#include "ADC_interface.h"

u8 login();
void Control_AC();

int main(void)
{
	ADC_voidInit(ADC_REFERENCE_INTRNAL);
	UART_voidInit();
	PWM0_voidInit();
	
	u8 mode = login();
	u8 active;
	u8 actions;
	
	// for L293D (DC motor)
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN0, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN1, DIO_PIN_OUTPUT);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN0, DIO_PIN_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN1, DIO_PIN_LOW);
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_PIN_OUTPUT);
	
	//for buzzer
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN6, DIO_PIN_OUTPUT);
	
	//for lamps
	LED_voidInit(DIO_PORTA, DIO_PIN6);
	LED_voidInit(DIO_PORTA, DIO_PIN7);
	LED_voidInit(DIO_PORTB, DIO_PIN5);
	LED_voidInit(DIO_PORTB, DIO_PIN6);
	LED_voidInit(DIO_PORTB, DIO_PIN7);
	
	//PWM0 for dimmable lamp
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);
	
	//PWM1 foe servo motor
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);
	PWM1_voidInitChannel1A();
	
    while (1) 
    {
		if(mode == 0){  // System Lockdown
			while(1);
		}
		
		else if(mode == 2){ //admin mode
			UART_voidTxString("lamps(1:6)   open door(7)  close door(8)");
			while(1){
				Control_AC();
				if(GET_BIT(UCSRA, 7)){
					UART_voidRxChar(&actions);
					if(actions == '1'){
						LED_voidToggle(DIO_PORTA, DIO_PIN6);
					}
					else if(actions == '2'){
						LED_voidToggle(DIO_PORTA, DIO_PIN7);
					}
					else if(actions == '3'){
						LED_voidToggle(DIO_PORTB, DIO_PIN5);
					}
					else if(actions == '4'){
						LED_voidToggle(DIO_PORTB, DIO_PIN6);
					}
					else if(actions == '5'){
						LED_voidToggle(DIO_PORTB, DIO_PIN7);
					}
					else if(actions == '6'){
						UART_voidTxString("  enter percentage(0:10): ");
						UART_voidRxChar(&actions);
						PWM0_voidStop();
						PWM0_voidGeneratePWM(actions*10);
					}
					else if(actions == '7'){  // open door
						PWM1_voidGeneratePWM_channel1A(50, 10);
					}
					else if(actions == '8'){  // close door
						PWM1_voidGeneratePWM_channel1A(50, 7.5);
					}
				}
			}
		}
		
		else if(mode == 1){ //user mode
			LCD_voidClear();
		    LCD_voidDisplayString("lamps(1:6)  ");
			DIO_voidGetPinValue(DIO_PORTA, DIO_PIN6, &active);
			if(active == 1)   LCD_voidDisplayString("LED1 on ");
			DIO_voidGetPinValue(DIO_PORTA, DIO_PIN7, &active);
			if(active == 1)   LCD_voidDisplayString("LED2 on ");
			DIO_voidGetPinValue(DIO_PORTB, DIO_PIN5, &active);
			if(active == 1)   LCD_voidDisplayString("LED3 on ");
			DIO_voidGetPinValue(DIO_PORTB, DIO_PIN6, &active);
			if(active == 1)   LCD_voidDisplayString("LED4 on ");
			DIO_voidGetPinValue(DIO_PORTB, DIO_PIN7, &active);
			if(active == 1)   LCD_voidDisplayString("LED5 on ");
	
			while(1){
				Control_AC();
				KPD_voidGetValue(&actions);
				if(actions != KPD_NOT_PRESSED)   break;
			}
			if(actions == '1'){
				LED_voidToggle(DIO_PORTA, DIO_PIN6);
			}
			else if(actions == '2'){
				LED_voidToggle(DIO_PORTA, DIO_PIN7);
			}
			else if(actions == '3'){
				LED_voidToggle(DIO_PORTB, DIO_PIN5);
			}
			else if(actions == '4'){
				LED_voidToggle(DIO_PORTB, DIO_PIN6);
			}
			else if(actions == '5'){
				LED_voidToggle(DIO_PORTB, DIO_PIN7);
			}
			else if(actions == '6'){
				LCD_voidClear();
				LCD_voidDisplayString("enter percentage: ");
				while(1){
					KPD_voidGetValue(&actions);
					if(actions != KPD_NOT_PRESSED){
						PWM0_voidStop();
						PWM0_voidGeneratePWM(actions*10);
						break;
					}
				}
			}
		}
    }
}

u8 login(){
	u8 AdminPassword[] ="AdminG9B5M8";
	u32 UserPassword = 7085;
	
	u8 input[12];
	u8 attempts=0;
	u8 i=0;
	u8 EnteredDigit;
	u32 EnteredPassword=0;
	
	UART_voidInit();
	KPD_voidInit();
	LCD_voidInit();
	
	LCD_voidDisplayString("Enter password: ");
	UART_voidTxString("Enter password: ");
	
	while(attempts < 3){
		while(1){
			KPD_voidGetValue(&EnteredDigit);
			if(EnteredDigit != KPD_NOT_PRESSED){
				// user mode
				EnteredPassword = 0;
				EnteredPassword=EnteredPassword*10 + (EnteredDigit - '0');
				i=0;
				while(i<3){
					KPD_voidGetValue(&EnteredDigit);
					if(EnteredDigit != KPD_NOT_PRESSED){
						EnteredPassword = EnteredPassword*10 + (EnteredDigit - '0');
						i++;
					}
				}
				if(EnteredPassword == UserPassword){
					LCD_voidClear();
					LCD_voidDisplayString("Welcome User!");
					_delay_ms(1500);
					return 1;
				}
				else{
					attempts++;
					LCD_voidClear();
					LCD_voidDisplayString("Wrong. Try Again  ");
					break;
				}
			}
			
			else if(GET_BIT(UCSRA, 7)){
				UART_voidRxString(input);
				if(strlen((char*)input) > 0){
					// admin mode
					if(strcmp((char*)input, (char*)AdminPassword) == 0){
						UART_voidTxString("Welcome Admin!");
						return 2;
					}
					else{
						attempts++;
						UART_voidTxString("Wrong. Try Again  ");
						break;
					}
				}
			}
		}
	}
	LCD_voidDisplayString("System Lockdown");
	UART_voidTxString("System Lockdown");
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN6, DIO_PIN_HIGH);
	return 0;
}

void Control_AC(){
	u16 digitalValue;
	u32 analogValue;
	u16 temp;
	ADC_voidGetDigitalValue(ADC_CHANNEL_0, &digitalValue);
	analogValue = ((u32)digitalValue*2.56*1000)/1024;
	temp = analogValue/10;
	if(temp<21){
		DIO_voidSetPinValue(DIO_PORTD, DIO_PIN2, DIO_PIN_LOW);
	}
	else if(temp>28){
		DIO_voidSetPinValue(DIO_PORTD, DIO_PIN2, DIO_PIN_HIGH);
	}
}