/*
 *
 * @file LCD_config.h
 * @author Kareem Hussein
 * @brief configuration header file contain configuraron macros for LCD
 * @date 17/08/2024      
 * @version 1.0
 *
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/* Macros For Rs configuration */
#define LCD_RS_PORT			DIO_PORTA
#define LCD_RS_PIN          DIO_PIN3


/* Macros For Enable configuration */
#define LCD_E_PORT			DIO_PORTA
#define LCD_E_PIN           DIO_PIN2

                   /* LCD DATA CONFIGURATIONS */
/*
LCD mode options
1- LCD_8_BIT_MODE
2- LCD_4_BIT_MODE
*/
#define LCD_MODE			LCD_4_BIT_MODE

/* 8 Bit Mode Data Port Configurations */
#define LCD_DATA_PORT			DIO_PORTB


/* 4 Bit Mode Data Pins Configurations */
#define LCD_D4_PORT			DIO_PORTB
#define LCD_D4_PIN          DIO_PIN0

#define LCD_D5_PORT			DIO_PORTB
#define LCD_D5_PIN          DIO_PIN1

#define LCD_D6_PORT			DIO_PORTB
#define LCD_D6_PIN          DIO_PIN2

#define LCD_D7_PORT			DIO_PORTB
#define LCD_D7_PIN          DIO_PIN4


#endif /* LCD_CONFIG_H_ */
