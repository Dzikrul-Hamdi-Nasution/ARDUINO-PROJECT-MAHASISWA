#include "HX711.h"
#include <ESP8266WiFi.h>
#include "Adafruit_Fingerprint.h"
#include "CTBot.h"                                                  // Memanggil library CTBot
CTBot myBot;

#define DOUT  5
#define CLK  4

String ssid  = "Server Project";
String pass  = "Master75wew";
String token = "5661450449:AAFrWAR-iRU0cBXYd1UZZ1RMlc58M3Rj1lc";

HX711 scale(DOUT, CLK);
float calibration_factor = 410;
float GRAM, nilai_berat, nilai_batas_bawah = 10000, nilai_batas_atas = 10000, batas_ambang = 100;
int sensor = 14, buzzer = 12;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  Serial.println();
  Serial.print("Connecting");
  myBot.wifiConnect(ssid, pass);                                     // Menghubungkan ke jaringan internet
  myBot.setTelegramToken(token);                                     // Menghubungkan ke telegram
  if (myBot.testConnection()) {                                      // Jika terhubung dengan jaringan internet, maka
    Serial.println("System Online ");                           // Tampil "testConnection OK" pada serial monitor
    myBot.sendMessage(1441844129, "System Online");
    myBot.sendMessage(1315539227, "System Online");
  } else {
    Serial.println("System OFFLINE ");
    delay(3000);
  }
  scale.set_scale();
  scale.tare();
  Serial.println("Kalibrasi Berat");
}

void loop() {

  cek_berat();

  TBMessage msg;
  if (digitalRead(sensor) == LOW) {
    Serial.println("Terjadi Pencurian");
    myBot.sendMessage(1315539227, "Terjadi Pencurian");
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("cek")) {
      myBot.sendMessage(1315539227, "Berat Kendaraan = " + String(GRAM, 2) + " Gram");
      Serial.println("Cek Berat");
    }
    if (msg.text.equalsIgnoreCase("konfirmasi")) {
      nilai_berat = GRAM;
      nilai_batas_bawah = nilai_berat - batas_ambang;
      nilai_batas_atas = nilai_berat + batas_ambang;
      myBot.sendMessage(1315539227, "Konfirmasi Berat = " + String(GRAM, 2) + " Gram");
      myBot.sendMessage(1315539227, "Konfirmasi Berat Max = " + String(nilai_batas_atas, 2) + " Gram");
      myBot.sendMessage(1315539227, "Konfirmasi Berat Min = " + String(nilai_batas_bawah, 2) + " Gram");
      Serial.println("Konfirasmi Berat");
    }
  }
  if (nilai_berat > 10) {
    if (GRAM < nilai_batas_bawah) {
      Serial.println("Timbangan Berkurang");
      myBot.sendMessage(1315539227, "Terjadi Pengurangan Berat");
      myBot.sendMessage(1315539227, "Berat = " + String(GRAM, 2) + " Gram");
      digitalWrite(buzzer, HIGH);
      delay(2000);
    } else {
      digitalWrite(buzzer, LOW);
    }
    if (GRAM > nilai_batas_atas) {
      Serial.println("Timbangan Bertambah");
      myBot.sendMessage(1315539227, "Terjadi Penambahan Berat");
      myBot.sendMessage(1315539227, "Berat = " + String(GRAM, 2) + " Gram");
      digitalWrite(buzzer, HIGH);
      delay(2000);
    } else {
      digitalWrite(buzzer, LOW);
    }
  }



}



void cek_berat() {
  scale.set_scale(calibration_factor);
  float data_berat = abs(scale.get_units());
  GRAM = (data_berat), 4;
  Serial.println(String(GRAM, 2));
}
