#include <Arduino.h>

#include <WiFi.h>


#include <HTTPClient.h>

#include <WiFiClientSecure.h>
int counter = 0;

float freq = 1;
float on_time;


unsigned long lastUpdate = 0;

int freqIndex = 0;
int on_timeIndex = 0;

String payload = "";



int freqList[] = {10, 18, 14, 20};
int on_timeList [] = { 23, 35, 5, 22};


int a;

float first_valfloat;
float second_valfloat;



const char* ssid = "KDG-7F7BC_RPT";
const char* password = "AJscwWMFKa0K";

const char* rootCACertificate = \
                                "-----BEGIN CERTIFICATE-----\n" \
                                "MIIF6TCCA9GgAwIBAgIQBeTcO5Q4qzuFl8umoZhQ4zANBgkqhkiG9w0BAQwFADCB\n" \
                                "iDELMAkGA1UEBhMCVVMxEzARBgNVBAgTCk5ldyBKZXJzZXkxFDASBgNVBAcTC0pl\n" \
                                "cnNleSBDaXR5MR4wHAYDVQQKExVUaGUgVVNFUlRSVVNUIE5ldHdvcmsxLjAsBgNV\n" \
                                "BAMTJVVTRVJUcnVzdCBSU0EgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMTQw\n" \
                                "OTEyMDAwMDAwWhcNMjQwOTExMjM1OTU5WjBfMQswCQYDVQQGEwJGUjEOMAwGA1UE\n" \
                                "CBMFUGFyaXMxDjAMBgNVBAcTBVBhcmlzMQ4wDAYDVQQKEwVHYW5kaTEgMB4GA1UE\n" \
                                "AxMXR2FuZGkgU3RhbmRhcmQgU1NMIENBIDIwggEiMA0GCSqGSIb3DQEBAQUAA4IB\n" \
                                "DwAwggEKAoIBAQCUBC2meZV0/9UAPPWu2JSxKXzAjwsLibmCg5duNyj1ohrP0pIL\n" \
                                "m6jTh5RzhBCf3DXLwi2SrCG5yzv8QMHBgyHwv/j2nPqcghDA0I5O5Q1MsJFckLSk\n" \
                                "QFEW2uSEEi0FXKEfFxkkUap66uEHG4aNAXLy59SDIzme4OFMH2sio7QQZrDtgpbX\n" \
                                "bmq08j+1QvzdirWrui0dOnWbMdw+naxb00ENbLAb9Tr1eeohovj0M1JLJC0epJmx\n" \
                                "bUi8uBL+cnB89/sCdfSN3tbawKAyGlLfOGsuRTg/PwSWAP2h9KK71RfWJ3wbWFmV\n" \
                                "XooS/ZyrgT5SKEhRhWvzkbKGPym1bgNi7tYFAgMBAAGjggF1MIIBcTAfBgNVHSME\n" \
                                "GDAWgBRTeb9aqitKz1SA4dibwJ3ysgNmyzAdBgNVHQ4EFgQUs5Cn2MmvTs1hPJ98\n" \
                                "rV1/Qf1pMOowDgYDVR0PAQH/BAQDAgGGMBIGA1UdEwEB/wQIMAYBAf8CAQAwHQYD\n" \
                                "VR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMCIGA1UdIAQbMBkwDQYLKwYBBAGy\n" \
                                "MQECAhowCAYGZ4EMAQIBMFAGA1UdHwRJMEcwRaBDoEGGP2h0dHA6Ly9jcmwudXNl\n" \
                                "cnRydXN0LmNvbS9VU0VSVHJ1c3RSU0FDZXJ0aWZpY2F0aW9uQXV0aG9yaXR5LmNy\n" \
                                "bDB2BggrBgEFBQcBAQRqMGgwPwYIKwYBBQUHMAKGM2h0dHA6Ly9jcnQudXNlcnRy\n" \
                                "dXN0LmNvbS9VU0VSVHJ1c3RSU0FBZGRUcnVzdENBLmNydDAlBggrBgEFBQcwAYYZ\n" \
                                "aHR0cDovL29jc3AudXNlcnRydXN0LmNvbTANBgkqhkiG9w0BAQwFAAOCAgEAWGf9\n" \
                                "crJq13xhlhl+2UNG0SZ9yFP6ZrBrLafTqlb3OojQO3LJUP33WbKqaPWMcwO7lWUX\n" \
                                "zi8c3ZgTopHJ7qFAbjyY1lzzsiI8Le4bpOHeICQW8owRc5E69vrOJAKHypPstLbI\n" \
                                "FhfFcvwnQPYT/pOmnVHvPCvYd1ebjGU6NSU2t7WKY28HJ5OxYI2A25bUeo8tqxyI\n" \
                                "yW5+1mUfr13KFj8oRtygNeX56eXVlogMT8a3d2dIhCe2H7Bo26y/d7CQuKLJHDJd\n" \
                                "ArolQ4FCR7vY4Y8MDEZf7kYzawMUgtN+zY+vkNaOJH1AQrRqahfGlZfh8jjNp+20\n" \
                                "J0CT33KpuMZmYzc4ZCIwojvxuch7yPspOqsactIGEk72gtQjbz7Dk+XYtsDe3CMW\n" \
                                "1hMwt6CaDixVBgBwAc/qOR2A24j3pSC4W/0xJmmPLQphgzpHphNULB7j7UTKvGof\n" \
                                "KA5R2d4On3XNDgOVyvnFqSot/kGkoUeuDcL5OWYzSlvhhChZbH2UF3bkRYKtcCD9\n" \
                                "0m9jqNf6oDP6N8v3smWe2lBvP+Sn845dWDKXcCMu5/3EFZucJ48y7RetWIExKREa\n" \
                                "m9T8bJUox04FB6b9HbwZ4ui3uRGKLXASUoWNjDNKD/yZkuBjcNqllEdjB+dYxzFf\n" \
                                "BT02Vf6Dsuimrdfp5gJ0iHRc2jTbkNJtUQoj1iM=\n" \
                                "-----END CERTIFICATE-----\n";




