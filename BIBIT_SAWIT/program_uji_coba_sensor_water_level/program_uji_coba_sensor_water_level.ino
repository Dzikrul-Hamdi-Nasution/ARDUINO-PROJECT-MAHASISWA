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

  cek_sensor();
  cek_galon();

}




void cek_sensor() {
  sensorValue_1 = analogRead(sensorPin_1);//sensor kelembapan tanah 1
  sensorValue_2 = analogRead(sensorPin_2);//sensor kelembapan tanah 2
  sensorValue_galon = analogRead(sensorPin_3);//sensor water level pada galon
}

void cek_galon() {
  
  if (sensorValue_galon > 700) {
    status_air = "Kosong";
    digitalWrite(tangki, HIGH);
  }
  else {
    status_air = "Penuh";
    digitalWrite(tangki, LOW);
  }
}
