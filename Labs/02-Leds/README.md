# PART 1 - Preparation for labs

| LED Color | Supply Voltage | LED current |  LED voltage  | Resistor value |
|-----------|----------------|-------------|---------------|----------------|
|    RED    |       5V       |    20 mA    |      1,7 V    |     660        |
|    Blue   |       5V       |    20 mA    |       3V      |     100        |


# PART 2 - Active low and active high LEDs

|   PORTB   |   Description  |
|-----------|----------------|
|    0      |Output low value| 
|    1      |Output low value|


|   DDRB    |   Description  |
|-----------|----------------|
|    0      |    Input pin   | 
|    1      |   Output pin   |

 
|   DDRB    |    PORTB    |     PUD     |   Direction   |internal pull-up resistor|            Descriptiion                 |
|-----------|-------------|-------------|---------------|-------------------------|-----------------------------------------|
|     0     |     O       |      X      |     input     |           No            |        Tri-state, high-impedance        |
|     0     |     1       |      0      |     input     |           yes           |PBx will source current if ext.pulled low|
|     0     |     1       |      1      |     input     |           No            |        Tri-state, high-impedance        |
|     1     |     0       |      X      |     output    |           No            |            Output low (sink)            |
|     1     |     1       |      1      |     output    |           No            |           Output High (source)          | 



|   Port    |     Pin     |                Input/output usage                |
|-----------|-------------|--------------------------------------------------|
|     A     |     X       |Microcontroller ATmega328P does not contain port A|
|     B     |     0       |              Yes (Arduino pin 8)                 |
|           |     1       |              Yes (Arduino pin -9)                |
|           |     2       |              Yes (Arduino pin -10)               |
|           |     3       |              Yes (Arduino pin -11)               |
|           |     4       |             	Yes (Arduino pin 12)                |   
|           |     5       |              Yes (Arduino pin 13)                | 
|           |     6       |                      NO                          |
|           |     7       |                      NO                          | 
|     C     |     0       |              Yes (Arduino pin A0)                |
|           |     1       |              Yes (Arduino pin A1)                |
|           |     2       |              Yes (Arduino pin A2)                |
|           |     3       |              Yes (Arduino pin A3)                |
|           |     4       |             	Yes (Arduino pin A4)                |   
|           |     5       |              Yes (Arduino pin A5)                | 
|           |     6       |                      NO                          |
|           |     7       |                  Doesnt have                     | 
|     D     |     0       |            Yes (Arduino pin RX<-0)               |
|           |     1       |            Yes (Arduino pin TX->1)               |
|           |     2       |              Yes (Arduino pin 2)                 |
|           |     3       |              Yes (Arduino pin -3)                |
|           |     4       |             	Yes (Arduino pin 4)                 |   
|           |     5       |              Yes (Arduino pin -5)                | 
|           |     6       |              Yes (Arduino pin -6)                |
|           |     7       |              Yes (Arduino pin 7)                 | 




