int TRUE = 1;
int FALSE = 0;

void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  char c;
  if(Serial.available() == TRUE)
  {
    c = Serial.read();
    
    if(c == 'Y')
    digitalWrite(13,HIGH);
    else if(c == 'N')
    digitalWrite(13,LOW);
  }
}

