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



|   Port    |     Pin     |          PUD            |
|-----------|-------------|-------------------------|
|     A     |     X       |      X                  |
|     B     |     0       |      0                  |
|           |     1       |      1                  |
|           |     2       |      X                  |
|           |     3       |      1                  |
|           |     4       |      1                  |   
|           |     5       |      1                  | 
|           |     6       |      1                  |
|           |     7       |      1                  | 



