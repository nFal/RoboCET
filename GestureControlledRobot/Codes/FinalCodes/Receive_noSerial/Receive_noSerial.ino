#include <Enrf24.h>
#include <string.h>
#include <SPI.h>
int P1_0=9;//CE
int P1_1=10;//CSN
int P1_2=3;//I


Enrf24 radio(P1_0, P1_1, P1_2);
const uint8_t rxaddr[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0x03 };



void setup() {

  analogReference(EXTERNAL);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  radio.begin();  // Defaults 1Mbps, channel 0, max TX power
  radio.setChannel(36);//set a different channel frequency
  radio.setRXaddress((void*)rxaddr);
  pinMode(P1_0, OUTPUT);
  digitalWrite(P1_0, LOW);
  radio.enableRX();

  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  digitalWrite(A0,LOW);//right wheels
  digitalWrite(A1,LOW); 
  digitalWrite(5,LOW);//left wheel
  digitalWrite(6,LOW);

  delay(1500);
}

void loop()
{
  char inbuf[33];
  if (radio.read(inbuf))
  {
    
    if(inbuf[0]=='F')
    {    
     
      digitalWrite(A0,HIGH);//right wheels
      digitalWrite(A1,LOW); 
      digitalWrite(5,HIGH);//left wheel
      digitalWrite(6,LOW);
    }
    else if(inbuf[0]=='R')
    {
         
      digitalWrite(A0,LOW);
      digitalWrite(A1,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
    }
    else if(inbuf[0]=='L')
    {   
      
      digitalWrite(A0,HIGH);
      digitalWrite(A1,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,HIGH);
    }
    else if(inbuf[0]=='B')
    {    
      
      digitalWrite(A0,LOW);//right wheels
      digitalWrite(A1,HIGH); 
      digitalWrite(5,LOW);//left wheel
      digitalWrite(6,HIGH);
    }


    else if(inbuf[0]=='S')
    {  
   
      digitalWrite(A0,HIGH);
      digitalWrite(A1,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
    }
    else if(inbuf[0]=='O')
    {
     
      digitalWrite(A0,HIGH);
      digitalWrite(A1,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
    }
    
  }

}

