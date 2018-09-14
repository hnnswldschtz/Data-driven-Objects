

#include  <Servo.h>
#include "Arduino.h"
#include <SoftwareSerial.h>


Servo servo_rot_5;//initialize a servo object for the connected servo
Servo servo_action_5;

Servo servo_rot_6;
Servo servo_action_6;

Servo servo_rot_7;
Servo servo_action_7;

Servo servo_rot_8;
Servo servo_action_8;

int angle_5;
int angle_6;

int angle_7;
int angle_8;





int countryId_5;



int countryId_6;


int countryId_7;


int countryId_8;






bool input_5 = false;
int state_5 = 0;
unsigned long changeTime_5 = 0;


bool input_6 = false;
int state_6 = 0;
unsigned long changeTime_6 = 0;


bool input_7 = false;
int state_7 = 0;
unsigned long changeTime_7 = 0;


bool input_8 = false;
int state_8 = 0;
unsigned long changeTime_8 = 0;





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
//pinMode(13,OUTPUT);
  // Motor initalizer
  servo_rot_5.attach(2);
  servo_action_5.attach(3);

  servo_rot_6.attach(4);
  servo_action_6.attach(5);


  servo_rot_7.attach(6);
  servo_action_7.attach(7);

  servo_rot_8.attach(8);
  servo_action_8.attach(9);






  servo_action_5.write(80);
  servo_rot_5.write(5);

  servo_action_6.write(80);
  servo_rot_6.write(5);

  servo_rot_7.write(80);
  servo_action_7.write(5);

  servo_rot_8.write(80);
  servo_action_8.write(5);

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
        if (txValue01 == 5) {
          countryId_5 = txValue02;
          input_5 = true;

        }




        if (txValue01 == 6)
        {
          countryId_6 = txValue02;
          
          if (countryId_6==3 || countryId_6==7){
          input_6 = false;}
          else {input_6 = true;
            }
        }


        if (txValue01 == 7)
        {
          countryId_7 = txValue02;
          input_7 = true;
        }

        if (txValue01 == 8)
        {
          countryId_8 = txValue02;
           if (countryId_8==10){
          input_8 = false;}
          else {input_8 = true;
            }
        }




      }



    }


  }











  if (countryId_5 == 2) angle_5 = 140;
  //Germany
  else if (countryId_5 == 3) angle_5 = 120;
  //Austria
  else if (countryId_5 == 4) angle_5 = 130;
  //Netherlands
  else if (countryId_5 == 1) angle_5 = 180;
  //China
  else if (countryId_5 == 6) angle_5 = 95;
  //Turkey
  else if (countryId_5 == 7) angle_5 = 85;
  //India
  else if (countryId_5 == 8) angle_5 = 65;
  //
  else if (countryId_5 == 9) angle_5 = 72;
  //
  else if (countryId_5 == 10) angle_5 = 30;
  //
  else if (countryId_5 == 11) angle_5 = 68;
  //
  else if (countryId_5 == 12) angle_5 = 50;



  if (countryId_6 == 1) angle_6 = 20;
  //Germany
  else if (countryId_6 == 2) angle_6 = 0;
  //Netherlands
  else if (countryId_6 == 4) angle_6 = 10;
  //China
  else if (countryId_6 == 5) angle_6 = 55;
  //Turkey

  //India

  //
  else if (countryId_6 == 8) angle_6 = 90;
  //
  else if (countryId_6 == 9) angle_6 = 160;
  //
  else if (countryId_6 == 10) angle_6 = 110;
  //
  else if (countryId_6 == 11) angle_6 = 180;

  else if (countryId_6 == 12) angle_6 = 140;




  if (countryId_7 == 1) angle_7 = 40;
  //Germany
  else if (countryId_7 == 2) angle_7 = 25;

    else if (countryId_7 == 3) angle_7 = 5;
  //Netherlands
  else if (countryId_7 == 4) angle_7 = 35;
  //China
  else if (countryId_7 == 5) angle_7 = 70;
  //Turkey
  else if (countryId_7 == 6) angle_7 = 60;
  //India
 
  //
  else if (countryId_7 == 8) angle_7 = 85;
  //
  else if (countryId_7 == 9) angle_7 = 110;
  //
  else if (countryId_7 == 10) angle_7 = 100;
  //
  else if (countryId_7 == 11) angle_7 = 170;

  else if (countryId_7 == 12) angle_7 = 130;




  if (countryId_8 == 1) angle_8 = 160;
  //Germany
  else if (countryId_8 == 2) angle_8 = 130;

  else if (countryId_8 == 3) angle_8 = 110;
  //Netherlands
  else if (countryId_8 == 4) angle_8 = 130;

  else if (countryId_8 == 5) angle_8 = 180;
  //Turkey
  else if (countryId_8 == 6) angle_8 = 100;
  //India
  else if (countryId_8 == 7) angle_8 = 70;
  //
 
  //
  else if (countryId_8 == 9) angle_8 = 50;
  //
  //else if (countryId_8 == 10) angle_8 = 30;
  //
  else if (countryId_8 == 11) angle_8 = 35;

  else if (countryId_8 == 12) angle_8 = 5;








  // ###################################### US ################################

  //Serial.println(angle_8);
  if (input_5) {
    servo_rot_5.attach(2);
    servo_action_5.attach(3);




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
    else  if (state_5 == 5 && millis() - changeTime_5 > 600) {
      state_5 = 0;

      input_5 = 0;
    }




  } else {
    servo_rot_5.detach();
    servo_action_5.detach();
  }









  //################################# India #######################################


  if (input_6) {
    servo_rot_6.attach(4);
    servo_action_6.attach(5);




    if (state_6 == 0)
    {
      servo_rot_6.write(angle_6);
      state_6 = 1;
      changeTime_6 = millis();

    }


    else  if (state_6 == 1 && millis() - changeTime_6 > 500) {

      servo_action_6.write(60);
      state_6 = 2;
      changeTime_6 = millis();


    }
    else if (state_6 == 2 && millis() - changeTime_6 > 500) {

      servo_action_6.write(80);
      state_6 = 3;
      changeTime_6 = millis();

    }
    else if (state_6 == 3 && millis() - changeTime_6 > 150) {
      servo_action_6.write(60);
      state_6 = 4;
      changeTime_6 = millis();

    }
    else if (state_6 == 4 && millis() - changeTime_6 > 250) {

      servo_action_6.write(5);
      //delay(1000);
      state_6 = 5;
      //changeTime_6 = 0;
      changeTime_6 = millis();



    }
    else  if (state_6 == 5 && millis() - changeTime_6 > 600) {
      state_6 = 0;


      input_6 = 0;
    }




  } else {
    servo_rot_6.detach();
    servo_action_6.detach();
  }





  //####################################  3   ##############################################



  if (input_7) {
    servo_rot_7.attach(6);
    servo_action_7.attach(7);




    if (state_7 == 0)
    {
      servo_rot_7.write(angle_7);
      state_7 = 1;
      changeTime_7 = millis();

    }


    else  if (state_7 == 1 && millis() - changeTime_7 > 500) {

      servo_action_7.write(60);
      state_7 = 2;
      changeTime_7 = millis();


    }
    else if (state_7 == 2 && millis() - changeTime_7 > 500) {

      servo_action_7.write(80);
      state_7 = 3;
      changeTime_7 = millis();

    }
    else if (state_7 == 3 && millis() - changeTime_7 > 150) {
      servo_action_7.write(60);
      state_7 = 4;
      changeTime_7 = millis();

    }
    else if (state_7 == 4 && millis() - changeTime_7 > 250) {

      servo_action_7.write(5);
      //delay(1000);
      state_7 = 5;
      //changeTime_7 = 0;
      changeTime_7 = millis();



    }
    else  if (state_7 == 5 && millis() - changeTime_7 > 600) {
      state_7 = 0;


      input_7 = 0;
    }




  } else {
    servo_rot_7.detach();
    servo_action_7.detach();
  }















  //####################################  3   ##############################################





  if (input_8) {
    servo_rot_8.attach(8);
    servo_action_8.attach(9);




    if (state_8 == 0)
    {
      servo_rot_8.write(angle_8);
      state_8 = 1;
      changeTime_8 = millis();

    }


    else  if (state_8 == 1 && millis() - changeTime_8 > 500) {

      servo_action_8.write(60);
      state_8 = 2;
      changeTime_8 = millis();


    }
    else if (state_8 == 2 && millis() - changeTime_8 > 500) {

      servo_action_8.write(80);
      state_8 = 3;
      changeTime_8 = millis();

    }
    else if (state_8 == 3 && millis() - changeTime_8 > 150) {
      servo_action_8.write(60);
      state_8 = 4;
      changeTime_8 = millis();

    }
    else if (state_8 == 4 && millis() - changeTime_8 > 250) {

      servo_action_8.write(5);
      //delay(1000);
      state_8 = 5;
      //changeTime_8 = 0;
      changeTime_8 = millis();



    }
    else  if (state_8 == 5 && millis() - changeTime_8 > 600) {
      state_8 = 0;


      input_8 = 0;
    }




  } else {
    servo_rot_8.detach();
    servo_action_8.detach();
  }

}
