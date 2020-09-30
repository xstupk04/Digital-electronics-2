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

 
|   DDRB    |    PORTB    |     PUD     |   Direction   |internal pull-up resistor|
|-----------|-------------|-------------|---------------|-------------------------|
|     0     |     O       |      X      |     input     |           No            |
|     0     |     1       |      0      |     input     |           yes           |
|     0     |     1       |      1      |     input     |           No            |
|     1     |     0       |      X      |     output    |           No            |
|     1     |     1       |      1      |     output    |           No            |





