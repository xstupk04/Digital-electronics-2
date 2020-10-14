# Home preparation

Consider an n-bit number that we increment based on the clock signal. If we reach its maximum value and try to increase it, the value will be reset. We call this state an overflow. 
Calculate the overflow times for three Timer/Counter modules that contain ATmega328P if CPU clock frequency is 16 MHz. Complete the following table for given prescaler values. Note that, Timer/Counter2 is able to set 7 prescaler values, including 32 and 128.
   

|     Module      | Number of bits |   1  |  8  | 32 |  64 | 128 |  256 | 1024 |
|-----------------|----------------|------|-----|----|-----|-----|------|------|
| Timer/Counter0  |       8        |  16u |128u | -- |1024u| - - |4096u |16384u|
| Timer/Counter1  |      16        |4.096m|32.8m| -- |262m | - - |1.0486|4.194 |
| Timer/Counter2  |       8        |  16u |128u |512u|1024u|2048u|4096u |16384u|  

|     Module      |    Operation   |   I/O registers  |  Bits  |
|-----------------|----------------|------------------|--------|
| Timer/Counter0  |Prescaler 8-bit data value; Overflow interrupt enable|TCCR0B; TCNT0L,TCNT0H; TIMSK0|CS02, CS01, CS00; (000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024); TCNT0[7:0]; TOIE0 (1: enable, 0: disable) |
| Timer/Counter1  |Prescaler; 16-bit data value; Overflow interrupt enable|TCCR1B; TCNT1H, TCNT1L, TIMSK1 |CS12, CS11, CS10 (000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)TCNT1[15:0], TOIE1 (1: enable, 0: disable)|
| Timer/Counter2  |Prescaler; 8-bit data value; Overflow interrupt enable|TCCR2B; TCNT2L,TCNT2H; TIMSK2|CS22, CS21, CS20; (000: stopped, 001: 1, 010: 8, 011: 32, 100: 64, 101: 128,110: 256,111:1024); TCNT2[7:0]; TOIE2 (1: enable, 0: disable)|

|Program addres      |  Source  | Vector name |Descripton |
|--------------------|----------|-------------|-----------|
| 0x0000             |Reset     |--           |Reset of the system|
| 0x0002             |INT0      |INT0_vect    |External interrupt request 0|
| 0x0004             |INT1      |INT1_vect    |External interrupt request 0|  
| 0x0006             |PCINT0    |PCINT0_vect  |Pin change interrupt request 0|
| 0x0008             |PCINT1    |PCINT1_vect  |Pin change interrupt request 1|  
| 0x000A             |PCINT2    |PCINT2_vect  |Pin change interrupt request 2|
| 0x000C             |WDT       |WDT_vect     |Watch dog time-out interrupt|
| 0x0012             |TIMER2_OVF|TIMER2_OVF_vect|Timer/Counter2 overflow|
| 0x0018             |TIMER1_COMPB|TIMER1_COMPB_vect|Compare match between Timer/Counter1 value and channel B compare value|
| 0x001A             |TIMER1_OVF |TIMER1_OVF_vect|Timer/Counter1 Overflow|
| 0x0020             |TIMER0_OVF |TIMER0_OVF_vect|Timer/Counter0 Overflow|
| 0x0028             |USART_RX   |USART_RX_vect|USART, Rx Complete|
| 0x002A             |ADC        |ADC_vect|ADC Conversion Complete|
| 0x0030             |TWI        |TWI_vect|2-wire Serial Interface|

|     Module      | Description    |MCU pin|Arduino pin|
|-----------------|----------------|-------|-----------|
|Timer/Counter0   |       0C0A     |  PD6  |6          |
|                 |      0C0B      |PD5    |5          |
| Timer/Counter1  |       0C1A     |  PB1  |9          |
|                 |      0C1B      |PB2    |10         | 
| Timer/Counter2  |      0C2A      |NA     |NA         | 
|                 |      0C2B      |PB3    |3          |   

