#include <avr/io.h>
#include <util/delay.h>

unsigned char S[9];
const unsigned char BLACK=0;
const unsigned char WHITE=1;
unsigned char F=0;
unsigned char J=0;
unsigned char R=0;
unsigned char L=0;


unsigned char turns[]={3,1,3,2,1,1,2,3,2,3};//B and D
//unsigned char turns[]={3,1,3,2,3,1,2,1,1,2,2};//B and C
//unsigned char turns[]={3,1,3,2,3,1,2,1,1,2,2};
unsigned char Tmax=10;

/*void timer_init()
{

    TCCR1A=0xA1;
    TCCR1B=0x0A;
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;


}*/
void ports_init()
{

    DDRB=0x00;
    PORTB=0x00;
    DDRD=0xFE;
    PORTD=0x00;

}

void readsen()
{
    int k=0;
    for(k=0;k<8;k++)
    {
        S[8-k]=PINB&(1<<k);
        if(S[8-k]!=0)
            S[8-k]=1;

    }
    S[0]=PIND&(0x01);


}

void front()
{
    PORTD=PORTD&0xCF;

    PORTD=PORTD&0x3F;
    PORTD=PORTD|0x80;
    PORTD=PORTD&0xF9;
    PORTD=PORTD|0x02;

    PORTD=PORTD|0x30;

}
void right()
{
    PORTD=PORTD&0xCF;

    PORTD=PORTD&0x3F;
    PORTD=PORTD|0x40;
    PORTD=PORTD&0xF9;
    PORTD=PORTD|0x02;

    PORTD=PORTD|0x30;


}
void sright()
{
    PORTD=PORTD&0xCF;

    PORTD=PORTD&0x3F;
    PORTD=PORTD&0xF9;
    PORTD=PORTD|0x02;

    PORTD=PORTD|0x30;


}
void left()
{
    PORTD=PORTD&0xCF;

    PORTD=PORTD&0x3F;
    PORTD=PORTD|0x80;
    PORTD=PORTD&0xF9;
    PORTD=PORTD|0x04;

    PORTD=PORTD|0x30;

}
void sleft()
{
    PORTD=PORTD&0xCF;

    PORTD=PORTD&0x3F;
    PORTD=PORTD|0x80;
    PORTD=PORTD&0xF9;

    PORTD=PORTD|0x30;

}

void stop()
{

    PORTD=PORTD&0xCF;

}

void turnleft90()
{

    readsen();
    while((S[8]==BLACK)||(S[7]==BLACK)||(S[6]==BLACK)||(S[5]==BLACK)||(S[4]==BLACK))
    {
        left();
        readsen();
    }

    unsigned int lp=0;
    for(lp=0;lp<1000;lp++)
    {readsen();
    F=(S[1]==WHITE)&&(S[7]==WHITE);
    R=(S[1]==BLACK)&&(S[7]==WHITE);
    L=(S[1]==WHITE)&&(S[7]==BLACK);
    if(F)
        front();
    if(R)
        sright();
    if(L)
        sleft();
    _delay_ms(1);
    }
    stop();

}
void turnright90()
{

    readsen();
    while((S[0]==BLACK)||(S[1]==BLACK)||(S[2]==BLACK)||(S[3]==BLACK)||(S[4]==BLACK))
    {
        right();
        readsen();
    }
    unsigned int lp=0;
    for(lp=0;lp<1000;lp++)
    {readsen();
    F=(S[1]==WHITE)&&(S[7]==WHITE);
    R=(S[1]==BLACK)&&(S[7]==WHITE);
    L=(S[1]==WHITE)&&(S[7]==BLACK);
    if(F)
        front();
    if(R)
        sright();
    if(L)
        sleft();
    _delay_ms(1);
    }

    stop();
}
void forwardT()
{
    readsen();
    while(S[0]==BLACK || S[8]==BLACK)
    {
        front();
        readsen();
    }
    stop();
}



int main(void)
{

    int T=0;
    ports_init();
    //timer_init();
    while(1)
    {
        readsen();

       J=((S[0]==BLACK)&&(S[1]==BLACK)&&(S[2]==BLACK)&&(S[3]==BLACK)&&(S[4]==BLACK)&&(S[8]==WHITE)) || ((S[8]==BLACK)&&(S[7]==BLACK)&&(S[6]==BLACK)&&(S[5]==BLACK)&&(S[4]==BLACK)&&(S[0]==WHITE));
       if(J)
        {
            if(T<Tmax)
            {   switch(turns[T])
                {
                    case 1:turnleft90();
                           break;
                    case 2:turnright90();
                           break;
                    case 3:forwardT();
                           break;
                    default:break;
                }
                T++;
            }
        }
        readsen();
        F=(S[1]==WHITE)&&(S[7]==WHITE);
        R=(S[1]==BLACK)&&(S[7]==WHITE);
        L=(S[1]==WHITE)&&(S[7]==BLACK);

        if(F)
            front();
        if(R)
            sright();
        if(L)
            sleft();

    }

    return 0;
}
