# Home preparation

Consider an n-bit number that we increment based on the clock signal. If we reach its maximum value and try to increase it, the value will be reset. We call this state an overflow. 
Calculate the overflow times for three Timer/Counter modules that contain ATmega328P if CPU clock frequency is 16 MHz. Complete the following table for given prescaler values. Note that, Timer/Counter2 is able to set 7 prescaler values, including 32 and 128.
   

|     Module      | Number of bits |   1  |  8  | 32 |  64 | 128 |  256 | 1024 |
|-----------------|----------------|------|-----|----|-----|-----|------|------|
| Timer/Counter0  |       8        |  16u |128u | -- |1024u| - - |4096u |16384u|
| Timer/Counter1  |      16        |4.096m|32.8m| -- |262m | - - |1.0486|4.194 |
| Timer/Counter2  |       8        |  16u |128u |512u|1024u|2048u|4096u |16384u|  
