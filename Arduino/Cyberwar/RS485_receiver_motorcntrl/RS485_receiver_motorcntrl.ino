

#include  <Servo.h>
#include "Arduino.h"
#include <SoftwareSerial.h>


Servo servo_rot_us;//initialize a servo object for the connected servo
Servo servo_action_us;

Servo servo_rot_india;
Servo servo_action_india;

Servo servo_rot_3;
Servo servo_action_3;

Servo servo_rot_5;
Servo servo_action_5;

int angle_us;
int angle_india;

int angle_3;
int angle_5;

int num;


int action_us;
int countryId_us;


int action_india;
int countryId_india;


int countryId_3;


int countryId_5;






bool input_us = false;
int us_state = 0;
unsigned long us_changeTime = 0;


bool input_india = false;
int india_state = 0;
unsigned long india_changeTime = 0;


bool input_3 = false;
int state_3 = 0;
unsigned long changeTime_3 = 0;


bool input_5 = false;
int state_5 = 0;
unsigned long changeTime_5 = 0;





// These are the pins we'll be talking to the RS485 device on
#define RS485rx  4 // RS485 Receive pin  (R0)
#define RS485Tx  2 // RS485 Transmit pin  (DI)
#define RS485inout  8 // RS485 Transmit or Receive status  (DE)
// Ceonnect DE  & RE
// Connect the A's and the B's with the other boards
// GND with arduion GND and Vcc with 5v arduino



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
  servo_rot_us.attach(9);
  servo_action_us.attach(10);

  servo_rot_india.attach(11);
  servo_action_india.attach(12);


  servo_rot_3.attach(5);
  servo_action_3.attach(6);

  servo_rot_5.attach(7);
  servo_action_5.attach(13);






  servo_action_us.write(80);
  servo_rot_us.write(0);

  servo_action_india.write(80);
  servo_rot_india.write(0);

  servo_rot_3.write(80);
  servo_action_3.write(0);

  servo_rot_5.write(80);
  servo_action_5.write(0);

  //RS485 Init
  pinMode(RS485inout, OUTPUT);
  digitalWrite(RS485inout, RS485Receive);// Set RS485 device to read initially
  RS485.begin(baudrate);

  Serial.begin(baudrate);

}





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
      Serial.print(txValue01);
      delay(1);
      txValue02 = RS485.read();
      Serial.print(txValue02);
      delay(1);


      if (RS485.read() == 'b')
      {
        Serial.println('b');
        // if attack
        if (txValue01 == 1) {
          countryId_us = txValue02;
          action_us = 0;
          input_us = true;

        }




        if (txValue01 == 2)
        {
          countryId_india = txValue02;
          action_india = 0;
          input_india = true;
        }


        if (txValue01 == 3)
        {
          countryId_3 = txValue02;
          input_3 = true;
        }

        if (txValue01 == 5)
        {
          countryId_5 = txValue02;
          input_5 = true;
        }




      }



    }


  }











  if (countryId_us == 2) angle_us = 150;
  //Germany
  else if (countryId_us == 3) angle_us = 125;
  //Austria
  else if (countryId_us == 4) angle_us = 110;
  //Netherlands
  else if (countryId_us == 5) angle_us = 53;
  //China
  else if (countryId_us == 6) angle_us = 90;
  //Turkey
  else if (countryId_us == 7) angle_us = 105;
  //India
  else if (countryId_us == 8) angle_us = 70;
  //
  else if (countryId_us == 9) angle_us = 80;
  //
  else if (countryId_us == 10) angle_us = 60;
  //
  else if (countryId_us == 11) angle_us = 85;
  //
  else if (countryId_us == 12) angle_us = 70;



  if (countryId_india == 1) angle_india = 45;
  //Germany
  else if (countryId_india == 3) angle_india = 180;
  //Netherlands
  else if (countryId_india == 4) angle_india = 105;
  //China
  else if (countryId_india == 5) angle_india = 90;
  //Turkey
  else if (countryId_india == 6) angle_india = 130;
  //India
  else if (countryId_india == 7) angle_india = 150;
  //
  else if (countryId_india == 8) angle_india = 110;
  //
  else if (countryId_india == 9) angle_india = 130;
  //
  else if (countryId_india == 10) angle_india = 105;
  //
  else if (countryId_india == 11) angle_india = 140;

  else if (countryId_india == 12) angle_india = 125;




  if (countryId_3 == 1) angle_3 = 45;
  //Germany
  else if (countryId_3 == 2) angle_3 = 30;
  //Netherlands
  else if (countryId_3 == 4) angle_3 = 60;
  //China
  else if (countryId_3 == 5) angle_3 = 75;
  //Turkey
  else if (countryId_3 == 6) angle_3 = 105;
  //India
  else if (countryId_3 == 7) angle_3 = 145;
  //
  else if (countryId_3 == 8) angle_3 = 92;
  //
  else if (countryId_3 == 9) angle_3 = 120;
  //
  else if (countryId_3 == 10) angle_3 = 92;
  //
  else if (countryId_3 == 11) angle_3 = 135;

  else if (countryId_3 == 12) angle_3 = 114;




  if (countryId_5 == 1) angle_5 = 180;
  //Germany
  else if (countryId_5 == 2) angle_5 = 140;

  else if (countryId_5 == 3) angle_5 = 120;
  //Netherlands
  else if (countryId_5 == 4) angle_5 = 130;
  //Turkey
  else if (countryId_5 == 6) angle_5 = 95;
  //India
  else if (countryId_5 == 7) angle_5 = 85;
  //
  else if (countryId_5 == 8) angle_5 = 65;
  //
  else if (countryId_5 == 9) angle_5 = 72;
  //
  else if (countryId_5 == 10) angle_5 = 30;
  //
  else if (countryId_5 == 11) angle_5 = 68;

  else if (countryId_5 == 12) angle_5 = 50;








  // ###################################### US ################################

  //Serial.println(angle_us);
  if (input_us) {
    servo_rot_us.attach(9);
    servo_action_us.attach(10);




    if (us_state == 0)
    {
      servo_rot_us.write(angle_us);
      us_state = 1;
      us_changeTime = millis();

    }


    else  if (us_state == 1 && millis() - us_changeTime > 500) {

      servo_action_us.write(60);
      us_state = 2;
      us_changeTime = millis();


    }
    else if (us_state == 2 && millis() - us_changeTime > 500) {

      servo_action_us.write(80);
      us_state = 3;
      us_changeTime = millis();

    }
    else if (us_state == 3 && millis() - us_changeTime > 150) {
      servo_action_us.write(60);
      us_state = 4;
      us_changeTime = millis();

    }
    else if (us_state == 4 && millis() - us_changeTime > 250) {

      servo_action_us.write(5);
      //delay(1000);
      us_state = 5;
      //us_changeTime = 0;
      us_changeTime = millis();



    }
    else  if (us_state == 5 && millis() - us_changeTime > 1000) {
      us_state = 0;

      input_us = 0;
    }




  } else {
    servo_rot_us.detach();
    servo_action_us.detach();
  }









  //################################# India #######################################


  if (input_india) {
    servo_rot_india.attach(11);
    servo_action_india.attach(12);




    if (india_state == 0)
    {
      servo_rot_india.write(angle_india);
      india_state = 1;
      india_changeTime = millis();

    }


    else  if (india_state == 1 && millis() - india_changeTime > 500) {

      servo_action_india.write(60);
      india_state = 2;
      india_changeTime = millis();


    }
    else if (india_state == 2 && millis() - india_changeTime > 500) {

      servo_action_india.write(80);
      india_state = 3;
      india_changeTime = millis();

    }
    else if (india_state == 3 && millis() - india_changeTime > 150) {
      servo_action_india.write(60);
      india_state = 4;
      india_changeTime = millis();

    }
    else if (india_state == 4 && millis() - india_changeTime > 250) {

      servo_action_india.write(5);
      //delay(1000);
      india_state = 5;
      //india_changeTime = 0;
      india_changeTime = millis();



    }
    else  if (india_state == 5 && millis() - india_changeTime > 1000) {
      india_state = 0;


      input_india = 0;
    }




  } else {
    servo_rot_india.detach();
    servo_action_india.detach();
  }





  //####################################  3   ##############################################



  if (input_3) {
    servo_rot_3.attach(5);
    servo_action_3.attach(6);




    if (state_3 == 0)
    {
      servo_rot_3.write(angle_3);
      state_3 = 1;
      changeTime_3 = millis();

    }


    else  if (state_3 == 1 && millis() - changeTime_3 > 500) {

      servo_action_3.write(60);
      state_3 = 2;
      changeTime_3 = millis();


    }
    else if (state_3 == 2 && millis() - changeTime_3 > 500) {

      servo_action_3.write(80);
      state_3 = 3;
      changeTime_3 = millis();

    }
    else if (state_3 == 3 && millis() - changeTime_3 > 150) {
      servo_action_3.write(60);
      state_3 = 4;
      changeTime_3 = millis();

    }
    else if (state_3 == 4 && millis() - changeTime_3 > 250) {

      servo_action_3.write(5);
      //delay(1000);
      state_3 = 5;
      //changeTime_3 = 0;
      changeTime_3 = millis();



    }
    else  if (state_3 == 5 && millis() - changeTime_3 > 1000) {
      state_3 = 0;


      input_3 = 0;
    }




  } else {
    servo_rot_3.detach();
    servo_action_3.detach();
  }















  //####################################  3   ##############################################





  if (input_5) {
    servo_rot_5.attach(7);
    servo_action_5.attach(13);




    if (state_5 == 0)
    {
      servo_rot_5.write(angle_5);
      state_5 = 1;
      changeTime_5 = millis();

    }


    else  if (state_5 == 1 && millis() - changeTime_5 > 500) {

      servo_action_5.write(60);
      state_5 = 2;
      changeTime_5 = millis();


    }
    else if (state_5 == 2 && millis() - changeTime_5 > 500) {

      servo_action_5.write(80);
      state_5 = 3;
      changeTime_5 = millis();

    }
    else if (state_5 == 3 && millis() - changeTime_5 > 150) {
      servo_action_5.write(60);
      state_5 = 4;
      changeTime_5 = millis();

    }
    else if (state_5 == 4 && millis() - changeTime_5 > 250) {

      servo_action_5.write(5);
      //delay(1000);
      state_5 = 5;
      //changeTime_5 = 0;
      changeTime_5 = millis();



    }
    else  if (state_5 == 5 && millis() - changeTime_5 > 1000) {
      state_5 = 0;


      input_5 = 0;
    }




  } else {
    servo_rot_5.detach();
    servo_action_5.detach();
  }

}
