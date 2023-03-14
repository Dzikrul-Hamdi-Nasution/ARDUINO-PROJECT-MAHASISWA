#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>
#include <TinyGPS++.h>
#include <WiFi.h>
//#include <SoftwareSerial.h>

TinyGPSPlus gps;
#define FIREBASE_HOST "monitoring-gps-tracker-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "fTPjNDeA2SIQeLQDOze0sHqoDrrXoPW0KRtBtFSg"
#define WIFI_SSID "Server Project"
#define WIFI_PASSWORD "Salamproject2022"

String latitude, longtitude;
static const int RXPin = 14, TXPin = 12;
static const uint32_t GPSBaud = 9600;
//SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  //ss.begin(GPSBaud);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  //Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //Serial.println(F("Ublox Neo-7N GPS Module Test"));
  //Firebase.setString("tes", "oke");
}

void loop() {

  delay(300);


  while (Serial.available() > 0)
    if (gps.encode(Serial.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    latitude = String(gps.location.lat(), 6);
    Firebase.setString("lat", latitude);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    longtitude = String(gps.location.lng(), 6);
    Firebase.setString("long", longtitude);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}
