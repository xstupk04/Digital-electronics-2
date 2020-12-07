# R-2R ladder Digital to Analog Converter (DAC)

## Zadání projektu
Aplikace generátoru analogového signálu využívající 8bitový DAC; několik přednastavených typů signálů; displej; ovládání pomocí klávesnice 4x3; (možnost generování tónu DTMF, Dual-Tone Multiple Frequencies); odesílání zajímavých informací o stavu aplikace na UART.

*Write your text here*


## Popis hardwaru
![Project schedule](https://user-images.githubusercontent.com/60606149/101371108-acd26f00-38aa-11eb-9d29-3d5ed93bbe3b.png)

Projekt postavený na mikrokontóleru Atmega328p z rodiny AVR. K němuž je připojen LCD displej s řadičem HD44780 pro zobrazení typu posílaného signálu a informace ohledně stisknuté klávesnici. Nastavený typ signálu bude možné nastavit pomocí 4x3 keypadu. Pro převod signálu z digitální hodnoty na analogovou bude využit tzv. 8 bitový žebříkový systém odporů na jehož výstup se připojí osciloskop na kterém se zobrazí průběh signálu. Informace o typu signálu, stisku konkrétního tlačítka si bude možné zjistit pomocí UARTu

## Schéma zapojení

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

## Video/Animation

*Write your text here*


## Zdroje
http://www.avr-asm-tutorial.net/avr_en/apps/key_matrix/keypad/resmatrix/resmatrix.html
https://www.electronics-tutorials.ws/combination/r-2r-dac.html

