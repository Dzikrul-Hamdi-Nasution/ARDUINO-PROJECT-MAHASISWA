#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>


float latitude, longitude;
static const int RXPin = 4, TXPin = 5;


SoftwareSerial ss(RXPin, TXPin);



#define FIREBASE_HOST "monitoring-gps-tracker-default-rtdb.firebaseio.com"
#define WIFI_SSID "Server Beta"
#define WIFI_PASSWORD "Master75wew"

unsigned int move_index = 1;


void setup()
{
  Serial.begin(9600);
  //Serial.println();
  ss.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Firebase.begin(FIREBASE_HOST);
  //timer.setInterval(5000L, checkGPS);
}

void loop()
{
  while (ss.available() > 0)
  {
    displayInfo();
    cek_database();
  }



}


void displayInfo()
{
  char type = ss.read();
  if (type == 'A') {
    float lat = ss.parseFloat();
    latitude = lat;
  }
  if (type == 'B') {
    float longi = ss.parseFloat();
    longitude = longi;
  }

  Serial.print("LAT:  ");
  Serial.println(latitude, 6);
  Serial.print("LONG: ");
  Serial.println(longitude, 6);

  Serial.println();
}


void cek_database() {
  Firebase.setString("lat", String(latitude, 6));
  Firebase.setString("long", String(longitude, 6));

}

