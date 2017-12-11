int TRUE = 1;
int FALSE = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  Serial.println("Hello!");
}

void loop()
{
  char c;
 
  if(Serial.available() == TRUE)
  {
    c = Serial.read();
    Serial.print("You just said: ' ");
    Serial.print(c);
    Serial.println(" '");
  }
}

