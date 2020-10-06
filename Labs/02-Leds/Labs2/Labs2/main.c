/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_01   PB1     // AVR pin where green LED is connected
#define LED_02   PB2
#define LED_03	 PB3
#define LED_04	 PB4
#define LED_05	 PB5
#define BLINK_DELAY 250
#define BTN			PD0
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed.
 */
int main(void)
{
	// Set pin as output in Data Direction Register...
		DDRB = DDRB | (1<<LED_01);
	// ...and turn LED off in Data Register
		PORTB = PORTB & ~(1<<LED_01);
	// Set pin as output in Data Direction Register...
		DDRB = DDRB | (1<<LED_02);
	// ...and turn LED off in Data Register
		PORTB = PORTB & ~(1<<LED_02);
	// Set pin as output in Data Direction Register...
		DDRB = DDRB | (1<<LED_03);
	// ...and turn LED off in Data Register
		PORTB = PORTB & ~(1<<LED_03);
	// Set pin as output in Data Direction Register...
		DDRB = DDRB | (1<<LED_04);
	// ...and turn LED off in Data Register
		PORTB = PORTB & ~(1<<LED_04);
	// Set pin as output in Data Direction Register...
		DDRB = DDRB | (1<<LED_05);
	// ...and turn LED off in Data Register
		PORTB = PORTB & ~(1<<LED_05);
	//set pin as input in Data Direction Register
	
	//button with pullup ressistor 
	DDRD = DDRD  & ~(1<<BTN);
	PORTD = PORTD | (1<<BTN);
	
    // Infinite loop
    while (1)
{
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);
		if (bit_is_clear(PIND, BTN));
	{
        // WRITE YOUR CODE HERE
	PORTB = PORTB ^ (1<<LED_01);
	_delay_ms(BLINK_DELAY);
	PORTB = PORTB ^ (1<<LED_01);
	PORTB = PORTB ^ (1<<LED_02);
	_delay_ms(BLINK_DELAY);
	PORTB = PORTB ^ (1<<LED_02);
	PORTB = PORTB ^ (1<<LED_03);
	_delay_ms(BLINK_DELAY);
	PORTB = PORTB ^ (1<<LED_03);
	PORTB = PORTB ^ (1<<LED_04);
	_delay_ms(BLINK_DELAY);
	PORTB = PORTB ^ (1<<LED_04);
	PORTB = PORTB ^ (1<<LED_05);
	_delay_ms(BLINK_DELAY);
	PORTB = PORTB ^ (1<<LED_04);
	PORTB = PORTB ^ (1<<LED_05);
	_delay_ms(BLINK_DELAY);
	PORTB = PORTB ^ (1<<LED_03);
	PORTB = PORTB ^ (1<<LED_04);
	_delay_ms(BLINK_DELAY);
	PORTB = PORTB ^ (1<<LED_02);
	PORTB = PORTB ^ (1<<LED_03);
	_delay_ms(BLINK_DELAY);
	PORTB = PORTB ^ (1<<LED_02);
    }
}

    // Will never reach this
    return 0;
}