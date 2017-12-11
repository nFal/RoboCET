#include <math.h>

double  x=0;
double  y=0;
double  z=0;
double xangle,yangle,zangle,argy,argx,argz;
double H;
double V;
double D; 

void setup()
{  
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  Serial.println("Hold still measurement starts in 2s ");
  delay(2000);
  Serial.println("Measuring... ");
  delay(1000);
  for(int i=0;i<100;i++)
  { 
    x=analogRead(A0)+x;
    y=analogRead(A1)+y;
    z=analogRead(A2)+z;
  }

  x=x/100;
  y=y/100;
  z=z/100;

  H=(x+y)/2;
  V=z;
  D=V-H;
  

}

void loop()
{

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

  xangle=57.3*asin(argx/D);
  yangle=57.3*asin(argy/D);
  zangle=57.3*asin(argz/D);

  if(xangle>-15 && xangle<15 && yangle>-15 && yangle<15 && zangle>60)
    Serial.print("Stop");
  else if(xangle>-45 && xangle<-10 && yangle>-15 && yangle<15 && zangle>45 && zangle<80)
    Serial.print("Right");
  else if(xangle>15 && xangle<45 && yangle>-15 && yangle<15 && zangle>45 && zangle<75)
    Serial.print("Left");
  else if(xangle>-15 && xangle<15 && yangle>-45 && yangle<-10 && zangle>45 && zangle<80)
    Serial.print("Front");
  else if(xangle>-15 && xangle<15 && yangle>15 && yangle<45 && zangle>45 && zangle<75)
    Serial.print("Back");
  else
    Serial.print("Out of Range ");

  Serial.print(" xangle ");
  Serial.print(xangle);
  Serial.print(" yangle ");
  Serial.print(yangle);
  Serial.print(" zangle ");
  Serial.print(zangle);

  Serial.println();
  Serial.println();

  delay(200);      
}




