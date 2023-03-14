#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#define roda_kiri_A 8
#define roda_kiri_B 9
#define roda_kanan_A 10
#define roda_kanan_B 11
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
SoftwareSerial BT(2, 3);
static const int RXPin = 15, TXPin = 14;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
String data = "";
float latitude, longtitude;
float headingDegrees;
void setup() {
  // put your setup code here, to run once:
  BT.begin(9600);
  Serial.begin(9600);
  ss.begin(9600);
  BT.println("uji coba");
  Serial.println("uji coba");
  pinMode(roda_kiri_A, OUTPUT);
  pinMode(roda_kiri_B, OUTPUT);
  pinMode(roda_kanan_A, OUTPUT);
  pinMode(roda_kanan_B, OUTPUT);

  delay(1000);
}



void loop() {

  BT.listen();
  // put your main code here, to run repeatedly:
  if (BT.available() > 0) {
    char c = BT.read();
    if (c != '/') {
      data += c;
    }
    else {
      Serial.println(data);
      data = "";
      BT.flush();
    }
  }



}
