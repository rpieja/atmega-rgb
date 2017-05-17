#define FOSC 800000  // Clock Speed
#define BAUD 9600
#define MYUBRR 51
#define F_CPU 800000UL
#include <avr/io.h>
#include <util/delay.h>

void USART_Init(unsigned int ubrr);
void USART_Flush(void);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive(void);

int main(void)
{
    USART_Init(MYUBRR);
    unsigned char mp = USART_Receive();
    //uint8_t max_percentage = (uint8_t)mp;
    //int max_percentage = 100;

    DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3);
    
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

    TCCR1A |= /*(1 << WGM11) |*/ (1 << WGM10);
    
    TCCR1B |= (1 << CS11);


    TCCR2 |= (1 << WGM20) | (1 << COM21)  | (1 << CS21);


    while (1)
    {


        OCR1A = USART_Receive();
        USART_Transmit('x');
        //OCR1B = USART_Receive();

        //OCR2 = USART_Receive();

        /*for(int percentage=max_percentage; percentage>0;--percentage)
        {
          
          _delay_ms(10);
        }
        for(int percentage=1; percentage<max_percentage;++percentage)
        {
          OCR1A = ((0x03FF/100)*percentage);
          _delay_ms(10);}
        }*/
      }
}

void USART_Init( unsigned int ubrr)
{
  /* Set baud rate */
  UBRRH = (unsigned char)(ubrr>>8);
  UBRRL = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSRB = (1<<RXEN)|(1<<TXEN);
  /* Set frame format: 8data, 2stop bit */
  UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}
void USART_Flush( void )
{
  unsigned char dummy;
  while ( UCSRA & (1<<RXC) ) dummy = UDR;
}
unsigned char USART_Receive( void )
{
  /* Wait for data to be received */
  while ( !(UCSRA & (1<<RXC)) );
  /* Get and return received data from buffer */
  return UDR;
}
void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSRA & (1<<UDRE)) )
;
/* Put data into buffer, sends the data */
UDR = data;
}