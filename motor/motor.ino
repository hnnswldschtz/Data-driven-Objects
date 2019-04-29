
const int drumPinL = 8;
const int drumPinR = 9;

const int errorPin = 10;

bool error = 0;

int shift = 50; // in percent of the Left Drumsick Frequency/Perdiod
int R_offset = 0;

float frequencyL = 1.0; //in Hz approx range: 1 - 7
float frequencyR = 1.0;

int on_time ; // in ms needs to be experimented

int on_long = 100;

//float on_short = 5;


int counterR ;
int counterL ;

unsigned long lastDrumHitL = 0;




float a;

int b;


float delta;

float prevVal;

bool interp=0; 



void setup() {
  Serial.begin(9600);
  Serial.setTimeout(15);
  pinMode(drumPinL, OUTPUT);
  pinMode(drumPinR, OUTPUT);
  pinMode(errorPin, OUTPUT);

}



void loop() {

  if (Serial.available()) {

    if (Serial.read() == 'a') {
      
      

      a = Serial.parseFloat(); //value between 1-5 ms;
     

    

     


      
      if (a == -1) {
      error=1;
      digitalWrite(errorPin, HIGH);
      Serial.println(a);
      } else {
        
        error=0;
        digitalWrite(errorPin, LOW);

        
        frequencyL = a;
        frequencyR = a;

        
        Serial.println(a);

        if (Serial.read() == 'b')

        {
          b = Serial.parseInt(); //value between 50-100 ms;
          Serial.println(b);
          on_long = b;
        }

      }
    }


  }



  R_offset = (1000 / frequencyL) / 2;
  //Serial.print ("R_offset:  ");
  // Serial.println (R_offset);










 
    drumstickL(drumPinL, frequencyL, on_long);
    drumstickR(drumPinR, frequencyR, on_long);
 




}







void drumstickL(int pinNr, float freq, int on_time) {

  static char drum_state = 0;
  static unsigned long drum_changeTime = 0;
  int full_cycle = 1000 / freq;
  //Serial.println(full_cycle);

  if (drum_state == 0 ) {
    digitalWrite(pinNr, HIGH);

    drum_state = 1;
    drum_changeTime = millis();
    lastDrumHitL = drum_changeTime;

    


  }
  else if (drum_state == 1 && millis() - drum_changeTime > on_time) {
    digitalWrite(pinNr, LOW);

    drum_state = 2;

  }
  else if (drum_state == 2 && millis() - drum_changeTime > full_cycle ) {
    drum_state = 0;

    
    
  }

}



void drumstickR(int pinNr, float freq, int on_time) {

  static char drum_state = 0;
  static unsigned long drum_changeTime = 0;
  int full_cycle = 1000 / freq;


  if (drum_state == 0  ) {
    digitalWrite(pinNr, HIGH);

    drum_state = 1;
    drum_changeTime = lastDrumHitL + R_offset;

    
  }
  else if (drum_state == 1 && millis() - drum_changeTime > on_time) {
    digitalWrite(pinNr, LOW);
    drum_state = 2;
  }

  else if (drum_state == 2 && millis() - drum_changeTime > full_cycle ) {
    drum_state = 0;

    

    
  }

}




float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
