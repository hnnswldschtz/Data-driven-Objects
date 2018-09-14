 #include    <Servo.h>      //Servo library
#include "Arduino.h"
#include <SoftwareSerial.h>


Servo servo_rot;//initialize a servo object for the connected servo
Servo servo_action;
int angle;
int num;

int countryId;
int action;

int currentValue = 0;
int values[] = {0, 0};

int us_state = 0;
unsigned long us_changeTime = 0;
bool input;




// Define the RS485 object
//ftwareSerial RS485(RS485rx, RS485Tx);


void setup()
{
  //servo_rot.attach(10);
 
  servo_action.attach(5);

  //servo_action.write(0);
  //servo_rot.write(20);

  Serial.begin(9600);

  //Mode(RS485inout, OUTPUT);

  // Set RS485 device to read initially
  //gitalWrite(RS485inout, RS485Receive);


  //RS485.begin(9600);








}


void loop()
{

//
//    servo_action.write(75);
//    delay(500);
//    servo_action.write(110);
//  
//    delay(150);
//    servo_action.write(75);
//    delay(500);
//    servo_action.write(0);
//    //delay(1000);





//


    if (Serial.available()>0){

      //servo_action.attach(11);
  int angle= Serial.parseInt();
  servo_action.write(angle);
 input=1;
  Serial.println(angle);}
 
  


}


