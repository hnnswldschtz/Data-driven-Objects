#include "Arduino.h"

// Library to allow a Serial port on arbitrary pins
#include <SoftwareSerial.h>

// These are the pins we'll be talking to the RS485 device on
#define RS485rx    6 // RS485 Receive pin  (RO)
#define RS485Tx   7 // RS485 Transmit pin  (DI)
#define RS485inout  5 // RS485 Transmit or Receive status (DE)
// Connect a cable betweeen DE and RE
// Connect the A's and the B's with the other boards 

// Connect the A's and the B's with the other boards 


#define RS485Transmit HIGH
#define RS485Receive  LOW
#define ledPin      13
#define baudRate    9600

// Define the RS485 object
SoftwareSerial RS485(RS485rx, RS485Tx);

// The data bytes we're sending or receiving
byte rxValue;
byte txValue;

byte data[]= 
{1 , 5,
3 , 5,
5 , 2,
2 , 1,
1 , 12,
4 , 1,
5 , 12,
3 , 1,
2 , 1,
3 , 1,
5 , 1,
1 , 12,
6 , 1,
2 , 1,
5 , 3,
1 , 12,
1 , 5,
2 , 1,
3 , 5,
1 , 4,
5 , 11,
1 , 11,
5 , 1,
5 , 2,
7 , 2,
2 , 1,
4 , 2,
1 , 12,
2 , 1,
11 , 1,
5 , 1,
2 , 1,
3 , 1,
8 , 1,
2 , 1,
2 , 1,
6 , 1,
8 , 1,
2 , 1,
6 , 5,
2 , 1,
2 , 1,
1 , 2,
3 , 1,
6 , 1,
1 , 12,
6 , 1,
8 , 1,
1 , 5,
1 , 5,
1 , 12,
1 , 10,
2 , 1,
1 , 12,
2 , 1,
5 , 1,
2 , 1,
2 , 1,
12 , 1,
1 , 3,
10 , 1,
2 , 1,
2 , 1,
2 , 1,
2 , 1,
6 , 0,
0 , 5,
0 , 9,
2 , 0,
1 , 6,
0 , 5,
2 , 5,
3 , 0,
1 , 0,
0 , 5,
6 , 0,
0 , 5,
2 , 1,
6 , 0,
6 , 0,
2 , 1,
2 , 1,
3 , 0,
7 , 0,
0 , 10,
1 , 0,
7 , 0,
3 , 0,
7 , 0,
0 , 10,
6 , 0,
7 , 0,
4 , 0,
10 , 0,
6 , 0,
6 , 0,
7 , 0,
0 , 10,
6 , 0,
7 , 0,
0 , 4,
7 , 0,
2 , 0,
7 , 0,
7 , 0,
1 , 5,
8 , 0,
10 , 0,
1 , 0,
7 , 0,
7 , 0,
3 , 0,
7 , 0,
7 , 0,
7 , 0,
11 , 0,
7 , 2,
7 , 0,
10 , 0,
2 , 0,
1 , 10,
10 , 0,
7 , 0,
0 , 2,
2 , 0,
0 , 5,
0 , 1,
8 , 0,
0 , 7,
0 , 5,
0 , 10,
1 , 0,
0 , 5,
0 , 5,
0 , 5,
0 , 1,
7 , 0,
6 , 0,
7 , 0,
1 , 9,
7 , 0,
7 , 0,
3 , 0,
3 , 0,
7 , 0,
10 , 0,
7 , 0,
7 , 0,
1 , 0,
5 , 0,
7 , 0,
4 , 0,
0 , 5,
7 , 0,
11 , 0,
7 , 0,
2 , 0,
1 , 0,
0 , 5,
7 , 0,
7 , 0,
1 , 0,
7 , 0,
0 , 6,
7 , 0,
7 , 0,
0 , 2,
0 , 10,
6 , 0,
7 , 0,
7 , 0,
1 , 0,
7 , 0,
7 , 0,
6 , 0,
7 , 0
  };

// -----------------------------------------------------------------
// SETUP         SETUP         SETUP         SETUP         SETUP
// -----------------------------------------------------------------
void setup() /****** SETUP: RUNS ONCE ******/
{
  // Debugging window
  Serial.begin(9600);

  // Set modes for pins
  pinMode(ledPin, OUTPUT);
  pinMode(RS485inout, OUTPUT);

  // Ensure the on-board LED is off
  digitalWrite(ledPin, HIGH);

  // Set RS485 device to read initially
  digitalWrite(RS485inout, RS485Receive);

  // Set the baud rate. The longer the wire the slower you should
  // set the transmission rate. Anything here:
  // 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250,
  // 38400, 57600, and 115200
  // MUST BE THE SAME AS THE SENDER UNIT!
  RS485.begin(9600);
}

// -----------------------------------------------------------------
// LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP
// -----------------------------------------------------------------

void loop()
{
 
  
  
  //String teststring =  String('a');
  //int val1=0;
  //int val2=5;
  //byte teststring[] = {val1, val2}; // Serial Communication is easy!";
  //Serial.write(12);
  digitalWrite(RS485inout, RS485Transmit);
  int i; 
  int j=0;

  
  for (i = 0; i < 352; i++) {

  
  if (j==0){
  RS485.write('a');
  //delay(5);
  
  }
  j++;
  RS485.write(data[i]);
 //delay(5);
  
  if (j==2){
  RS485.write('b');
  delay(100);
  
  j=0;
  }
  

  
  
  }
  
  
  
}
