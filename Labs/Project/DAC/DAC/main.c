/***********************************************************************
 * 
 * Analog-to-digital conversion with displaying result on LCD and 
 * transmitting via UART.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
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
#include "uart.h"           // Peter Fleury's UART library
#include <math.h>
#ifndef F_CPU
#define F_CPU 16000000
#endif
uint16_t DTMF = 0;
uint16_t x = 0;
float T = 5;
float Tvz=0.001;
uint16_t duration = 0;
uint8_t fceType = 10;//0..sin, 1..saw, 2..triangle
uint16_t i = 0;

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Use Timer/Counter1
 * and start ADC conversion four times per second. Send value to LCD
 * and UART.
 */

//function for generating signals values
unsigned int fce(unsigned int i ) {
	
	if(fceType==0) 
		return (unsigned int)(255*(1 + sin(i * 6.28 * Tvz/T))/2); //returns sin values
	else if(fceType==1)
		return (unsigned int)(255 * fmod(i*Tvz,T)/T);			  //returns saw values
	else if(fceType==2) {										  //returns triangle values
		int j = (int)(i*Tvz/(T/2));
		float a = 2*fmod(i*Tvz,T)/T; 
		a = 255*(j%2==0? a : 1 - a);   
		return (unsigned int)a;	
	}
	else if(fceType==10)										  //stops signal generating
	return (uint8_t)(0);
}
// function for recognition each bit values
unsigned setByte(unsigned int num) {
	if (num & (0x01 << 0)) GPIO_write_high(&PORTD,PD3); else GPIO_write_low(&PORTD,PD3);
	if (num & (0x01 << 1)) GPIO_write_high(&PORTD,PD2); else GPIO_write_low(&PORTD,PD2);
	if (num & (0x01 << 2)) GPIO_write_high(&PORTD,PD1); else GPIO_write_low(&PORTD,PD1);
	if (num & (0x01 << 3)) GPIO_write_high(&PORTD,PD0); else GPIO_write_low(&PORTD,PD0);
	if (num & (0x01 << 4)) GPIO_write_high(&PORTC,PC6); else GPIO_write_low(&PORTC,PC6);
	if (num & (0x01 << 5)) GPIO_write_high(&PORTC,PC5); else GPIO_write_low(&PORTC,PC5);
	if (num & (0x01 << 6)) GPIO_write_high(&PORTC,PC4); else GPIO_write_low(&PORTC,PC4);
	if (num & (0x01 << 7)) GPIO_write_high(&PORTC,PC3); else GPIO_write_low(&PORTC,PC3);		
}

int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);
    lcd_gotoxy(1, 0); lcd_puts("adc_value:");
    lcd_gotoxy(1, 1); lcd_puts("prubeh:");
	//config output 
	GPIO_config_output(&DDRD, PD0);
	GPIO_config_output(&DDRD, PD1);
	GPIO_config_output(&DDRD, PD2);
	GPIO_config_output(&DDRD, PD3);
	GPIO_config_output(&DDRB, PB6);
	GPIO_config_output(&DDRC, PC3);
	GPIO_config_output(&DDRC, PC4);
	GPIO_config_output(&DDRC, PC5);
	GPIO_config_output(&DDRC, PC6);
	// Enable interrupt and set the overflow prescaler to 262 ms
	TIM2_overflow_interrupt_enable();
	TIM2_overflow_16us();
	TIM1_overflow_interrupt_enable();
	TIM1_overflow_262ms();
	TIM0_overflow_interrupt_enable();
	TIM0_overflow_4ms();
	// Configure ADC to convert PC0[A0] analog value
	// Set ADC reference to AVcc
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	// Set input channel to ADC0
	ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3));
	// Enable ADC module
	ADCSRA |= (1<<ADEN);
	// Enable conversion complete interrupt
	ADCSRA |= (1<<ADIE);
	// Set clock prescaler to 128
	ADCSRA |= ((1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2));
	// Initialize UART to asynchronous, 8N1, 9600
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
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
 * ISR starts when Timer/Counter1 overflows. Use single conversion mode
 * and start conversion four times per second.
 */
ISR(TIMER1_OVF_vect)
{	
	// Start ADC conversion
	ADCSRA |= (1<<ADSC);
}

ISR(TIMER0_OVF_vect)
{
	uint16_t a =fce(i++); //calls for signal values
	setByte(a);			  //calls for bit recognition
}	

ISR(TIMER2_OVF_vect)
	// DTMF generator
{ 
	x++;
	if (x>=(DTMF/2)&&duration>1){
		GPIO_toggle(&PORTB,PB6);
		x=0;
		duration=duration-1;
	}
}

ISR(ADC_vect)
{
	uint16_t value = ADC;
	char lcd_string[6] ="      ";
	itoa(value, lcd_string, 10); // value to dacimal
	if (value < 700) // reduce amount of sent uart data
	{
		uart_puts("ADC value in decimal:");
		uart_puts(lcd_string); // send uart value in decimal
		uart_puts("\n");
	}
	lcd_gotoxy(12, 0);
	lcd_puts("    "); //clear area
	lcd_gotoxy(12, 0);
	lcd_puts(lcd_string); // show decimal
	
	if (value>465 && value<520){fceType=0;DTMF=34;duration=300;}    //key1
	if (value>360 && value<380){fceType=1;DTMF=32;duration=300;}	//key2
	if (value>198 && value<208){fceType=2;DTMF=30;duration=300;}	//key3
	if (value>450 && value<460){DTMF=32;duration=300;}				//key4
	if (value>330 && value<340){DTMF=30;duration=300;}				//key5
	if (value>140 && value<150){DTMF=29;duration=300;}				//key6
	if (value>420 && value<432){DTMF=32;duration=300;}				//key7
	if (value>290 && value<300){DTMF=29;duration=300;}				//key8
	if (value>70 && value<80){DTMF=27;duration=300;}				//key9									
	if (value>390 && value<410){T=T*2;}								//key*
	if (value>240 && value<250){T=T/2;}								//key0
	if (value==0)fceType=10;										//key#
		if (fceType==0){lcd_gotoxy(12, 1); lcd_puts("sin");}
		if (fceType==1){lcd_gotoxy(12, 1); lcd_puts("saw");}
		if (fceType==2){lcd_gotoxy(12, 1); lcd_puts("tri");}
		if (fceType==10){lcd_gotoxy(12, 1); lcd_puts("off");}
	



}