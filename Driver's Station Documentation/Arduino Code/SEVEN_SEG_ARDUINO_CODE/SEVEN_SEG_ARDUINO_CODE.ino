#define signal A0
//SEVEN SEGMENT DISPLAY OUTPUT PINS
  //ON THE DISPLAY PCP THE LOWER LEFT PIN IS 1 AND THE UPPER RIGHT PIN IS 12
  //   A   
  //F     B
  //   G   
  //E     C
  //   D   P
int a = 8; // display pin 11
int b = 9; // display pin 7
int c = 6; // display pin 4
int d = 4; // display pin 2
int e = 3; // display pin 1
int f = 2; // display pin 10
int g = 5; // display pin 5
int p = 7; // display pin 3

int digit4 = 13; // display pin 6
int digit3 = 12; // display pin 8
int digit2 = 11; // display pin 9
int digit1 = 10; // display pin 12
//END SEVEN SEGMENT DISPLAY OUTPUT PINS

int displayNum;

void setup()
{
  //mySerial.begin(4800);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(p, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(signal, INPUT);
  digitalWrite(signal, HIGH);
}

void loop()
{
  int time;
  while(digitalRead(signal))
  {
  }
  time = millis();
  while(!digitalRead(signal))
  {
  }
  time = millis() - time;
  if(time < 5)
  {
    writeSevenSeg(461);
  }
  if(time > 5)
  {
    partyMode();
  }
}

void writeSevenSeg(int i)
{
  int thousands = i / 1000;
  int hundreds = (i - (1000 * thousands)) / 100;
  int tens = (i - (1000 * thousands) - (100 * hundreds)) / 10;
  int ones = (i - (1000 * thousands) - (100 * hundreds) - (10 * tens));
  int digits[] = {thousands, hundreds, tens, ones};
  for(int i = 0; i<4; i++)
  {
    delay(4);
    switch(i)
    {
      case 0: 
        digitalWrite(digit1, LOW);
        digitalWrite(digit2, HIGH);
        digitalWrite(digit3, HIGH); 
        digitalWrite(digit4, HIGH); 
        break;
      case 1: 
        digitalWrite(digit1, HIGH);
        digitalWrite(digit2, LOW);
        digitalWrite(digit3, HIGH);
        digitalWrite(digit4, HIGH);   
        break;
      case 2: 
        digitalWrite(digit1, HIGH);
        digitalWrite(digit2, HIGH);
        digitalWrite(digit3, LOW); 
        digitalWrite(digit4, HIGH);
        break;
      case 3:
        digitalWrite(digit1, HIGH);
        digitalWrite(digit2, HIGH);
        digitalWrite(digit3, HIGH); 
        digitalWrite(digit4, LOW);
        break;
    }
    switch(digits[i])
    {
      case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    }
  }
}

void clearSevenSeg()
{
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(p, LOW);
}

void partyMode()
{
  int ptime = millis();
  while(millis() - ptime < 300)
  {
    writeSevenSeg(1000);
  }
  while(millis() - ptime < 600)
  {
    writeSevenSeg(6100);
  }
  while(millis() - ptime < 900)
  {
    writeSevenSeg(4610);
  }
  while(millis() - ptime < 1200)
  {
    writeSevenSeg(461);
  }
  while(millis() - ptime < 1500)
  {
    writeSevenSeg(46);
  }
  while(millis() - ptime < 1800)
  {
    writeSevenSeg(4);
  }
}
