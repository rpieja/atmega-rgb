/*
#define F_CPU 800000UL
B#include <avr/io.h>
#include <util/delay.h>
//Define functions
//======================
void ioinit(void);
void led_on(void);
void led_off(void);
//======================
//int main (void)
//{
 //  ioinit(); //Setup IO pins and defaults
//   while (1)
//   {
//     _delay_ms(10000);
//     led_on();
//     led_off();
//  }
//}

void ioinit (void)
{
   DDRB = (1<<DDB1);
   PORTB = 0b00000000;
}

void led_on(void)
{
   PORTB |= _BV(PB1);
}

void led_off(void)
{
   PORTB &= ~_BV(PB1);
}
*/