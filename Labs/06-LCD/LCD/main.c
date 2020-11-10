/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include <string.h>


/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */

uint8_t customChar[] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,	//first column 
	
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,	//second column
	
	0b11000,
	0b11000,
	0b11000,
	0b11000,
	0b11000,
	0b11000,
	0b11000,
	0b11000,	//thrid column
	
	0b11100,
	0b11100,
	0b11100,
	0b11100,
	0b11100,
	0b11100,
	0b11100,
	0b11100,	//fourth column
	
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111		//fifht column
	
};

int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    // Put string(s) at LCD display
    lcd_gotoxy(1, 0);
    lcd_puts("00:00.0");
	lcd_gotoxy(12, 1);
    lcd_putc('D');
	lcd_gotoxy(13, 1);
	lcd_putc('E');
	lcd_gotoxy(14, 1);
	lcd_putc('2');
	
	// Set pointer to beginning of CGRAM memory
	lcd_command(1 << LCD_CGRAM);
	for (uint8_t i = 0; i < 42; i++)
	{
		// Store all new chars to memory line by line
		lcd_data(customChar[i]);
	}
	// Set DDRAM address
	lcd_command(1 << LCD_DDRAM);
	 
	

    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set prescaler and enable overflow interrupt every 16 ms
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();
	
	// Configure 8-bit Timer/Counter0 for Stopwatch
	// Set prescaler and enable overflow interrupt every 16 ms
	TIM0_overflow_16ms();
	TIM0_overflow_interrupt_enable();
	
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16 ms = 100 ms).
 */
ISR(TIMER2_OVF_vect)
{
	static uint8_t number_of_overflows = 0;
	static uint8_t number_of_overflows2 = 0;
	static uint8_t tens = 0;        // Number of tens
	static uint8_t secs = 0;		// First number of seconds
	static uint8_t Second_secs = 0; // Second number of seconds
	static uint8_t min = 0;			// First number of minutes
	static uint8_t Second_min = 0;	// Second number of minutes
	static uint8_t square = 0;    		// Secs for square
	char lcd_string[2] = "  ";      // String for converting numbers by itoa()
	char buff[2] = "  ";
	number_of_overflows++;
	number_of_overflows2++;
	
	if (number_of_overflows2 >=60 )
	{
		number_of_overflows2=0;		//function of square 
		square++;
		if(square >= 60) 
		{
			square=0; 
			lcd_gotoxy(12, 0);
			lcd_puts(" ");
			lcd_gotoxy(13, 0);
			lcd_puts(" ");
			lcd_gotoxy(14, 0);
			lcd_puts(" ");
			}
		itoa(square*square, buff,10);
		lcd_gotoxy(11, 0);
		lcd_puts(buff);
	}
	
	if (number_of_overflows >= 6)
	{
		// Do this every 6 x 16 ms = 100 ms
		number_of_overflows = 0;
		
		tens ++;
		if (tens > 9)
		{
			tens = 0;
			secs ++;
		}
		if(secs > 9)
		{
			secs=0;
			Second_secs++;
		}
		if(Second_secs >= 6)
		{
			Second_secs=0;
			min++;
		}
		if(min >= 9)
		{
			min=0;
			Second_min++;
		}
		if(Second_min >= 6)
		{
			Second_min=0;
		}
		// Convert decimal value to string
		itoa(tens, lcd_string, 10);
		lcd_gotoxy(7, 0);
		lcd_puts(lcd_string);
		itoa(secs, lcd_string, 10);
		lcd_gotoxy(5, 0);
		lcd_puts(lcd_string);
		itoa(Second_secs, lcd_string, 10);
		lcd_gotoxy(4, 0);
		lcd_puts(lcd_string);
		itoa(min, lcd_string, 10);
		lcd_gotoxy(2, 0);
		lcd_puts(lcd_string);
		itoa(Second_min, lcd_string, 10);
		lcd_gotoxy(1, 0);
		lcd_puts(lcd_string);
		
		
		
		
	}
}

ISR(TIMER0_OVF_vect)
{
	static uint8_t character = 0;
	static uint8_t position = 0;
	static uint8_t overflow = 0;

	overflow++;
	
	if(overflow == 2){
		character++;
		overflow=0;
	}
	if (character == 5)
	{
		character = 0;
		position++;
		if (position == 6)
		{
			position = 0;
			lcd_gotoxy(1, 1);
			lcd_puts(" ");
			lcd_gotoxy(2, 1);
			lcd_puts(" ");
			lcd_gotoxy(3, 1);
			lcd_puts(" ");
			lcd_gotoxy(4, 1);
			lcd_puts(" ");
			lcd_gotoxy(5, 1);
			lcd_puts(" ");
			lcd_gotoxy(6, 1);
			lcd_puts(" ");
			
		}
		
	}
	
	lcd_gotoxy(1 + position, 1);
	lcd_putc(character);
	
	
	
}