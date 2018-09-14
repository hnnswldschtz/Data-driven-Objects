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
  servo_rot.attach(2);
  servo_action.attach(3);

  //servo_action.write(0);
  //servo_rot.write(0);

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
   angle= Serial.parseInt();
  
 input=1;
  Serial.println(angle);}
  


   if (input)
   {
     servo_rot.attach(2);
  servo_action.attach(3);

 
  
 

if (us_state==0) 
{

   Serial.print("Angle in state: ");
  Serial.println(angle);
     servo_rot.write(angle);
    us_state=1;
     us_changeTime = millis();
     Serial.println("State zero");
  }

    
   else  if (us_state == 1 && millis() - us_changeTime > 600) {
  
      servo_action.write(70);
      us_state = 2;
      us_changeTime = millis();
      Serial.println("State one");
     
    }
    else if (us_state == 2 && millis() - us_changeTime > 500) {
      
      servo_action.write(90);
      us_state = 3;
      us_changeTime = millis();
      Serial.println("State two");
    }
    else if (us_state == 3&& millis() - us_changeTime > 150) {
      servo_action.write(70);
      us_state = 4;
      us_changeTime = millis();
        Serial.println("State three");
    }
    else if (us_state == 4 && millis() - us_changeTime > 250) {
      
      servo_action.write(5);
      //delay(1000);
    us_state=5;
      //us_changeTime = 0;
       us_changeTime = millis();
       Serial.println("State four");
      

    }
    else  if (us_state==5 && millis() - us_changeTime > 500){
        us_state = 0;
      Serial.println("State five");
    
      input=0;
      }

       
   }
   else{
      servo_action.detach();
      servo_rot.detach();
      
    }

// drumstickL();











  /*


    if (RS485.available()==2){

      int incomingValue = RS485.read();

      values[currentValue++] = incomingValue;





      action=values[0];
      countryId= values[1];
      //angle=countryId;

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
        if (countryId==1){
        angle=10;
        }
        //Germany
        if (countryId==2){
        angle=25;
        }
        //Austria
        if (countryId==3){
        angle=45;
        }
        //Netherlands
        if (countryId==4){
        angle=65;
        }

        //China
        if (countryId==5){
        angle=100;
        }
        //Turkey
        if (countryId==6){
        angle=140;
        }
        //India
        if (countryId==7){
        angle=180;
        }


        if(angle != NULL){
          Serial.println(angle);

          if (action==0){


          servo_rot.write(angle);
          delay(1200);
          servo_action.write(0);
          delay(500);
          servo_action.write(65);

          }


        if(action==1){

          servo_rot.write(angle);
          delay(1200);
          servo_action.write(120);
          delay(500);
          servo_action.write(65);
          }
      }








      //delay(1000);
    }


  */

}

void drumstickL(){

  static char drum_state=0;
  static unsigned long drum_changeTime=0;
  //int full_cycle=1000/freq;


  
      if (drum_state==0 ){
        
        servo_action.write(75);
        drum_state=1;
        drum_changeTime=millis();
        
      }
    else if (drum_state==1&&millis()-drum_changeTime>100){
      //digitalWrite(pinNr,LOW);
       servo_action.write(100);
      drum_state=2;
    }
      else if (drum_state==2&&millis()-drum_changeTime>500){
          drum_state=0;
      }
  
}
