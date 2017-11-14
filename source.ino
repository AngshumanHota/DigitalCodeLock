#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>
#include<Servo.h>

Servo myservo;
//int pos=0;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
char password[4] = {NULL};
char pass[4], pass1[4];
int i = 0;
char customKey = 0;
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
char hexaKeys[ROWS][COLS] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {15, 14, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 7}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
void setup()
{
  lcd.begin(16, 2);
  lcd.print("  Electronic ");
  lcd.setCursor(0, 1);
  lcd.print("  Keypad Lock ");
  delay(2000);
  lcd.clear();
  lcd.print("Enter Ur Passkey:");
  lcd.setCursor(0, 1);
  for (int j = 0; j < 4; j++)
  {
    EEPROM.write(j, j + 49);
  }
  for (int j = 0; j < 4; j++)
  {
    pass[j] = EEPROM.read(j);
  }
  myservo.attach(6);
}
void change()
{
  int j = 0;
  lcd.clear();
  lcd.print("UR Current Pass");
  lcd.setCursor(0, 1);
  while (j < 4)
  {
    char key = customKeypad.getKey();
    if (key)
    {
      pass1[j++] = key;
      lcd.print(key);
    }
    key = 0;
  }
  delay(500);

  if ((strncmp(pass1, pass, 4)))
  {
    lcd.clear();
    lcd.print("Wrong Passkey...");
    lcd.setCursor(0, 1);
    lcd.print("Better Luck Again");
    delay(1000);
  }
  else
  {
    j = 0;

    lcd.clear();
    lcd.print("Enter New Passk:");
    lcd.setCursor(0, 1);
    while (j < 4)
    {
      char key = customKeypad.getKey();
      if (key)
      {
        pass[j] = key;
        lcd.print(key);
        EEPROM.write(j, key);
        j++;

      }
    }
    lcd.print("  Done......");
    delay(1000);
  }
  lcd.clear();
  lcd.print("Enter Ur Passk:");
  lcd.setCursor(0, 1);
  customKey = 0;
}


void loop()
{
  customKey = customKeypad.getKey();
  if (customKey == '#')
    change();
  else if (customKey != '#')
  {
    while (i < 4)
    {
      password[i] = customKey;
      lcd.setCursor(0, i);
      lcd.print(customKey);
      i++;
    }
  }
  if (i == 4 && customKey == '*')
  {
    delay(200);
    if ((strncmp(password, pass, 4)) == 0)
    {

      lcd.clear();
      lcd.print("Passkey Accepted");
      delay(2000);
      // for(pos=0;pos<=90;pos++)

      myservo.write(90);

      lcd.setCursor(0, 1);
      lcd.print("#.Change Passkey");
      delay(2000);
      lcd.clear();
      lcd.print("Enter Passkey:");
      lcd.setCursor(0, 1);
      i = 0;
    }

    else
    {
      lcd.clear();
      lcd.print("Access Denied...");
      lcd.setCursor(0, 1);
      lcd.print("#.Change Passkey");
      delay(2000);
      lcd.clear();
      lcd.print("Enter Passkey:");
      lcd.setCursor(0, 1);
      i = 0;
    }
  }
}
