
const int drumPinL = 3;
const int drumPinR = 5;

int shift = 50; // in percent of the Left Drumsick Frequency/Perdiod
int R_offset=0;

int frequencyL=4; //in Hz approx range: 1 - 7
int frequencyR=1;

int on_timeL=10; // in ms needs to be experimented
int on_timeR= 300;
bool first=1;
unsigned long lastDrumHitR=0;

//void drumstickL(int pinNr, int freq, int on_time, bool on=1);
//void drumstickR(int pinNr, int freq, int on_time, bool on=1);

float tempo=1;



void setup(){
Serial.begin(9600);
pinMode(drumPinL, OUTPUT);
pinMode(drumPinR, OUTPUT);

R_offset = map(shift,0,100,0,1000/frequencyL);
Serial.print ("R_offset:  ");
Serial.print (R_offset);
}


void loop(){

  //frequencyR=frequencyL; // synchronizer
  while (Serial.available() >0){
  tempo=Serial.parseFloat();}
  drumstickL(drumPinL, frequencyL, on_timeL, true,tempo);

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
        digitalWrite(pinNr,HIGH);
        drum_state=1;
        drum_changeTime=millis();
        
      }
    else if (drum_state==1&&millis()-drum_changeTime>on_time){
      digitalWrite(pinNr,LOW);
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
      if (drum_state==0 ){
        digitalWrite(pinNr,HIGH);
        drum_state=1;
        drum_changeTime=millis();
        
        //lastDrumHitR=millis();
      }
    else if (drum_state==1&&millis()-drum_changeTime>on_time){
      digitalWrite(pinNr,LOW);
      drum_state=2;
    }
      else if (drum_state==2&&millis()-drum_changeTime>full_cycle * tempo){
          drum_state=0;
      }
  }
}
