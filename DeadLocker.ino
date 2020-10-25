/*
   Name: DeadLocker application
   Date Created: October 18, 2020
   Creators: Jester Cornejo & Ian Baguio
   Date Updated: October 24, 2020

   References: https://www.instructables.com/How-to-Use-I2C-Serial-LCD-20X4-Yellow-Backlight/
               https://www.youtube.com/watch?v=wEbGhYjn4QI&t=1649s

*/
#define lockerS 9
#define grn 3
#define spk 7
#include "LED.h"
#include "Person.h"
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"
Servo Locker;

FPS_GT511C3 fps(4, 5);

// LCD variables
int lcdWidth = 20;
int lcdHeight = 4;
String message = "";
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7);



LED Green = LED(grn);


bool isLocked;

Person person = Person(2, "Jester", "Cornejo");

void setup() {
  //delair servo port
  Locker.attach(lockerS);
  
  //begin baudrate 9600
  Serial.begin(9600);
  
  //declair pin modes
  pinMode(3, OUTPUT);

  // LCD setup
  lcd.begin(lcdWidth, lcdHeight);

  Beep(3, 80);
  UnLock();
  fps.Open();         //send serial command to initialize fps
  fps.SetLED(true);   //turn on LED so fps can see fingerprint
}


void loop() {
  // put your main code here, to run repeatedly:
 if (fps.IsPressFinger() == true)
 {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    
       /*Note:  GT-521F52 can hold 3000 fingerprint templates
                GT-521F32 can hold 200 fingerprint templates
                 GT-511C3 can hold 200 fingerprint templates. 
                GT-511C1R can hold 20 fingerprint templates.
       Make sure to change the id depending on what
       model you are using */
    if (id == 2 || id == 3) //<- change id value depending model you are using
    {//if the fingerprint matches, provide the matching template ID
      Serial.print("Verified ID:");
      Serial.println(id);
      UnLock();
      delay(3000);
    }
    else
    {//if unable to recognize
      Serial.println("Finger not found");
     
    }
  }

  delay(100);
   Lock();


}

void Lock()
{

  Locker.write(90);
  delay(1000);
  Locker.detach();
}
void UnLock()
{
   Locker.attach(lockerS);
   delay(1000);
 Locker.write(10);

}

/*
   Function: Beep

   Purpose: turn on the passive buzzer.
   Parameters: freq = how many times the buzzer should beep
                del = delay of buzzer's oscillation
*/
void Beep(int freq, int del)
{
  for (int i = 0; i < freq; i++)
  {
    digitalWrite(spk, HIGH);
    delay(del);
    digitalWrite(spk, LOW);
    delay(del);
  }
}

/*
   Function: deadLocker

   Parameters: status - true = lock
                        false = unlock

*/
void deadLocker(bool stat) {

}
