#include <Wire.h>
#include "DS3231.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
RTClib RTC;
int jam, menit, detik, tahun, bulan, hari;
int sensorPin_1 = A0;
int sensorPin_2 = A1;
int sensorPin_3 = A2;
int sensorValue_1, sensorValue_2, sensorValue_galon;

int relay_pompa = 9;
int relay_ultrasonic = 8;
int menit_saat_ini, kunci;
String status_tanah, status_air;
String dataIn;
String dt[10];
int i, kunci_waktu;
boolean parsing = false;

int jam_pagi, jam_sore;
int lembap = 5;
int tangki = 4;

void setup () {
  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin();
  pinMode(relay_pompa, OUTPUT);
  pinMode(relay_ultrasonic, OUTPUT);
  digitalWrite(relay_pompa, HIGH);
  digitalWrite(relay_ultrasonic, HIGH);
  pinMode(lembap, OUTPUT);
  pinMode(tangki, OUTPUT);
}

void loop () {
  
  DateTime now = RTC.now();
  tahun = now.year();
  bulan = now.month();
  hari = now.day();
  jam = now.hour();
  menit = now.minute();
  detik = now.second();

  Serial.print(tahun);
  Serial.print(" / ");
  Serial.print(bulan);
  Serial.print(" / ");
  Serial.print(hari);
  Serial.print(" ");
  Serial.print(jam);
  Serial.print(": ");
  Serial.print(menit);
  Serial.print(": ");
  Serial.print(detik);
  Serial.println();


 
}
