
long x=0;
long y=0;
long z=0;

void setup()
{  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  analogReference(EXTERNAL);
  Serial.begin(115200);
}

void loop()
{
    
  for(int i=0;i<100;i++)
  { 
     x=analogRead(A0)+x;
     y=analogRead(A1)+y;
     z=analogRead(A2)+z;
  }
    
  x=x/100;
  y=y/100;
  z=z/100;
      
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(z);
  Serial.print(" ");
  Serial.println();
  Serial.println();
  delay(100);  
}

  
