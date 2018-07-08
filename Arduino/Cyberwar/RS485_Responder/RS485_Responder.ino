#include "Arduino.h"

// Library to allow a Serial port on arbitrary pins
#include <SoftwareSerial.h>

// These are the pins we'll be talking to the RS485 device on
#define RS485rx		6 // RS485 Receive pin  (R0)
#define RS485Tx		7 // RS485 Transmit pin  (DI)
#define RS485inout	5 // RS485 Transmit or Receive status  (DE)
// connect  between DE and RE
// Connect the A's and the B's with the other boards 
// GND with arduion gnd and Vcc with 5v arduino
#define RS485Transmit	HIGH
#define RS485Receive	LOW
#define ledPin			13
#define baudRate		9600

// Define the RS485 object
SoftwareSerial RS485(RS485rx, RS485Tx);

// The data bytes we're sending or receiving
byte rxValue;
byte txValue01;
byte txValue02;
byte sending;

// -----------------------------------------------------------------
// SETUP         SETUP         SETUP         SETUP         SETUP
// -----------------------------------------------------------------
void setup()
{
  // Debugging window
  Serial.begin(9600);

  // Set modes for pins
  pinMode(ledPin, OUTPUT);
  pinMode(RS485inout, OUTPUT);

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
  // Is there something on the serial pin?
   
  if (RS485.available())
  {
    //char* input[2];
    //for(int i=0; i<2; i++){ //testing part
      //input[i] = Serial.read();
      //txValue = RS485.read();
    //}
    //txValue = RS485.read();   
   // Serial.print("helloddddd:");
   
   if (RS485.read()=='a'){
    
    Serial.print('a'); 
    delay(1);
    txValue01=RS485.read();
    delay(1);
    txValue02=RS485.read();
    delay(1);
    Serial.print(txValue01);
    Serial.print(txValue02);
    
    if (RS485.read()=='b')
    Serial.println('b'); 
    
    
   }
   
   //Serial.print(txValue); 

   
     

    // Turn on the on-board LED pin to show activity
    digitalWrite(ledPin, HIGH);

    // Set the direction pin to xmit (HIGH)
    digitalWrite(RS485inout, RS485Transmit);

    // This delay is REQUIRED for things to settle before transmission
    //delay(10);

    // Send back a modified value
    //RS485.write(RS485.read());

    // Wait for the transmission to complete.
    // This delay is dependent on the baud rate. To calculate:
    // delay = (baud rate / 10) * 2
    int bufferDelay = (baudRate / 10) * 2 + 100;
    delayMicroseconds(bufferDelay);

    // Set the RS485 back to receive
    digitalWrite(RS485inout, RS485Receive);

    // Turn off built in LED pin
    digitalWrite(ledPin, LOW);
  }
}
