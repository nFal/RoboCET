#include <avr/io.h>
#include<avr/delay.h>

int main(void)
{

    DDRB=0xFF;
    TCCR0=0b01101001;
    OCR0=128;
    while(1)
    {
        OCR0=50;
        _delay_ms(500);
        OCR0=250;
        _delay_ms(500);
    }
    return 0;
}
