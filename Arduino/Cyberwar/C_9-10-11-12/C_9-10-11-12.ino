

#include  <Servo.h>
#include "Arduino.h"
#include <SoftwareSerial.h>


Servo servo_rot_9;//initialize a servo object for the connected servo
Servo servo_action_9;

Servo servo_rot_10;
Servo servo_action_10;

Servo servo_rot_11;
Servo servo_action_11;

Servo servo_rot_12;
Servo servo_action_12;

int angle_9;
int angle_10;

int angle_11;
int angle_12;

int num;



int countryId_9;



int countryId_10;


int countryId_11;


int countryId_12;






bool input_9 = false;
int state_9 = 0;
unsigned long changeTime_9 = 0;


bool input_10 = false;
int state_10 = 0;
unsigned long changeTime_10 = 0;


bool input_11 = false;
int state_11 = 0;
unsigned long changeTime_11 = 0;


bool input_12 = false;
int state_12 = 0;
unsigned long changeTime_12 = 0;





// These are the pins we'll be talking to the RS485 device on
#define RS485rx  12 // RS485 Receive pin  (R0)
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
pinMode(13,OUTPUT);
  // Motor initalizer
  servo_rot_9.attach(2);
  servo_action_9.attach(3);

  servo_rot_10.attach(4);
  servo_action_10.attach(5);


  servo_rot_11.attach(6);
  servo_action_11.attach(7);

  servo_action_12.attach(8);
  servo_action_12.attach(9);






  servo_action_9.write(80);
  servo_rot_9.write(5);

  servo_action_10.write(80);
  servo_rot_10.write(5);

  servo_rot_11.write(80);
  servo_action_11.write(5);

  servo_rot_12.write(80);
  servo_action_12.write(5);

  //RS485 Init
  //pinMode(RS485inout, OUTPUT);
  //digitalWrite(RS485inout, RS485Receive);// Set RS485 device to read initially
  RS485.begin(baudrate);

  Serial.begin(baudrate);

}





