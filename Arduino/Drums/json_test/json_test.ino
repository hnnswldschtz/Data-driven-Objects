#include <ArduinoJson.h>

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



WiFiClient http;





Servo servo01;
//init sensors' values 
float t12;
float t7;

static char respBuffer[1024];

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





//////////////////////////////////////////LOOP////////////////////////////////
void loop() {

  //repeat every 10 seconds
  if (millis()-oldTime>5000){
  // wait for WiFi connection
  if (WiFi.status() == WL_CONNECTED) {

    
    // configure server and url

    const char request[] = 
    "GET /example.json HTTP/1.1\r\n" 
    "User-Agent: ESP8266/0.1\r\n"
    "Accept: */*\r\n"
    "Host: arduinojson.org\r\n"
    "Connection: close\r\n"
    "\r\n";
    
    http.connect("arduinojson.org",80); 
    http.print(request);
    http.flush();
    //delay(1000);
    uint16_t index=0;
    while(http.connected())
    {
      //Serial.println("Client Connected");
      if(http.available())
      {
        respBuffer[index++]=http.read();
        //delay(1);
      }
    }
    http.stop();
    char* json = strchr(respBuffer,'{');

    DynamicJsonBuffer jBuffer;
    JsonObject& root = jBuffer.parseObject(json);
    String  id= root["sensor"];
    Serial.print("Sensor is: ");
    Serial.println (id);
    
    


       
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
    




  if (millis()-delaytimeH> 150){
    digitalWrite(LED_BUILTIN, HIGH); 
    //digitalWrite(4, HIGH); 
    delaytimeH=millis();
     if (millis()-delaytimeL> 200){
      digitalWrite(LED_BUILTIN, LOW); 
      //digitalWrite(4, LOW); 
      delaytimeL=millis();
      } 

  }
  
}

float getVal(String id,String payload){

        int ID_Index = payload.indexOf("TDRM."+id+"<");
        int breakIndex = payload.indexOf("<b>",ID_Index);
        int valIndex = breakIndex+3;
        int valEndIndex = payload.indexOf("</b>",breakIndex);
        int valLength = valEndIndex-valIndex;
       
        String val="";
        for (int i=valIndex;i<valEndIndex;i++){
          val+=payload.charAt(i);
        }

        Serial.print("TDRM."+id+" value is: ");
        Serial.println(val);

        float floatVal=val.toFloat();
        float floatPeriod=linear(floatVal,0,0.466,1000,100);
        
        Serial.print("Delay: ");
        Serial.print(floatPeriod);
        Serial.println(" ms");

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

   




