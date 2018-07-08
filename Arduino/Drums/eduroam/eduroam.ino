#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

extern "C" {
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
}

ESP8266WiFiMulti WiFiMulti;



static const char* ssid = "eduroam";

static u8 ent_username[] = "mgast03";
static u8 ent_password[] = "D4t4Dr1v3n0bj3ct$";
HTTPClient http;



Servo servo01;
//init sensors' values 
int  t12;
int t7;

void setup() {
  //servo01.attach(4); 
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  
 wifi_station_disconnect();
 wifi_station_clear_enterprise_identity();
 wifi_station_clear_enterprise_username();
 wifi_station_clear_enterprise_password();
   
 wifi_set_opmode(STATION_MODE);
 
  struct station_config stationConf;


  memset(&stationConf, 0, sizeof(stationConf));
  strcpy((char*)stationConf.ssid, ssid);

  wifi_station_set_config(&stationConf);
  if(wifi_station_set_config(&stationConf))
    Serial.println("Config success");
  else Serial.println("Config error");

//   // switch to WPA2 Enterprise 
   wifi_station_set_wpa2_enterprise_auth(1); 


   
   if(wifi_station_set_enterprise_identity(ent_username, strlen((char*)ent_username))!=0){
    Serial.println("username set fail\r\n");
  }
  if(wifi_station_set_enterprise_username(ent_username, strlen((char*)ent_username))!=0){
    Serial.println("username set fail\r\n");
  }
//
  if(wifi_station_set_enterprise_password(ent_password, strlen((char*)ent_password))!=0){
    Serial.println("password set fail\r\n");
  }
  
  if(!wifi_station_connect()){
    Serial.println("connect fail\r\n");
  }
   
   Serial.println("trying to connect...");

   delay(5000);
  
  

}

unsigned long oldTime=0;
unsigned long delaytimeH=0;
unsigned long delaytimeL=0;
String payload="";


void loop() {

  //repeat every 10 seconds
  if (millis()-oldTime>5000){
  // wait for WiFi connection
  if (WiFi.status() == WL_CONNECTED) {

    
    // configure server and url
    http.begin("http://tdrm.fiff.de/data/"); 

    //Serial.println("Refreshing...");
    // start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been sent and Server response header has been handled
      // file found at server

      //Serial.println("Http code more than 0");

      
      if (httpCode == HTTP_CODE_OK) {
       payload = http.getString();
       //Serial.println("Http code ok");
       t12=getVal("12",payload);
       t7=getVal("7",payload);
       Serial.print('a');
       Serial.print(t12);
       Serial.print('b');
       Serial.print(t7);

       
       }
    } else {
      //Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  else{
    Serial.println(WiFi.status());
    delay(2000);
    Serial.println("Not connected");
    if (WiFi.status()==WL_NO_SSID_AVAIL)
      Serial.println("So ssid");
    }
  
  oldTime=millis();
  }
    
//    servo01.write(180);       //command to rotate the servo to the specified angle
//    delay(t12);
//    servo01.write(150);       //command to rotate the servo to the specified angle
//    delay(100);



  if (millis()-delaytimeH> 150){
    digitalWrite(LED_BUILTIN, HIGH); 
    //digitalWrite(4, LOW); 
    delaytimeH=millis();
     if (millis()-delaytimeL> t12){
      //Serial.println(t12);
      digitalWrite(LED_BUILTIN, LOW); 
     // digitalWrite(4, HIGH); 
      delaytimeL=millis();
      } 

  }
  
}

int getVal(String id,String payload){

        int ID_Index = payload.indexOf("TDRM."+id+"<");
        int breakIndex = payload.indexOf("<b>",ID_Index);
        int valIndex = breakIndex+3;
        int valEndIndex = payload.indexOf("</b>",breakIndex);
        int valLength = valEndIndex-valIndex;
       
        String val="";
        for (int i=valIndex;i<valEndIndex;i++){
          val+=payload.charAt(i);
        }

        //Serial.print("TDRM."+id+" value is: ");
        //Serial.println(val);

        float floatVal=val.toFloat();
        int floatPeriod=linear(floatVal,0,0.466,0,100);
        
       // Serial.print("Delay: ");
        //Serial.print(floatPeriod);
        //Serial.println(" ms");

        return floatPeriod;
}

float linear(float i, float imin, float imax, float omin, float omax)
{
  if (i < imin) {i = imin;}
  if (i > imax) {i = imax;}
  float o = ((omax-omin)*((i-imin)/(imax-imin))+omin);
  return o;
}

//for reference:
    //typedef enum {
    //    WL_NO_SHIELD = 255,   // for compatibility with WiFi Shield library
    //    WL_IDLE_STATUS = 0,
    //    WL_NO_SSID_AVAIL = 1,
    //    WL_SCAN_COMPLETED = 2,
    //    WL_CONNECTED = 3,
    //    WL_CONNECT_FAILED = 4,
    //    WL_CONNECTION_LOST = 5,
    //    WL_DISCONNECTED = 6
    //} wl_status_t;

   




