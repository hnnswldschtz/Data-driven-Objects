

#include  <Servo.h>
#include "Arduino.h"
#include <SoftwareSerial.h>


Servo servo_rot_us;//initialize a servo object for the connected servo
Servo servo_action_us;

Servo servo_rot_india;
Servo servo_action_india;

int angle_us;
int angle_china;
int angle_india;

int num;



int action_india;
int countryId_india;


int action_us;
int countryId_us;

int currentValue = 0;
int values[] = {0, 0};


bool input_us = false;
bool input_india = false;



// These are the pins we'll be talking to the RS485 device on
#define RS485rx  4 // RS485 Receive pin  (R0)
#define RS485Tx  2 // RS485 Transmit pin  (DI)
#define RS485inout  8 // RS485 Transmit or Receive status  (DE)
// Ceonnect DE  & RE
// Connect the A's and the B's with the other boards 



#define RS485Transmit  HIGH
#define RS485Receive  LOW
#define baudrate 9600

// Define the RS485 object
SoftwareSerial RS485(RS485rx, RS485Tx);

// The data bytes we're sending or receiving
byte rxValue;
byte txValue01;
byte txValue02;

void setup()
{

  // Motor initalizer
  servo_rot_us.attach(10);
  servo_action_us.attach(11);

  servo_rot_india.attach(12);
  servo_action_india.attach(7);




  servo_action_us.write(80);
  servo_rot_us.write(0);

  servo_action_india.write(80);
  servo_rot_india.write(0);

  //RS485 Init
  pinMode(RS485inout, OUTPUT);
  digitalWrite(RS485inout, RS485Receive);// Set RS485 device to read initially
  RS485.begin(baudrate);

  Serial.begin(baudrate);

}



unsigned long delay_rot_us = 0;
unsigned long delay_action_us = 0;


unsigned long delay_rot_india = 0;
unsigned long delay_action_india = 0;

void loop()
{

  if (RS485.available()) {

    //    int incomingValue = RS485.read();
    //
    //    values[currentValue++] = incomingValue;
    //
    //    if (currentValue>1){currentValue=0;}
    //
    //
    //    action=values[0];
    //    countryId= values[1];

    if (RS485.read() == 'a') {

      Serial.print('a');
      delay(1);
      txValue01 = RS485.read();
      delay(1);
      txValue02 = RS485.read();
      delay(1);


      if (RS485.read() == 'b')
      {
        //Serial.println('b');

        if (txValue01 == 0) {
          countryId_us = txValue02;
          action_us = 0;
          input_us = true;

        }

        if (txValue02 == 0) {
          countryId_us = txValue01;
          action_us = 1;
          input_us = true;
        }

        if (txValue01 == 7)
        {
          countryId_india = txValue02;
          action_india = 0;
          input_india = true;
        }

        if (txValue02 == 7)
        {
          countryId_india = txValue01;
          action_india = 1;
          input_india = true;
        }


      }



    }


  }








  //    Serial.println(values[0]);
  //    Serial.println(values[1]);
  //    Serial.println(currentValue);
  //num=Serial.parseInt();

  //htmlInput= Serial.read();
  //Serial.println("Testing Serial");
  //Serial.println(num);

  //num=int((map(num,0,100,1000,50)));
  //
  //Thailand


  //us --> china Action


  if (countryId_us == 1) angle_us = 108;
  //Germany
  else if (countryId_us == 2) angle_us = 18;
  //Austria
  else if (countryId_us == 3) angle_us = 36;
  //Netherlands
  else if (countryId_us == 4) angle_us = 54;
  //China
  else if (countryId_us == 5) angle_us = 72;
  //Turkey
  else if (countryId_us == 6) angle_us = 90;
  //India
  else if (countryId_us == 7) angle_us = 1;
  //
  else if (countryId_us == 8) angle_us = 126;
  //
  else if (countryId_us == 9) angle_us = 144;
  //
  else if (countryId_us == 10) angle_us = 162;
  //
  else if (countryId_us == 11) angle_us = 180;



  if (countryId_india == 1) angle_india = 1;
  //Germany
  else if (countryId_india == 2) angle_india = 18;
  //Austria
  else if (countryId_india == 3) angle_india = 36;
  //Netherlands
  else if (countryId_india == 4) angle_india = 54;
  //China
  else if (countryId_india == 5) angle_india = 72;
  //Turkey
  else if (countryId_india == 6) angle_india = 90;
  //India
  else if (countryId_india == 0) angle_india = 170;
  //
  else if (countryId_india == 8) angle_india = 126;
  //
  else if (countryId_india == 9) angle_india = 144;
  //
  else if (countryId_india == 10) angle_india = 162;
  //
  else if (countryId_india == 11) angle_india = 108;








// ###################################### US ################################

  //Serial.println(angle_us);
  if (input_us) {


    if (action_us == 0) {
      //2000-0=2000

      
      servo_rot_us.write(angle_us);

      delay(1000);

      servo_action_us.write(180);
       delay(100);
      servo_action_us.write(140);

      delay(500);

      servo_action_us.write(100);




    }




    if (action_us == 1) {

      servo_rot_us.write(angle_us);


      delay(1000);

      servo_action_us.write(180);

      delay(500);

      servo_action_us.write(100);
      input_us = false;


    }


    
    input_us = false;

  }










//################################# India #######################################


  if (input_india) {




    if (action_india == 0) {


      servo_rot_india.write(angle_india);

      delay(1000);

      servo_action_india.write(0);

      delay(500);
      delay_action_india = millis();
      servo_action_india.write(65);


    }



    if (action_india == 1) {



      servo_rot_india.write(angle_india);

      delay(1000);

      servo_action_india.write(110);

      delay(500);

      servo_action_india.write(65);



    }





    input_india = false;

    
  }



}
