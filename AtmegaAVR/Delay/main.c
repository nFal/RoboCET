#include <avr/io.h>
#include <util/delay.h>
int main(void)
{

    DDRB=0xFF;
    while(1)
    {
        PORTB=0xFF;
        _delay_ms(250);
        PORTB=0x00;
        _delay_ms(250);

    }
    return 0;
}