void setup() {

  Serial.begin(9600);
  // Serial.setDebugOutput(true);

  //  Serial.println();
  //  Serial.println();
  //  Serial.println();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
    counter++;
    if (counter >= 30) { //after 30 seconds timeout - reset board
      ESP.restart();
    }

    Serial.print('a');
    Serial.print(-1);
    //Serial.print("wifi Dissconnected");
  }


}

void loop() {


  if (WiFi.status() == WL_CONNECTED) { //if we are connected to Eduroam network
    counter = 0; //reset counter
    //Serial.println("Wifi is still connected with IP: ");
    //Serial.println(WiFi.localIP());   //inform user about his IP address
  } else if (WiFi.status() != WL_CONNECTED) { //if we lost connection, retry
    WiFi.begin(ssid, password);
  }
  while (WiFi.status() != WL_CONNECTED) { //during lost connection, print dots
    //delay(500);
    Serial.print('a');
    Serial.print(-1);
    //Serial.print("wifi Dissconnected");
    counter++;
    if (counter >= 30) { //30 seconds timeout - reset board
      ESP.restart();
    }
  }
  //************************************Fetch*******************************
  //delay(10000);
  if (millis() - lastUpdate > 10000) {
    lastUpdate = millis();
    HTTPClient http;

    //Serial.print("[HTTPS] begin...\n");
    if (http.begin("https://tdrm.fiff.de/data/diagram/grab.php?stations=" + String(freqList[freqIndex]) + "," + String(on_timeList[on_timeIndex]))) { // HTTPS

      //Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        //Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          payload = http.getString();
          //String timeVal = payload.substring(0, payload.indexOf(";"));

          if (station_on(freqList[freqIndex])) {
            first_valfloat = getVal(freqList[freqIndex]).toFloat();

            //Serial.print("Current Station is ON: ");
            //Serial.println(freqList[freqIndex]);

          }
          else {
            if (freqIndex >= 3) { //if last station in list is reached, return to first station
              freqIndex = 0;
            }
            else {
              //Serial.print("Current Station is OFF: ");
              //Serial.println(freqList[freqIndex]);
              freqIndex++;

            }

          }


          if (station_on(on_timeList[on_timeIndex])) {
            second_valfloat = getVal(on_timeList[on_timeIndex]).toFloat();
          }
          else {
            if (on_timeIndex >= 3) {  //if last station in list is reached, return to first station
              on_timeIndex = 0;
            } else on_timeIndex++;
          }





          freq = mapfloat(first_valfloat, 0.0, 0.4, 5.0, 6.0);
          on_time = mapfloat(second_valfloat, 0.0, 0.4, 30.0, 80.0);





          Serial.print('a');
          Serial.print(freq);
          Serial.print('b');
          Serial.print(on_time);


        } else {
          Serial.print('a');
          Serial.print(-1);
        }
      } else {

        Serial.print('a');
        Serial.print(-1);
        //Serial.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {

      Serial.print('a');
      Serial.print(-1);
      //Serial.printf("[HTTPS] Unable to connect\n");
    }



    //Serial.println();
    //Serial.println("Waiting 10s before the next round...");

  }





}



bool station_on(int stationId) {

  int idColonIndex = payload.indexOf(";" + String(stationId));
  int idCommaIndex = payload.indexOf(',', idColonIndex + 1);
  int flagCommaIndex = payload.indexOf(',', idCommaIndex + 1);

  String flag = payload.substring(idCommaIndex + 1, flagCommaIndex);

  if (flag == "1") {
    return true;
  }
  else return false;

}





String getVal(int stationId)
{

  String val;
  int idColonIndex = payload.indexOf(";" + String(stationId));
  int idCommaIndex = payload.indexOf(',', idColonIndex + 1);
  int flagCommaIndex = payload.indexOf(',', idCommaIndex + 1);
  int countsCommaIndex = payload.indexOf(',', flagCommaIndex + 1);

  int second_idColonIndex = payload.indexOf(';', idColonIndex + 1);

  if (second_idColonIndex == -1) {
    val = payload.substring(countsCommaIndex + 1);
  } else {
    val = payload.substring(countsCommaIndex + 1, second_idColonIndex);
  }

  return val;
}





float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
