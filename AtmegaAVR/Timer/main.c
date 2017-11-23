#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

ISR(TIMER0_OVF_vect) {
    PORTA=~PORTA;
}



int main(void)
{
    DDRA=0xFF;
    TIMSK=(1<<TOIE0);
    TCNT0=0x00;
    TCCR0 = (1<<CS02) | (1<<CS00);
    sei();
    while(1)
    {}

    return 0;
}


