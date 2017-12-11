#include <Enrf24.h>
#include <string.h>
#include <SPI.h>
#include <math.h>

Enrf24 radio(9, 10, 2); 
const uint8_t txaddr[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0x0A };


double  x=0;
double  y=0;
double  z=0;

double xangle,yangle,zangle,argx,argy,argz;

double H;
double V;
double D; 

void setup() 
{

  
  
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  radio.begin();  // Defaults 1Mbps, channel 0, max TX power
  radio.setChannel(36);
  radio.setTXaddress((void*)txaddr);

 
  analogReference(EXTERNAL);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  
  
  delay(2000);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  delay(3000);
  
  for(int i=0;i<100;i++)
  { 
    x=analogRead(A0)+x;
    y=analogRead(A1)+y;
    z=analogRead(A2)+z;
  }
  
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);

  x=x/100;
  y=y/100;
  z=z/100;

  H=(x+y)/2;
  V=z;
  D=H-V;
}

void loop() {

  x=y=z=0;
  for(int i=0;i<100;i++)
  { 
    x=analogRead(A0)+x;
    y=analogRead(A1)+y;
    z=analogRead(A2)+z;
  }

  x=x/100;
  y=y/100;
  z=z/100;
  
  argz=z-H;
  argy=y-H;
  argx=x-H;

  if(argz<-D)
    argz=-D;
  else if(argz>D)
    argz=D;
  if(argy<-D)
    argy=-D;
  else if(argy>D)
    argy=D;
  if(argx<-D)
    argx=-D;
  else if(argx>D)
    argx=D;
  

  xangle =57.3*asin(argx/D);
  yangle=-57.3*asin(argy/D);
  zangle=-57.3*asin(argz/D);

  if(xangle>-15 && xangle<15 && yangle>-15 && yangle<15 && zangle>60)
  {  
    radio.print("S");
    radio.flush();
  }
  else if(xangle>-45 && xangle<-10 && yangle>-15 && yangle<15 && zangle>45 && zangle<80)
  { 
    radio.print("R");
    radio.flush();
  }
  else if(xangle>15 && xangle<45 && yangle>-15 && yangle<15 && zangle>45 && zangle<75)
  { 
    radio.print("L");
    radio.flush();
  }
  else if(xangle>-15 && xangle<15 && yangle>-45 && yangle<-10 && zangle>45 && zangle<80)
  { 
    radio.print("F");
    radio.flush();
  }
  else if(xangle>-15 && xangle<15 && yangle>15 && yangle<45 && zangle>45 && zangle<75)
  {  
    radio.print("B");
    radio.flush();
  }
  else
  {
    
    radio.print("O");
    radio.flush();
  }
     
  delay(100);
}


