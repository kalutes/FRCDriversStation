#include "MegaJoy.h" //JOYSTICK LIBRARY

//ARDUINO PINS FOR DIGITAL INPUTS
int button1 = 22;//Bottom right corner: red button
int button2 = 23;//Bottom right corner: white toggle button
int button3 = 24;//Bottom left corner: top green button
int button4 = 25;//Bottom left corner: bottom green button
int button5 = 26;//Bottom left corner: top yellow button
int button6 = 27;//Bottom left corner: bottom yellow button
int button7 = 28;//Bottom left corner: top blue button
int button8 = 29;//Bottom left corner: bottom blue button
int switch1 = 31;//momentary switch
int switch2 = 32;//momentary switch
int switch3 = 34;//momentary switch
int switch4 = 35;//momentary switch
int switch5 = 37;//momentary switch
int switch6 = 38;//momentary switch
//END ARDUINO PINS FOR DIGITAL INPUTS

//ARDUINO PINS FOR ANALOG INPUTS
int rotarySwitch = A0; //GET THE PIN
//END ARDUINO PINS FOR ANALOG INPUTS

//BUTTON ASSIGNMENTS FOR DIGITAL INPUTS
int button1_buttonAssignment = 1;//red button
int button2_buttonAssignment = 2;//white button, toggle button
int button3_buttonAssignment = 3;//top green button
int button4_buttonAssignment = 4;//bottem green button
int button5_buttonAssignment = 5;//top yellow button
int button6_buttonAssignment = 6;//bottem yellow button
int button7_buttonAssignment = 7;//top blue button
int button8_buttonAssignment = 8;//bottem blue button
int switch1_buttonAssignment = 9;//momentary switch
int switch2_buttonAssignment = 10;//momentary switch
int switch3_buttonAssignment = 11;//momentary switch
int switch4_buttonAssignment = 12;//momentary switch
int switch5_buttonAssignment = 34;//momentary switch
int switch6_buttonAssignment = 35;//momentary switch
//END BUTTON ASSIGNMENTS FOR DIGITAL INPUTS

//SEVEN SEGMENT DISPLAY OUTPUT PINS
int sevSignal = 6;
//END SEVEN SEGMENT DISPLAY OUTPUT PINS

//VARIABLES FOR THE SHIFT REGISTRIES
int SER_Pin = 2;   
int RCLK_Pin = 3; 
int SRCLK_Pin = 4;
#define number_of_74hc595s 4 
#define numOfRegisterPins number_of_74hc595s * 8
boolean registers[numOfRegisterPins];
//END VARIABLES FOR THE SHIFT REGISTRIES

int rgbSignal = 5;

//SHIFT REGISTRY PINS FOR LEDS
//Top Right, 1 B - 0
//Top Right, 4 B - 1
//2
//Top Right, 1 R - 3
//Bottom Right Red Button - 4
//White Latching Button - 5
//Green Bottom - 6
//Green Top - 7
//8
//Yellow Top - 9
//Yellow Bottom - 10
//Blue Bottom - 11
//Blue Top - 12
//13
//14
//15
//Side Green - 16
//Side Red - 17
//Driver's Left R - 18
//Driver's Left G - 19
//Driver's Left B - 20
//Driver's Right R - 21
//Driver's Right G - 22
//Driver's Right B - 23
//Top Right, 2 R - 24
//Top Right, 2 G - 25
//Top Right, 2 B - 26
//Top Right, 3 R - 27
//Top Right, 3 G - 28
//Top Right, 3 B - 29
//Top Right, 4 R - 30
//Top Right, 4 G - 31
//END REGISTRY PINS FOR LEDS

//MISCELLANEOUS VARIABLES
int button[] = {22, 23, 24, 25, 26, 27, 28, 29};
int buttonLED[] = {4, 5, 7, 6, 9, 10, 12, 11};
//END MISCELLANEOUS VARIABLES

void setup(){
  setupPins();
  setupMegaJoy();
  clearRegisters();
  writeRegisters();
}

void loop(){
  //DO THE PRETTY LEDS ON THE BUTTONS
  for(int i = 0; i < 8; i++)
  {
    if(digitalRead(button[i]))
    {
      setRegisterPin(buttonLED[i], HIGH);
    }
    else
    {
      setRegisterPin(buttonLED[i], LOW);
    }
  }
  writeRegisters();
  // Always be getting fresh data
  megaJoyControllerData_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void){
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  pinMode(button7, INPUT);
  pinMode(button8, INPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(switch4, INPUT);
  pinMode(switch5, INPUT);
  pinMode(switch6, INPUT);
  digitalWrite(button1, HIGH);
  digitalWrite(button2, HIGH);
  digitalWrite(button3, HIGH);
  digitalWrite(button4, HIGH);
  digitalWrite(button5, HIGH);
  digitalWrite(button6, HIGH);
  digitalWrite(button7, HIGH);
  digitalWrite(button8, HIGH);
  digitalWrite(switch1, HIGH);
  digitalWrite(switch2, HIGH);
  digitalWrite(switch3, HIGH);
  digitalWrite(switch4, HIGH);
  digitalWrite(switch5, HIGH);
  digitalWrite(switch6, HIGH);
  pinMode(rotarySwitch, INPUT);
  pinMode(sevSignal, OUTPUT);
  pinMode(rgbSignal, OUTPUT);
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
}

megaJoyControllerData_t getControllerData(void){
  //GET BLANK DATA SPACE FOR BUTTON STATES
  megaJoyControllerData_t controllerData = getBlankDataForMegaController();

  //READ BUTTONS AND PUT DATA IN THE BUTTON ARRAY
  controllerData.buttonArray[(button1_buttonAssignment - 2) / 8] |= (digitalRead(button1)) << ((button1_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(button2_buttonAssignment - 2) / 8] |= (digitalRead(button2)) << ((button2_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(button3_buttonAssignment - 2) / 8] |= (digitalRead(button3)) << ((button3_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(button4_buttonAssignment - 2) / 8] |= (digitalRead(button4)) << ((button4_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(button5_buttonAssignment - 2) / 8] |= (digitalRead(button5)) << ((button5_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(button6_buttonAssignment - 2) / 8] |= (digitalRead(button6)) << ((button6_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(button7_buttonAssignment - 2) / 8] |= (digitalRead(button7)) << ((button7_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(button8_buttonAssignment - 2) / 8] |= (digitalRead(button8)) << ((button8_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(switch1_buttonAssignment - 2) / 8] |= (digitalRead(switch1)) << ((switch1_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(switch2_buttonAssignment - 2) / 8] |= (digitalRead(switch2)) << ((switch2_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(switch3_buttonAssignment - 2) / 8] |= (digitalRead(switch3)) << ((switch3_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(switch4_buttonAssignment - 2) / 8] |= (digitalRead(switch4)) << ((switch4_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(switch5_buttonAssignment - 2) / 8] |= (digitalRead(switch5)) << ((switch5_buttonAssignment - 2) % 8);
  controllerData.buttonArray[(switch6_buttonAssignment - 2) / 8] |= (digitalRead(switch6)) << ((switch6_buttonAssignment - 2) % 8);
  //RETURN THE DATA
  return controllerData;
}

void clearRegisters()
{
  for(int i = numOfRegisterPins - 1; i >=  0; i--)
  {
     registers[i] = LOW;
  }
}

void writeRegisters()
{
  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--)
  {
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, HIGH);
}

void setRegisterPin(int index, int value)
{
  registers[index] = value;
}
