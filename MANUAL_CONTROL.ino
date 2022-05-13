
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //SETTING UP THE LCD PIN NUMBERS
const int PushB1 = 6; //SETTING UP PUSHBUTTON TO OUTPUT PINS
const int PushB2 = 7;
const int PushB3 = 8;

int LED = 10;  //SELECT THE PIN FOR THE LED
int LDR = A0;  //SETTING THE PIN FOR THE SENSOR

int PV;        // PROCESS VARIABLE
float CO;        //CONTROL OUTPUT VALUE

int ScreenNumber;

int LastState1;
int LastState2;
int LastState3;
int CurrentState1;
int CurrentState2;
int CurrentState3;

void setup()
{
  Serial.begin(9600);             //SETTTING UP THE SPEED OF THE SERIAL COMMUNICATION
  lcd.begin(16, 2);               //SETTING UP THE SIZE OF THE LCD SCREEN
  pinMode(PushB1, INPUT_PULLUP);
  pinMode(PushB2, INPUT_PULLUP);
  pinMode(PushB3, INPUT_PULLUP);
  pinMode(LED, OUTPUT);           //declare the led pin as an output
}

void loop() {
  analogWrite(LED, CO);
  PV = analogRead(LDR);

  /*PUSH BUTTON 1, ADDING SETTINGS*/
  LastState1 = CurrentState1;
  CurrentState1 = digitalRead(PushB1);
  if (LastState1 == 1 && CurrentState1 == 0)
  {
    if (ScreenNumber == 0)
    {
      CO = CO + 1;
    }
  }

  /*PUSH BUTTON 2, MINUS SETTINGS*/
  LastState2 = CurrentState2;
  CurrentState2 = digitalRead(PushB2);
  if (LastState2 == 1 && CurrentState2 == 0)
  {
    if (ScreenNumber == 0)
    {
      CO = CO - 1;
    }
  }
  /*PUSH BUTTON 3, CHANGE PAGE SETTINGS*/
  LastState3 = CurrentState3;
  CurrentState3 = digitalRead(PushB3);
  if (LastState3 == 1 && CurrentState3 == 0)
  {
    ScreenNumber = ScreenNumber + 1;
    if (ScreenNumber > 1)
    {
      ScreenNumber = 0;
    }
  }
  switch (ScreenNumber) {
    case 0:
      //SHOWING CO AND PV VALUES ON LCD SCREEN 1
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CO = ");
      lcd.print(CO);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print("PV = ");
      lcd.print(PV);
      lcd.print(" ");
      delay(100);
      break;
    case 1:
      //SHOWING PV AND PV VALUES ON LCD SCREEN 1
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("PV = ");
      lcd.print(PV);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("PV = ");
      lcd.print(PV);
      lcd.print(" ");
      delay(100);
    default:
      break;
  }
  //PRINTING THESE VALUES TO SERIAL MONITOR
  Serial.print("PV = ");
  Serial.print(PV);
  Serial.print("\t CO = ");
  Serial.print(CO);
  Serial.println();
}
