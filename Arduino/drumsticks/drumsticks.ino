#include    <Servo.h>      //Servo library
 
 
Servo servo_0;
Servo servo_1;//initialize a servo object for the connected servo  
const int drumPinL = 3;
const int drumPinR = 5;

int shift = 50; // in percent of the Left Drumsick Frequency/Perdiod
int R_offset=0;

int frequencyL=4; //in Hz approx range: 1 - 7
int frequencyR=1;

int on_timeL=100; // in ms needs to be experimented
int on_timeR= 100;
bool first=1;
unsigned long lastDrumHitR=0;

//void drumstickL(int pinNr, int freq, int on_time, bool on=1);
//void drumstickR(int pinNr, int freq, int on_time, bool on=1);
// TEST TEST TEST TEST 

float tempo=1;
int a;



void setup(){
Serial.begin(9600);
Serial.setTimeout(20);
//pinMode(drumPinL, OUTPUT);
//pinMode(drumPinR, OUTPUT);

servo_0.attach(3); 
servo_1.attach(5); 

R_offset = map(shift,0,100,0,1000/frequencyL);
Serial.print ("R_offset:  ");
Serial.print (R_offset);
}



float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop(){

  //frequencyR=frequencyL; // synchronizer
//  while (Serial.available() >0){
//  tempo=Serial.parseFloat();}


  if (Serial.read() == 'a') {
    // delay(1);
    a = Serial.parseInt();
    //Serial.println(a);
if (a>1){
     tempo= mapfloat(a,0,100,2.0,0.7);
  Serial.print("a: ");
  Serial.println(a);
  Serial.print("tempo : ");
  Serial.println(tempo);
}
   
  }

 //Serial.print(a);

 
  drumstickL(drumPinL, frequencyL, on_timeL, true,tempo);
  //Serial.println(tempo);

  //if (millis() - lastDrumHitR>R_offset) {
    drumstickR(drumPinR, frequencyR, on_timeR, true, tempo);
   // lastDrumHitR=millis();
 // }

}





void drumstickL(int pinNr, int freq, int on_time, bool on,float tempo){

  static char drum_state=0;
  static unsigned long drum_changeTime=0;
  int full_cycle=1000/freq;


  if (on){
      if (drum_state==0 ){
        //digitalWrite(pinNr,HIGH);
        servo_0.write(180);
        drum_state=1;
        drum_changeTime=millis();
        
      }
    else if (drum_state==1&&millis()-drum_changeTime>on_time){
      //digitalWrite(pinNr,LOW);
       servo_0.write(140);
      drum_state=2;
    }
      else if (drum_state==2&&millis()-drum_changeTime>full_cycle * tempo){
          drum_state=0;
      }
  }
}


void drumstickR(int pinNr, int freq, int on_time, bool on, float tempo){

  static char drum_state=0;
  static unsigned long drum_changeTime=0;
  int full_cycle=1000/freq;


  if (on){
      if (drum_state==0 && millis() - lastDrumHitR>R_offset){
        //digitalWrite(pinNr,HIGH);
         servo_1.write(180);
        drum_state=1;
        drum_changeTime=millis();
        
        lastDrumHitR=millis();
      }
    else if (drum_state==1&&millis()-drum_changeTime>on_time){
      //digitalWrite(pinNr,LOW);
      servo_1.write(140);
      drum_state=2;
    }
      else if (drum_state==2&&millis()-drum_changeTime>full_cycle * tempo){
          drum_state=0;
      }
  }
}
