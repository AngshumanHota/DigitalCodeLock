//******************************************
//			  Designed and developed 
//				      	 by
//			Tamojit Saha, Angshuman Hota
//******************************************

//******************************************
//				    PROJECT NAME:
//	User defined password protected digital
//	lock based on Arduino Uno(ATmega328P-PU)
//******************************************
#include <Keypad.h>
#include<Servo.h>
#include<LiquidCrystal.h>

#include<EEPROM.h>

LiquidCrystal liquid_crystal_display(12, 11, 9, 8, 7, 6);
Servo lock;
char password[4];

char initial_password[4],new_password[4];

int i=0;

char key_lock = 0;
char key_pressed=0;

const byte rows = 4; 

const byte columns = 3; 

char hexaKeys[rows][columns] = {

{'1','2','3'},

{'4','5','6'},

{'7','8','9'},

{'*','0','#'}

};

byte row_pins[rows] = {2, 3, 4, 5};

byte column_pins[columns] = {A0,A1,A2};

Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);




void setup()

{
lock.attach(10);  
liquid_crystal_display.begin(16,2);
liquid_crystal_display.setCursor(0,0);
liquid_crystal_display.print(" Electronic Lock ");

delay(2000);
liquid_crystal_display.clear();
liquid_crystal_display.print("Enter Password:");
liquid_crystal_display.setCursor(0,1);
initialpassword();

lock.write(0);
}




void loop()
{
  
  key_pressed = keypad_key.getKey();
  
  if(key_pressed=='#')
    {change();}

  if (key_pressed == '1' ||key_pressed == '2' || 
  key_pressed == '3' || key_pressed == '4' ||
  key_pressed == '5' || key_pressed == '6'||
  key_pressed == '7' || key_pressed == '8'||
  key_pressed == '9' || key_pressed == '0')

  {
    password[i++]=key_pressed;

    liquid_crystal_display.print(key_pressed);

  }

  if(i==4)

  {

    delay(200);

    for(int j=0;j<4;j++)

      initial_password[j]=EEPROM.read(j);

    if(!(strncmp(password, initial_password,4)))

    {
      int isOpen = 0;
      liquid_crystal_display.clear();

      liquid_crystal_display.print("Pass Accepted");
      liquid_crystal_display.setCursor(0,1);
      liquid_crystal_display.print("Door Opened!");
      if(lock.read() == 0)
      lock.write(90);
      liquid_crystal_display.clear();
      liquid_crystal_display.setCursor(0,0);
      liquid_crystal_display.print("Door Opened!");
      liquid_crystal_display.setCursor(0,1);
      liquid_crystal_display.print("Press * to lock");
      while(isOpen != 1)
      {
        key_pressed= keypad_key.getKey();
        if(key_pressed == '*')
        {
          if(lock.read() == 90)
          lock.write(0);  
          liquid_crystal_display.clear();
          liquid_crystal_display.setCursor(0,0);
          liquid_crystal_display.print("Door Locked!");
          isOpen = 1;
        }
      }
     
           
      delay(2000);
      liquid_crystal_display.clear();
      liquid_crystal_display.setCursor(0,0);
      liquid_crystal_display.print("Press # to");
      liquid_crystal_display.setCursor(0,1);
      liquid_crystal_display.print("change password.");

      delay(2000);

      liquid_crystal_display.clear();

      liquid_crystal_display.print("Enter Password:");

      liquid_crystal_display.setCursor(0,1);

      i=0;




    }

    else
    {
      liquid_crystal_display.clear();
      liquid_crystal_display.print("Wrong Password!");
      liquid_crystal_display.setCursor(0,1);
      liquid_crystal_display.print("Try again...");
      delay(2000);
      liquid_crystal_display.clear();
      liquid_crystal_display.print("Enter Password");
      liquid_crystal_display.setCursor(0,1);
      i=0;
    }

  }

}

void change()

{

  int j=0;

  liquid_crystal_display.clear();

  liquid_crystal_display.print("Current Password");

  liquid_crystal_display.setCursor(0,1);

  while(j<4)

  {

    char key=keypad_key.getKey();

    if(key== '1' ||key == '2' || 
  key == '3' || key == '4' ||
  key == '5' || key == '6'||
  key == '7' || key == '8'||
  key == '9' || key == '0')

    {

      new_password[j++]=key;

      liquid_crystal_display.print(key);

       

    }

    key=0;

  }

  delay(500);




  if((strncmp(new_password, initial_password, 4)))

  {

    liquid_crystal_display.clear();

    liquid_crystal_display.print("Wrong Password!");

    liquid_crystal_display.setCursor(0,1);

    liquid_crystal_display.print("Try Again...");

    delay(1000);

  }

  else

  {

    j=0;

    liquid_crystal_display.clear();

    liquid_crystal_display.print("New Password:");

    liquid_crystal_display.setCursor(0,1);

    while(j<4)

    {

      char key=keypad_key.getKey();

      if(key== '1' ||key == '2' || 
  key == '3' || key == '4' ||
  key == '5' || key == '6'||
  key == '7' || key == '8'||
  key == '9' || key == '0')

      {
        initial_password[j]=key;
        liquid_crystal_display.print(key);
        EEPROM.write(j,key);
        j++;
      }
    }
    liquid_crystal_display.clear();
    liquid_crystal_display.setCursor(0,0);
    liquid_crystal_display.print("Password changed");
    liquid_crystal_display.setCursor(0,1);
    liquid_crystal_display.print("successfully!");
    delay(2000);
  }

  liquid_crystal_display.clear();
  liquid_crystal_display.print("Enter Password:");
  liquid_crystal_display.setCursor(0,1);
  key_pressed=0;

}

void initialpassword(){

  //char initial_pswd = 
  for(int j=0;j<4;j++)

    EEPROM.write(j, '0');

  for(int j=0;j<4;j++){
    initial_password[j]=EEPROM.read(j);
  }
    

} 
