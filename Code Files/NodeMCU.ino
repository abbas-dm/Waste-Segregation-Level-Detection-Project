/*======================================================================================*/
                                /*NODEMCU code*/
/*======================================================================================*/

/*Nodemcu code to connect with ThingSpeak cloud*/
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
int Dlevel,Slevel;

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Rajia786"; // your network SSID (name)
char pass[] = "@Rajia786@"; // your network password
//-------------------------------------------//

//----------- Channel Details -------------//
unsigned long Channel_ID = 1232280; // Channel ID
const int Field_number = 1; // Don't change
const int Field_number2 = 2; // Don't change
const char * WriteAPIKey = "O6HNG7EL0SX2O3MI"; // Your write API Key
// ----------------------------------------//

SoftwareSerial s(D6, D5); // RX and TX pins
SoftwareSerial s2(D3, D2); // RX and TX pins
WiFiClient client;

void setup(){
 Serial.begin(115200);
 s.begin(9600);
 s2.begin(9600);
 WiFi.mode(WIFI_STA);
 ThingSpeak.begin(client);
}
void loop(){
 Dlevel = 0;
 Slevel = 0;
 internet();
 get_value();
 upload();
}
void upload(){
 internet();
 ThingSpeak.setField(1, Dlevel);
 ThingSpeak.setField(2, Slevel);
 ThingSpeak.writeFields(Channel_ID, WriteAPIKey);
 Serial.println("Data Updated.");
}
void internet(){
 if (WiFi.status() != WL_CONNECTED){
   Serial.print("Attempting to connect to SSID: ");
   Serial.println(ssid);
   while (WiFi.status() != WL_CONNECTED){
     WiFi.begin(ssid, pass);
     Serial.print(".");
     delay(5000);
   }
   Serial.println("\nConnected.");
 }
}
void get_value(){
  if(s.available()){
    Dlevel = s.read();
    Serial.print("Level of Dry waste dustbin is :: ");
    Serial.println(Dlevel);
  }
  if(s2.available()){
    Slevel = s2.read();
    Serial.print("Level of Wet waste dustbin is :: ");
    Serial.println(Slevel);
  }
  delay(15000);
}
