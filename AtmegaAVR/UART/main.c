#include <avr/io.h>

void init_UART(unsigned int ubrr)
{
    UBRRH=(unsigned char)(ubrr>>8);
    UBRRL=(unsigned char)ubrr;
    UCSRB=(1<<RXEN)|(1<<TXEN);
    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

void trans_UART(unsigned char data)
{
    while(!(UCSRA & (1<<UDRE)))
    {}
    UDR=data;
}

unsigned char recev_UART(void)
{
    while(!(UCSRA & (1<<RXC)))
    {}
    return UDR;
}


int main(void)
{

    unsigned int baud=0x000C;
    init_UART(baud);

    while(1)
    {   unsigned char i='A';
        for(i='A';i<'Z';i++)
        {
            trans_UART(i);
        }
    }

    return 0;
}
