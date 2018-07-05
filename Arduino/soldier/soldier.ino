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
int values[] = {0,0};




// Define the RS485 object
//ftwareSerial RS485(RS485rx, RS485Tx);


void setup() 
{ 
  servo_rot.attach(10); 
  servo_action.attach(11);

  servo_action.write(0);
  servo_rot.write(0);
  
  Serial.begin(9600);

  //Mode(RS485inout, OUTPUT);

  // Set RS485 device to read initially
  //gitalWrite(RS485inout, RS485Receive);

  
  //RS485.begin(9600);



  
  
  
  
  
} 


void loop() 
{ 


  servo_action.write(75);
  delay(500);
  servo_action.write(110);

   delay(150);
  servo_action.write(75);
  delay(500);
  servo_action.write(0);
   delay(1000);

   
  
//  if (Serial.available()>0){
//int angle= Serial.parseInt();
//servo_action.write(angle);
//Serial.println(angle);
//    
//  }
/*
 * 
  
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

