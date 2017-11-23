/*code written for a clap following bot*/
/*relevant header files need to be included*/

volatile boolean flag6 = LOW;
volatile boolean flag7 = LOW;
volatile boolean backward = LOW;
volatile long mi6 = 0;
volatile long mi7 = 0;
volatile long mi9 = 0;
long diff;

volatile int count = 0;
volatile boolean flag = LOW;

volatile boolean left = false;
volatile boolean right = false;
volatile int a = 90;

void setup()
{

  pinMode(10, INPUT_PULLUP);
  attachInterrupt(10, fun, RISING);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(7, pi6, RISING);
  attachInterrupt(8, pi7, RISING);
  attachInterrupt(9, back, RISING);

}

void loop()
{


  if (flag6 || flag7)
  {
    delay(10);
    if (flag6 && flag7)
    {
      diff = mi6 - mi7;
      Serial.println(diff);

      flag6 = flag7 = LOW;
      if (diff > 0)
        left = true;
      else
      { 
        right = true;
        diff = diff * -1;
      }
      if (diff <= 300)
        a = 0;
      else if (diff <= 620)
        a = 45;
      else
        a = 90;
      if (backward && (mi9 < mi6 || mi9 < mi7))
      { 
        a = 180 - a;
        backward = LOW;
      }
      mi6 = mi7 = mi9 = 0;
      while (count <= (a / 4.05))
        turn();
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(14, LOW);
      digitalWrite(15, LOW);
      count = 0;
      left = false;
      right = false;
      delay(500);
      while (count <= 60)
        straight();
      count = 0;
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(14, LOW);
      digitalWrite(15, LOW);

    }
    else
    {
      flag6 = flag7 = LOW;
      backward = LOW;
    }
  }



}

void back()
{ 
  if (!backward)
  { 
    backward = HIGH;
    mi9 = micros();
  }
}

void pi6()
{
  if (!flag6)
  {
    flag6 = HIGH;
    mi6 = micros();

  }
}

void pi7()
{
  if (!flag7)
  {
    flag7 = HIGH;
    mi7 = micros();

  }
}
void fun()
{
  count++;

}

void turn()
{ 
  int b = a / 4;

  if (left && !right)
  { 
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(14, HIGH);
    digitalWrite(15, LOW);
  }
  else if (!left && right)
  { 
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    digitalWrite(15, HIGH);
  }

  else
  { 
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    digitalWrite(15, LOW);
  }
}
void straight()
{ 
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
}


