

#include  <Servo.h>
#include "Arduino.h"
#include <SoftwareSerial.h>


Servo servo_rot_1;//initialize a servo object for the connected servo
Servo servo_action_1;

Servo servo_rot_2;
Servo servo_action_2;

Servo servo_rot_3;
Servo servo_action_3;

Servo servo_rot_4;
Servo servo_action_4;

int angle_1;
int angle_2;

int angle_3;
int angle_4;

int num;



int countryId_1;



int countryId_2;


int countryId_3;


int countryId_4;






bool input_1 = false;
int state_1 = 0;
unsigned long changeTime_1 = 0;


bool input_2 = false;
int state_2 = 0;
unsigned long changeTime_2 = 0;


bool input_3 = false;
int state_3 = 0;
unsigned long changeTime_3 = 0;


bool input_4 = false;
int state_4 = 0;
unsigned long changeTime_4 = 0;





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
  servo_rot_1.attach(2);
  servo_action_1.attach(3);

  servo_rot_2.attach(4);
  servo_action_2.attach(5);


  servo_rot_3.attach(6);
  servo_action_3.attach(7);

  servo_rot_4.attach(8);
  servo_action_4.attach(9);






  servo_action_1.write(80);
  servo_rot_1.write(5);

  servo_action_2.write(80);
  servo_rot_2.write(5);

  servo_rot_3.write(80);
  servo_action_3.write(5);

  servo_rot_4.write(80);
  servo_action_4.write(5);

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
        if (txValue01 == 1) {
          countryId_1 = txValue02;
          input_1 = true;

        }




        if (txValue01 == 2)
        {
          countryId_2 = txValue02;
          input_2 = true;
        }


        if (txValue01 == 3)
        {
          countryId_3 = txValue02;
          input_3 = true;
        }

        if (txValue01 == 4)
        {
          countryId_4 = txValue02;
          input_4 = true;
        }




      }



    }


  }











  if (countryId_1 == 2) angle_1 = 150;
  //Germany
  else if (countryId_1 == 3) angle_1 = 125;
  //Austria
  else if (countryId_1 == 4) angle_1 = 110;
  //Netherlands
  else if (countryId_1 == 5) angle_1 = 53;
  //China
  else if (countryId_1 == 6) angle_1 = 90;
  //Turkey
  else if (countryId_1 == 7) angle_1 = 105;
  //India
  else if (countryId_1 == 8) angle_1 = 70;
  //
  else if (countryId_1 == 9) angle_1 = 80;
  //
  else if (countryId_1 == 10) angle_1 = 60;
  //
  else if (countryId_1 == 11) angle_1 = 85;
  //
  else if (countryId_1 == 12) angle_1 = 70;



  if (countryId_2 == 1) angle_2 = 45;
  //Germany
  else if (countryId_2 == 3) angle_2 = 180;
  //Netherlands
  else if (countryId_2 == 4) angle_2 = 105;
  //China
  else if (countryId_2 == 5) angle_2 = 90;
  //Turkey
  else if (countryId_2 == 6) angle_2 = 130;
  //India
  else if (countryId_2 == 7) angle_2 = 150;
  //
  else if (countryId_2 == 8) angle_2 = 110;
  //
  else if (countryId_2 == 9) angle_2 = 130;
  //
  else if (countryId_2 == 10) angle_2 = 105;
  //
  else if (countryId_2 == 11) angle_2 = 140;

  else if (countryId_2 == 12) angle_2 = 125;




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




  if (countryId_4 == 1) angle_4 = 180;
  //Germany
  else if (countryId_4 == 2) angle_4 = 140;

  else if (countryId_4 == 3) angle_4 = 120;
  //Netherlands
  else if (countryId_4 == 4) angle_4 = 130;
  //Turkey
  else if (countryId_4 == 6) angle_4 = 95;
  //India
  else if (countryId_4 == 7) angle_4 = 85;
  //
  else if (countryId_4 == 8) angle_4 = 65;
  //
  else if (countryId_4 == 9) angle_4 = 72;
  //
  else if (countryId_4 == 10) angle_4 = 30;
  //
  else if (countryId_4 == 11) angle_4 = 68;

  else if (countryId_4 == 12) angle_4 = 50;








  // ###################################### US ################################

  //Serial.println(angle_1);
  if (input_1) {
    servo_rot_1.attach(2);
    servo_action_1.attach(3);




    if (state_1 == 0)
    {
      servo_rot_1.write(angle_1);
      state_1 = 1;
      changeTime_1 = millis();

    }


    else  if (state_1 == 1 && millis() - changeTime_1 > 500) {

      servo_action_1.write(60);
      state_1 = 2;
      changeTime_1 = millis();


    }
    else if (state_1 == 2 && millis() - changeTime_1 > 500) {

      servo_action_1.write(80);
      state_1 = 3;
      changeTime_1 = millis();

    }
    else if (state_1 == 3 && millis() - changeTime_1 > 150) {
      servo_action_1.write(60);
      state_1 = 4;
      changeTime_1 = millis();

    }
    else if (state_1 == 4 && millis() - changeTime_1 > 250) {

      servo_action_1.write(5);
      //delay(1000);
      state_1 = 5;
      //changeTime_1 = 0;
      changeTime_1 = millis();



    }
    else  if (state_1 == 5 && millis() - changeTime_1 > 600) {
      state_1 = 0;

      input_1 = 0;
    }




  } else {
    servo_rot_1.detach();
    servo_action_1.detach();
  }









  //################################# India #######################################


  if (input_2) {
    servo_rot_2.attach(4);
    servo_action_2.attach(5);




    if (state_2 == 0)
    {
      servo_rot_2.write(angle_2);
      state_2 = 1;
      changeTime_2 = millis();

    }


    else  if (state_2 == 1 && millis() - changeTime_2 > 500) {

      servo_action_2.write(60);
      state_2 = 2;
      changeTime_2 = millis();


    }
    else if (state_2 == 2 && millis() - changeTime_2 > 500) {

      servo_action_2.write(80);
      state_2 = 3;
      changeTime_2 = millis();

    }
    else if (state_2 == 3 && millis() - changeTime_2 > 150) {
      servo_action_2.write(60);
      state_2 = 4;
      changeTime_2 = millis();

    }
    else if (state_2 == 4 && millis() - changeTime_2 > 250) {

      servo_action_2.write(5);
      //delay(1000);
      state_2 = 5;
      //changeTime_2 = 0;
      changeTime_2 = millis();



    }
    else  if (state_2 == 5 && millis() - changeTime_2 > 600) {
      state_2 = 0;


      input_2 = 0;
    }




  } else {
    servo_rot_2.detach();
    servo_action_2.detach();
  }





  //####################################  3   ##############################################



  if (input_3) {
    servo_rot_3.attach(6);
    servo_action_3.attach(7);




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
    else  if (state_3 == 5 && millis() - changeTime_3 > 600) {
      state_3 = 0;


      input_3 = 0;
    }




  } else {
    servo_rot_3.detach();
    servo_action_3.detach();
  }















  //####################################  3   ##############################################





  if (input_4) {
    servo_rot_4.attach(8);
    servo_action_4.attach(9);




    if (state_4 == 0)
    {
      servo_rot_4.write(angle_4);
      state_4 = 1;
      changeTime_4 = millis();

    }


    else  if (state_4 == 1 && millis() - changeTime_4 > 500) {

      servo_action_4.write(60);
      state_4 = 2;
      changeTime_4 = millis();


    }
    else if (state_4 == 2 && millis() - changeTime_4 > 500) {

      servo_action_4.write(80);
      state_4 = 3;
      changeTime_4 = millis();

    }
    else if (state_4 == 3 && millis() - changeTime_4 > 150) {
      servo_action_4.write(60);
      state_4 = 4;
      changeTime_4 = millis();

    }
    else if (state_4 == 4 && millis() - changeTime_4 > 250) {

      servo_action_4.write(5);
      //delay(1000);
      state_4 = 5;
      //changeTime_4 = 0;
      changeTime_4 = millis();



    }
    else  if (state_4 == 5 && millis() - changeTime_4 > 600) {
      state_4 = 0;


      input_4 = 0;
    }




  } else {
    servo_rot_4.detach();
    servo_action_4.detach();
  }

}
