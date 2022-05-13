
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int PushB1 = 6;
const int PushB2 = 7;
const int PushB3 = 8;

int LED = 10;
int ldr = A0;

int PV = 0;
int CO = 0;
int SetP = 0;
int Error = 0;
float pGain = 0.0;
float iGain = 0.0;

int ScreenNumber;

int LastState1;
int LastState2;
int LastState3;

int CurrentState1;
int CurrentState2;
int CurrentState3;

int Iaction;
int unsigned long previousMillis = 0;
const long interval = 100;
unsigned long currentMillis;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(PushB1, INPUT_PULLUP);
  pinMode(PushB2, INPUT_PULLUP);
  pinMode(PushB3, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}
void loop() {
  analogWrite(LED, CO);
  PV = analogRead(ldr);
  currentMillis = millis();

  /*PI GAIN SETTINGS*/
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    Error = SetP - PV;
    Iaction = (Iaction + Error);
    CO = (pGain * Error) + (iGain * Iaction);

    /*CAPPING CO TO NOT ALLOW THE USER TO GO OVER 255 AND UNDER 0*/
    if (CO >= 255)
    {
      CO = 255;
    }

    if (CO < 0)
    {
      CO = 0;
    }
    /*CAPPING Iaction TO NOT GO OVER 255 AND UNDER 0*/
    if (Iaction >= 255)
    {
      Iaction = 255;
    }

    if (Iaction < 0)
    {
      Iaction = 0;
    }
  }

  /*PUSH BUTTON 1 ADDING*/
  LastState1 = CurrentState1;
  CurrentState1 = digitalRead(PushB1);
  if (LastState1 == 1 && CurrentState1 == 0)
  {
    if (ScreenNumber == 0)
    {
      SetP = SetP + 50;
    }
    if (ScreenNumber == 1)
    {
      pGain = pGain + 0.01;
    }
    if (ScreenNumber == 2)
    {
      iGain = iGain + 0.01;
    }
  }

  /*PUSH BUTTON 2 MINUS*/
  LastState2 = CurrentState2;
  CurrentState2 = digitalRead(PushB2);
  if (LastState2 == 1 && CurrentState2 == 0)
  {
    if (ScreenNumber == 0)
    {
      SetP = SetP - 50;
    }
    if (ScreenNumber == 1)
    {
      pGain = pGain - 0.01;
    }
    if (ScreenNumber == 2)
    {
      iGain = iGain - 0.01;
    }
  }

  /*PUSH BUTTON 3 CHANGE SCREENS*/
  LastState3 = CurrentState3;
  CurrentState3 = digitalRead(PushB3);
  if (LastState3 == 1 && CurrentState3 == 0)
  {
    ScreenNumber = ScreenNumber + 1;
    if (ScreenNumber > 2) {
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
      lcd.print("pGain = ");
      lcd.print(pGain);
      lcd.setCursor(0, 1);
      lcd.print("PV = ");
      lcd.print(PV);
      break;

    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("iGain = ");
      lcd.print(iGain);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("CO = ");
      lcd.print(CO);
      lcd.print(" ");
    default:
      break;
  }
  Serial.print("SP: ");
  Serial.print(SetP);
  Serial.print("\t PV: ");
  Serial.print(PV);
  Serial.print("\t CO = ");
  Serial.print(CO);
  Serial.print("\t Error: ");
  Serial.print(Error);
  Serial.print("\t pGain = ");
  Serial.print(pGain);
  Serial.println();
}
