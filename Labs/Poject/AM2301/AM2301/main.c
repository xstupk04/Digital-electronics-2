/*
 * AM2301.c
 *
 * Created: 13.12.2020 17:32:45
 * Author : Mila
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "dht.h"

#define UART_BAUD_RATE 2400
#include "uart.h"
#include "lcd.h"
float temperature;


int main(void)
{
	lcd_init(LCD_DISP_ON);
	lcd_gotoxy(1, 0); lcd_puts("tem:");

	  
	char printbuff[100];

	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	//init interrupt
	sei();

	#if DHT_FLOAT == 0
	int8_t temperature = 0;
	int8_t humidity = 0;
	#elif DHT_FLOAT == 1
	float temperature = 0;
	float humidity = 0;
	#endif

	for (;;) {
		if(dht_gettemperaturehumidity(&temperature, &humidity) != -1) {

			#if DHT_FLOAT == 0
			itoa(temperature, printbuff, 10);
			#elif DHT_FLOAT == 1
			dtostrf(temperature, 3, 3, printbuff);
			#endif
			uart_puts("temperature: "); uart_puts(printbuff); uart_puts("C");uart_puts("\r\n");
			#if DHT_FLOAT == 0
			itoa(humidity, printbuff, 10);
			#elif DHT_FLOAT == 1
			dtostrf(humidity, 3, 3, printbuff);
			#endif
			uart_puts("humidity: "); uart_puts(printbuff); uart_puts("%RH");uart_puts("\r\n");

			} else {
			uart_puts("error"); uart_puts("\r\n");
		}

		uart_puts("\r\n");

		_delay_ms(1500);
	}
	
	while (1)
	{	
		/*---- Show data over LCD ----*/
		char lcd_string [] ="";	
		//clear decimal and hex position
		lcd_gotoxy(8,0);
		lcd_puts(lcd_string);
			
		//print ADC valeu on LCD in decimal
		itoa (temperature, lcd_string, 10);
		lcd_gotoxy(8,0);
		lcd_puts(lcd_string);
		
		
	//	realne = (float) 5.03 / 1023;
	//	realne = (float) realne * vysledek;
	//	vysledek = (float) realne * 100;
	//	if (kanal) kanal = 0; else kanal = 1;
	delay_ms(1000);
	}

	return 0;

}





