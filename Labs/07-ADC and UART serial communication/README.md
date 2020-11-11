## Preparation tasks (done before the lab at home)

Use schematic of the [LCD keypad shield](../../Docs/arduino_shield.pdf) and find out the connection of five push buttons: Select, Left, Up, Down, and Right.

&nbsp;

&nbsp;

![](images/butt.png)

&nbsp;



According to the connection, calculate the voltage value on pin PC0[A0] if one button is pressed at a time. In this case, the voltage on the pin is given by the [voltage divider](https://www.allaboutcircuits.com/tools/voltage-divider-calculator/), where resistors R3, R4, R5 and R6 are applied successively.

![Equation: Voltage divider](images/eq_divider1.png)

![Equation: Voltage divider](images/eq_divider2.png)

&nbsp;

![Equation: Voltage divider](images/eq_rest.png)


Calculate the ADC values for these voltages according to the following equation if reference is Vref=5V and number of bits for analog to digital conversion is n=10.


   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** |
   | :-: | :-: | :-: | :-: |
   | Right  | 0&nbsp;V | 0 |  |
   | Up     | 0.495&nbsp;V | 101 |  |
   | Down   |  1.202&nbsp;V| 246 |  |
   | Left   |  1.97&nbsp;V | 403 |  |
   | Select |  3.18&nbsp;V | 650 |  |
   | none   |  5&nbsp;V    | 1023|  |
   
   | **Operation** | **Register(s)** | **Bit(s)** | **Description** |
   | :-: | :-- | :-- | :-- |
   | Voltage reference | ADMUX | REFS1:0 | 01: AVcc voltage reference, 5V |
   | Input channel | ADMUX | MUX3:0 | 0000: ADC0, 0001: ADC1, ... |
   | ADC enable | ADCSRA | ADEN | 1 Enables ADC, 0 turn it off|
   | Start conversion | ADCSRA | ADSC | 1 Enables conversion.  |
   | ADC interrupt enable | ADCSRA | ADIE | 1 Enables interrupt |
   | ADC clock prescaler | ADCSRA | ADPS2:0 | 000: Division factor 2, 001: 2, 010: 4, ...|
   | ADC result | ADLAR | ADCH, ADCL | ADCH(9:2) ADCL(1:0) ADC results |
   
   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `uart_init` | `UART_BAUD_SELECT(9600, F_CPU)` | Initialize UART to 8N1 and set baudrate to 9600&nbsp;Bd | `uart_init(UART_BAUD_SELECT(9600, F_CPU));` |
   | `uart_getc` | `void`| Get received byte from ringbuffer. | `unsigned int uart_getc (void)`|
   | `uart_putc` | `unsigned char data` | Put byte to ringbuffer for transmitting via UART. | `void uart_putc(unsigned char data)`|
   | `uart_puts` | `s	string to be transmitted`| Put string to ringbuffer for transmitting via UART.|`void uart_puts(const char * s)`|	