void loop()
{

  //digitalWrite(RS485inout, RS485Transmit);


  //RS485.write(100);
  digitalWrite(RS485inout, RS485Receive);
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

    if (RS485.read() == 0x0D) {
      Serial.print('a');
      delay(1);
      txValue01 = RS485.read();
      Serial.print(txValue01);
      delay(1);
      txValue02 = RS485.read();
      Serial.print(txValue02);
      delay(1);


      if (RS485.read() == 0x0E)
      {
        Serial.println('b');
        // if attack
        if (txValue01 == 9) {
          countryId_9 = txValue02;

          if (countryId_9 == 7 && countryId_9 == 11) 
          {
          input_9 = false;
          
          }
          else{
             input_9 = true;
            }
        }




        if (txValue01 == 10)
        {
          countryId_10 = txValue02;
          input_10 = true;
        }


        if (txValue01 == 11)
        {
          countryId_11 = txValue02;
          input_11 = true;
        }

        if (txValue01 == 12)
        {
          countryId_12 = txValue02;
          input_12 = true;
        }




      }



    }


  }











  if (countryId_9 == 2) angle_9 = 30;
  //Germany
  else if (countryId_9 == 1) angle_9 = 60;
  else if (countryId_9 == 3) angle_9 = 5;
  //Austria
  else if (countryId_9 == 4) angle_9 = 50;
  //Netherlands
  else if (countryId_9 == 5) angle_9 = 80;
  //China
  else if (countryId_9 == 6) angle_9 = 40;
  //Turkey
  //else if (countryId_9 == 7) angle_9 = 105;
  //India
  else if (countryId_9 == 8) angle_9 = 110;
  //
 
  //
  else if (countryId_9 == 10) angle_9 = 130;
  //
  //else if (countryId_9 == 11) angle_9 = 85;
  //
  else if (countryId_9 == 12) angle_9 = 180;



  if (countryId_10 == 1) angle_10 = 140;
  //Germany
   else if (countryId_10 == 2) angle_10 = 120;
  else if (countryId_10 == 3) angle_10 = 80;
  //Netherlands
  else if (countryId_10 == 4) angle_10 = 115;
  //China
  else if (countryId_10 == 5) angle_10 = 135;
  //Turkey
  else if (countryId_10 == 6) angle_10 = 70;
  //India
  else if (countryId_10 == 7) angle_10 = 65;
  //
  else if (countryId_10 == 8) angle_10 = 85;
  //
  else if (countryId_10 == 9) angle_10 = 60;
  //
 
  //
  else if (countryId_10 == 11) angle_10 = 20;

  else if (countryId_10 == 12) angle_10 = 125;




  if (countryId_11 == 1) angle_11 = 90;
  //Germany
  else if (countryId_11 == 2) angle_11 = 70;
  //Netherlands

  else if (countryId_11 == 3) angle_11 = 50;
  else if (countryId_11 == 4) angle_11 = 80;
  //China
  else if (countryId_11 == 5) angle_11 = 110;
  //Turkey
  else if (countryId_11 == 6) angle_11 = 80;
  //India
  else if (countryId_11 == 7) angle_11 = 40;
  //
  else if (countryId_11 == 8) angle_11 = 110;
  //
  else if (countryId_11 == 9) angle_11 = 110;
  //
  else if (countryId_11 == 10) angle_11 = 135;
  //
 

  else if (countryId_11 == 12) angle_11 = 170;




  if (countryId_12 == 1) angle_12 = 118;
  //Germany
  else if (countryId_12 == 2) angle_12 = 98;

  else if (countryId_12 == 3) angle_12 = 75;
  //Netherlands
  else if (countryId_12 == 4) angle_12 = 105;
  
  else if (countryId_12 == 5) angle_12 = 128;
  //Turkey
  else if (countryId_12 == 6) angle_12 = 85;
  //India
  else if (countryId_12 == 7) angle_12 = 55;
  //
  else if (countryId_12 == 8) angle_12 = 115;
  //
  else if (countryId_12 == 9) angle_12 = 70;
  //
  else if (countryId_12 == 10) angle_12 = 150;
  //
  else if (countryId_12 == 11) angle_12 = 20;

  








  // ###################################### US ################################

  //Serial.println(angle_9);
  if (input_9) {
    servo_rot_9.attach(2);
    servo_action_9.attach(3);




    if (state_9 == 0)
    {
      servo_rot_9.write(angle_9);
      state_9 = 1;
      changeTime_9 = millis();

    }


    else  if (state_9 == 1 && millis() - changeTime_9 > 500) {

      servo_action_9.write(60);
      state_9 = 2;
      changeTime_9 = millis();


    }
    else if (state_9 == 2 && millis() - changeTime_9 > 500) {

      servo_action_9.write(80);
      state_9 = 3;
      changeTime_9 = millis();

    }
    else if (state_9 == 3 && millis() - changeTime_9 > 150) {
      servo_action_9.write(60);
      state_9 = 4;
      changeTime_9 = millis();

    }
    else if (state_9 == 4 && millis() - changeTime_9 > 250) {

      servo_action_9.write(5);
      //delay(1000);
      state_9 = 5;
      //changeTime_9 = 0;
      changeTime_9 = millis();



    }
    else  if (state_9 == 5 && millis() - changeTime_9 > 600) {
      state_9 = 0;

      input_9 = 0;
    }




  } else {
    servo_rot_9.detach();
    servo_action_9.detach();
  }









  //################################# India #######################################


  if (input_10) {
    servo_rot_10.attach(4);
    servo_action_10.attach(5);




    if (state_10 == 0)
    {
      servo_rot_10.write(angle_10);
      state_10 = 1;
      changeTime_10 = millis();

    }


    else  if (state_10 == 1 && millis() - changeTime_10 > 500) {

      servo_action_10.write(60);
      state_10 = 2;
      changeTime_10 = millis();


    }
    else if (state_10 == 2 && millis() - changeTime_10 > 500) {

      servo_action_10.write(80);
      state_10 = 3;
      changeTime_10 = millis();

    }
    else if (state_10 == 3 && millis() - changeTime_10 > 150) {
      servo_action_10.write(60);
      state_10 = 4;
      changeTime_10 = millis();

    }
    else if (state_10 == 4 && millis() - changeTime_10 > 250) {

      servo_action_10.write(5);
      //delay(1000);
      state_10 = 5;
      //changeTime_10 = 0;
      changeTime_10 = millis();



    }
    else  if (state_10 == 5 && millis() - changeTime_10 > 600) {
      state_10 = 0;


      input_10 = 0;
    }




  } else {
    servo_rot_10.detach();
    servo_action_10.detach();
  }





  //####################################  3   ##############################################



  if (input_11) {
    servo_rot_11.attach(6);
    servo_action_11.attach(7);




    if (state_11 == 0)
    {
      servo_rot_11.write(angle_11);
      state_11 = 1;
      changeTime_11 = millis();

    }


    else  if (state_11 == 1 && millis() - changeTime_11 > 500) {

      servo_action_11.write(60);
      state_11 = 2;
      changeTime_11 = millis();


    }
    else if (state_11 == 2 && millis() - changeTime_11 > 500) {

      servo_action_11.write(80);
      state_11 = 3;
      changeTime_11 = millis();

    }
    else if (state_11 == 3 && millis() - changeTime_11 > 150) {
      servo_action_11.write(60);
      state_11 = 4;
      changeTime_11 = millis();

    }
    else if (state_11 == 4 && millis() - changeTime_11 > 250) {

      servo_action_11.write(5);
      //delay(1000);
      state_11 = 5;
      //changeTime_11 = 0;
      changeTime_11 = millis();



    }
    else  if (state_11 == 5 && millis() - changeTime_11 > 600) {
      state_11 = 0;


      input_11 = 0;
    }




  } else {
    servo_rot_11.detach();
    servo_action_11.detach();
  }















  //####################################  3   ##############################################





  if (input_12) {
    servo_rot_12.attach(8);
    servo_action_12.attach(9);




    if (state_12 == 0)
    {
      servo_rot_12.write(angle_12);
      state_12 = 1;
      changeTime_12 = millis();

    }


    else  if (state_12 == 1 && millis() - changeTime_12 > 500) {

      servo_action_12.write(60);
      state_12 = 2;
      changeTime_12 = millis();


    }
    else if (state_12 == 2 && millis() - changeTime_12 > 500) {

      servo_action_12.write(80);
      state_12 = 3;
      changeTime_12 = millis();

    }
    else if (state_12 == 3 && millis() - changeTime_12 > 150) {
      servo_action_12.write(60);
      state_12 = 4;
      changeTime_12 = millis();

    }
    else if (state_12 == 4 && millis() - changeTime_12 > 250) {

      servo_action_12.write(5);
      //delay(1000);
      state_12 = 5;
      //changeTime_12 = 0;
      changeTime_12 = millis();



    }
    else  if (state_12 == 5 && millis() - changeTime_12 > 600) {
      state_12 = 0;


      input_12 = 0;
    }




  } else {
    servo_rot_12.detach();
    servo_action_12.detach();
  }

}
