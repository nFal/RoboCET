#include <avr/io.h>

int main(void)
{
    DDRB=0x00;
    DDRC=0xFF;
    while(1)
    {
        PORTC=PINB;
    }


    return 0;
}
