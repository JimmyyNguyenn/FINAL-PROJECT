
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int PushB1 = 6;
const int PushB2 = 7;
const int PushB3 = 8;

int LED = 10;
int LDR = A0;

int PV;
int CO;
int SetP = 0;
int Error = 0;
int Hys = 0;

int ScreenNumber;

int LastState1;
int LastState2;
int LastState3;

int CurrentState1;
int CurrentState2;
int CurrentState3;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(PushB1, INPUT_PULLUP);
  pinMode(PushB2, INPUT_PULLUP);
  pinMode(PushB3, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop()
{
  analogWrite(LED, CO);
  PV = analogRead(LDR);
  Error = (SetP - PV);

  /*HYSTERISIS SETTINGS*/
  if (PV <= SetP - Hys)
  {
    CO = 255;
  }
  if (PV >= SetP + Hys)
  {
    CO = 0;
  }

  /*CAPPING Hystorisis TO NOT ALLOW THE USER TO GO UNDER 0*/
  if (Hys <= 0)
  {
    Hys = 0;
  }

  /*CAPPING SETPOINT TO NOT ALLOW THE USER TO GO OVER 1000 AND UNDER 0*/
  if (SetP > 1000)
  {
    SetP = 1000;
  }
  if (SetP < 0)
  {
    SetP = 0;
  }

  /*PUSH BUTTON 1 ADDING SETTINGS*/

  LastState1 = CurrentState1;
  CurrentState1 = digitalRead(PushB1);
  if (LastState1 == 1 && CurrentState1 == 0)
  {
    if (ScreenNumber == 0)
    {
      SetP = SetP + 100;
    }
    if (ScreenNumber == 1)
    {
      Hys = Hys + 5;
    }
  }

  /*PUSH BUTTON 2 SUBTRACTING SETTINGS*/

  LastState2 = CurrentState2;
  CurrentState2 = digitalRead(PushB2);
  if (LastState2 == 1 && CurrentState2 == 0)
  {
    if (ScreenNumber == 0)
    {
      SetP = SetP - 100;
    }
    if (ScreenNumber == 1)
    {
      Hys = Hys - 5;
    }
  }

  /*PUSH BUTTON 3 CHANGE PAGE SETTINGS*/

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

  switch (ScreenNumber)
  {
    case 0:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SP = ");
      lcd.print(SetP);
      lcd.setCursor(0, 1);
      lcd.print("ERROR = ");
      lcd.print(Error);
      break;

    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Hyst = ");
      lcd.print(Hys);
      lcd.setCursor(0, 1);
      lcd.print("PV = ");
      lcd.print(PV);
    default:
      break;
  }
  Serial.print("SP: ");
  Serial.print(SetP);
  Serial.print("\t PV: ");
  Serial.print(PV);
  Serial.print("\t Error: ");
  Serial.print(Error);
  Serial.print("\t HYS: ");
  Serial.print(Hys);
  Serial.println();
}
