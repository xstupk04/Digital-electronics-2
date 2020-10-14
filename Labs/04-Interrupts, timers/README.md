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
| Timer/Counter0  |Prescaler 8-bit data value; Overflow interrupt enable| | 
| Timer/Counter1  |Prescaler; 16-bit data value; Overflow interrupt enable|TCCR1B; TCNT1H, TCNT1L, TIMSK1 |CS12, CS11, CS10 (000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)TCNT1[15:0], TOIE1 (1: enable, 0: disable)|
| Timer/Counter2  |Prescaler; 8-bit data value; Overflow interrupt enable| |

