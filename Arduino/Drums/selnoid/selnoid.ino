//#include <DIO2.h>
//#include "arduino2.h"
#include    <Servo.h>      //Servo library
#include "Arduino.h"







//############################################################### setup ######################################################
void setup() {
  
  Serial.begin(9600);
  Serial.setTimeout(20);
  //pinMode2(5, OUTPUT);
  //pinMode2(LED_BUILTIN, OUTPUT);
}





// init input variables

int  a;
int  b;

int  delay_a;
int  delay_b;




// init delay variables


unsigned long delaytimeH_1 = 0;
unsigned long delaytimeL_1 = 0;

unsigned long delaytimeL_2 = 0;
unsigned long delaytimeH_2 = 0;






//  Loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooop 
void loop() {


// Recive input and store in delay variables
  if (Serial.read() == 'a') {
    // delay(1);
    a = Serial.parseInt();
    //Serial.println(a);

    if (a > 1)
      delay_a = a;
    //Serial.println(delay_a);
  }

  if (Serial.read() == 'b') {
    //delay(1);
    b = Serial.parseInt();
    if (b > 1)
      delay_b = b;
    //Serial.println(delay_b);
  }







//############################################################ ----- Movement ----- ############################################################################


// Selniod 01 code

  if (millis() - delaytimeH_1 > 50) {
    analogWrite(5, 0);
    // analogWrite(LED_BUILTIN, 0);
    delaytimeH_1 = millis();

    if (millis() - delaytimeL_1 > delay_a) {
      Serial.println(delay_a);
      analogWrite(5, 255);
      //analogWrite(LED_BUILTIN, 255);
      delaytimeL_1 = millis();
    }
  }





// Selnoid 02 code

  if (millis() - delaytimeH_2 > 50) {
    analogWrite(3, 0);
    //analogWrite(LED_BUILTIN, 0);
    delaytimeH_2 = millis();

    if (millis() - delaytimeL_2 > delay_b) {
      Serial.println(delay_a);
      analogWrite(3, 255);
      //analogWrite(LED_BUILTIN, 255);
      delaytimeL_2 = millis();
    }
  }





}
