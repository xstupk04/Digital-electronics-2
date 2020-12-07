## Preparation tasks (done before the lab at home)

![Ledky](https://user-images.githubusercontent.com/60606149/99425832-af712280-2903-11eb-95d5-b65c775a7471.png) 

Use schematic of the and find out the connection of five push buttons: Select, Left, Up, Down, and Right.


Calculate the ADC values for these voltages according to the following equation if reference is Vref=5V and number of bits for analog to digital conversion is n=10.


   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** |
   | :-: | :-: | :-: | :-: |
   | Right  | 0&nbsp;V | 0 | 0 |
   | Up     | 0.495&nbsp;V | 101 | 101 |
   | Down   |  1.202&nbsp;V| 246 | 245 |
   | Left   |  1.97&nbsp;V | 403 | 402 |
   | Select |  3.18&nbsp;V | 650 | 650 |
   | none   |  5&nbsp;V    | 1023| 1022 |
   
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
