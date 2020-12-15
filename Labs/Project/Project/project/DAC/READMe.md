# R-2R ladder Digital to Analog Converter (DAC)

## Zadání projektu
Aplikace generátoru analogového signálu využívající 8bitový DAC; několik přednastavených typů signálů; displej; ovládání pomocí klávesnice 4x3; (možnost generování tónu DTMF, Dual-Tone Multiple Frequencies); odesílání zajímavých informací o stavu aplikace na UART.



## Popis hardwaru
![Project schedule](https://github.com/libormatejek/Digital-electronics-2/blob/master/Labs/project/Images/schema1.png?raw=true)

Projekt postavený na mikrokontóleru Atmega328p z rodiny AVR. K němuž je připojen LCD displej s řadičem HD44780 pro zobrazení typu posílaného signálu a informace ohledně stisknuté klávesnici. Nastavený typ signálu bude možné nastavit pomocí 4x3 keypadu. Pro převod signálu z digitální hodnoty na analogovou bude využit 8 bitový tzv. žebříkový systém odporů na jehož výstup se připojí osciloskop na kterém se zobrazí průběh signálu. Hodnota stisku konkrétního tlačítka je vysíláno pomocí UARTu

### Tabulka zapojení

   | **Zařízení** | **Port proceosru** | **Popis** |
   | :-: | :-: | :-: |
   | R-2R převodník         | PC[3:6], PD[0-3] | Připojení R2R DAC převodníku |
   |Analogový výstup keypadu|  C0              | AD převodník pro klávesnici  |
   | RS (disp)              |  PB0             | Výběr mezi instrukčním registrem (RS = 0) a datovým registrem (RS = 1) |
   | R/W (disp)             |  GND             | Read/write (Read=1, write=0) |
   | E (disp)               |  PB1             | Enable |
   |D[7:4] (disp)           |  PD[7:4]         | Obousměrná datová sběrnice, přenos dat se provádí jednou, přes D0 až D7, v případě, že délka dat je 8 bitů. Pokud pouze 4 bitová, jedná se o D4 až D7|

## R-2R rezistorová síť 
![Project schedule](https://user-images.githubusercontent.com/60606149/101371125-afcd5f80-38aa-11eb-9f3b-5953b6983c53.png)

Jak ze schématu plyne jedná síť rezistorů pomocí, které jde jednoduše převést digitální hodnotu signálu na ekvivalentní analogovou výstup. Rozlišení takovéto sítě je závislé na počtu tzv. „žebříků“ (čím více žebříků, tím vyšší rozlišení). Síť rezistorů není nic jiného než propojení několika odporových děličů napětí za sebou a jejich výstup závisí na přiveděné digitální hodnotě z vstupu (v našem případě generované hodnotě z mikroprocesoru). 

## 4x3 keypad
![Project schedule](https://user-images.githubusercontent.com/60606149/101371116-ae9c3280-38aa-11eb-82f0-7d82470d5ae3.png)

Pomocí využité klávesnice lze přednastavit 12 analogových hodnot. Výstup klávesnice je přiveden na port C0 mikroprocesoru. Tento port má funkci AD převodníku, kdy v rámci programu rozlišuje stisknuté tlačítko. Každá klávesa kombinuje specifické rezistory s děličem napětí, a tak vytváří specifické napětí na výstupu. S tímto napětím lze určit, zda je aktuálně stisknut jakýkoli a který konkrétní klíč. 

## Popis programu
Program je postaven na knihovnách ze cvičení- tedy timer.h, která zjednodušuje práci s časovači,gpio.h, jež umí ovládat i/o, lcd.h, která je převzata od Petera Fleuryho
a umožňující snadnou práci s lcd displejem, uart.h, která je převzata od stejného autora, jako knihovna lcd.h. Navíc využíváme knihovnu math.h pro zpříštupnění matematických operací.
DAC převodník je založen na stále se inkrementující hodnotě i pomocí interrupt rutiny, která je zpracovávána ve funkci fce. Tato funkce obsahuje 3 různé typy matematických výpočtů aktuálního vzorku pro nastavený průběh.
	
```C
//function for generating signals values
unsigned int fce(unsigned int i ) {
	
	if(fceType==0) 
		return (unsigned int)(255*(1 + sin(i * 6.28 * Tvz/T))/2); //returns sin values
	else if(fceType==1)
		return (unsigned int)(255 * fmod(i*Tvz,T)/T);             //returns saw values
	else if(fceType==2) {					            
		int j = (int)(i*Tvz/(T/2));                               //returns triangle values
		float a = 2*fmod(i*Tvz,T)/T; 
		a = 255*(j%2==0? a : 1 - a);   
		return (unsigned int)a;	
	}
	else if(fceType==10)                                              //stops signal generating
	return (uint8_t)(0);
}
```

Hodnota je dále filtrována funkcí setByte, která zjišťuje, zda je bit na určité pozici aktivní, nebo ne. Pokud zjistí aktivitu, vydá instrukci pro aktivaci výstupu.
```C
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
```


ADC interrupt, který je aktivován interruptem timeru 1, hlídá hondnotu ADC vstupu z keypadu a nastavuje typy průběhů + DTMF děličku frekvence a dobu příslučného tónu. 
DTMF je realizováno pomoci funkce GPIO_toggle(), která je aktivována pokaždé, kdy timer2 "dopočítá" do určená hodnoty DTMF hodnoty nastavené keypadem. Zároveň je regulovaná doba znění a to pomocí hodnoty duration. Togglování je totiž zastaveno v moment, kdy je napočítáno do právě hodnoty duration.

```C
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
```



## Video/Animation
 [Link for video simulation of signals](https://drive.google.com/file/d/1RberoMPwAhWS-ku1HDwhC8BtC2yYz-i1/view?usp=sharing)  
 [Link for video simulation of DTMF](https://drive.google.com/file/d/11BdKEo6V2hNEbUpJ4fsnwTo4pGqHie2j/view?usp=sharing)

## Zdroje
1. http://www.avr-asm-tutorial.net/avr_en/apps/key_matrix/keypad/resmatrix/resmatrix.html
2. https://www.electronics-tutorials.ws/combination/r-2r-dac.html
3. http://www.peterfleury.epizy.com
