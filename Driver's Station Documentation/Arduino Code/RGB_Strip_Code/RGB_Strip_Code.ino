int RED = 6;
int GREEN = 5;
int BLUE = 3;
int RED2 = 10;
int GREEN2 = 11;
int BLUE2 = 9;
int fade;
int FADESPEED = 5;
int signal = A1;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(BLUE2, OUTPUT);
  pinMode(signal, INPUT);
}

void loop()
{
  clearLEDs();
  int value = analogRead(signal);
  if(value >= 550 && value <= 580)
    rgbFade();
  else if(value >= 460 && value <= 470)
    redFade();
  else if(value >= 270 && value <= 285)
    blueFade();
  else if(value >= 180 && value <= 195)
    redFlash();
  else if(value >= 85 && value <= 95)
    blueFlash();
  else if(value >= -1 && value <= 5)
    partyMode();
  else if(value >= 1020 && value <= 1030)
    clearLEDs();
}

void rgbFade()
{
  int r, g, b;
  if(fade == 1)
  {
    analogWrite(BLUE, 255);
    analogWrite(BLUE2, 255);
  }
 
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(RED, r);
    analogWrite(RED2, r);
    delay(FADESPEED);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUE, b);
    analogWrite(BLUE2, b);
    delay(FADESPEED);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREEN, g);
    analogWrite(GREEN2, g);
    delay(FADESPEED);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(RED, r);
    analogWrite(RED2, r);
    delay(FADESPEED);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUE, b);
    analogWrite(BLUE2, b);
    delay(FADESPEED);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREEN, g);
    analogWrite(GREEN2, g);
    delay(FADESPEED);
  }
  fade = 1;
}

void redFade()
{
  int r;
  for(r = 0; r < 256; r++)
  {
    analogWrite(RED, r);
    analogWrite(RED2, r);
    delay(FADESPEED);
  }
  for(r = 255; r > -1; r--)
  {
    analogWrite(RED, r);
    analogWrite(RED2, r);
    delay(FADESPEED);
  }
}

void blueFade()
{
  int b;
  for(b = 0; b < 256; b++)
  {
    analogWrite(BLUE, b);
    analogWrite(BLUE2, b);
    delay(FADESPEED);
  }
  for(b = 255; b > -1; b--)
  {
    analogWrite(BLUE, b);
    analogWrite(BLUE2, b);
    delay(FADESPEED);
  }
}

void redFlash()
{
  analogWrite(RED, 255);
  analogWrite(RED2, 255);
  delay(50);
  analogWrite(RED, 0);
  analogWrite(RED2, 0);
  delay(50);
}

void blueFlash()
{
  analogWrite(BLUE, 255);
  analogWrite(BLUE2, 255);
  delay(50);
  analogWrite(BLUE, 0);
  analogWrite(BLUE2, 0);
  delay(50);
}

void partyMode()
{
  int r = random(0,255);
  int g = random(0,255);
  int b = random(0,255);
  analogWrite(RED, r);
  analogWrite(RED2, r);
  analogWrite(GREEN, g);
  analogWrite(GREEN2, g);
  analogWrite(BLUE, b);
  analogWrite(BLUE2, b);
  delay(40);
}

void clearLEDs()
{
  analogWrite(RED, 0);
  analogWrite(RED2, 0);
  analogWrite(GREEN, 0);
  analogWrite(GREEN2, 0);
  analogWrite(BLUE, 0);
  analogWrite(BLUE2, 0);
}
