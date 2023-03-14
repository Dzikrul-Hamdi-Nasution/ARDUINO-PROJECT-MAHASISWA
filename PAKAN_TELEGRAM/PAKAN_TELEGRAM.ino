#include "CTBot.h"                                                  // Memanggil library CTBot
CTBot myBot;                                                        // Objek untuk mengakses library CTBot
#include <Servo.h>
#include <RTClib.h>
#include <Wire.h>
RTC_DS3231 rtc;
Servo servo_takaran, servo_utama;
#define triggerPin  D8
#define echoPin     D7
long duration, jarak;
int jam, menit, detik, tahun, bulan, hari, kunci = 0;
int makan_pagi ;
int makan_sore ;
int menit_makan = 25;
String pesan_pagi = "Pemberian Pakan Pagi";
String pesan_sore = "Pemberian Pakan Sore";
String alert = "Pakan Habis";

String ssid  = "Server Project";                                // ganti ini dengan nama jaringannya
String pass  = "Master75wew";
String token = "1968981204:AAFHfmN0TWKziu_PMvuL2dmkCW13B1mgrOU";     // token telegram

String substringku0, substringku1, substringku2, string_pagi, string_sore;
void setup() {
  Serial.begin(9600);                                                  // Deklarasi baudrate komunikasi serial
  Wire.begin(5, 4);
  rtc.begin();
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //Serial.print("INisialiosasi....");
  myBot.wifiConnect(ssid, pass);                                     // Menghubungkan ke jaringan internet
  myBot.setTelegramToken(token);                                     // Menghubungkan ke telegram
  if (myBot.testConnection()) {                                      // Jika terhubung dengan jaringan internet, maka
    // Serial.println("\ntestConnection OK");                           // Tampil "testConnection OK" pada serial monitor
  }
  else {                                                             // Jika tidak, maka
    // Serial.println("\ntestConnection NOK");                          // Tampil "testConnection NOK" pada serial monitor
  }
  myBot.sendMessage(1441844129, "System Online");
  myBot.sendMessage(1513186151, "System Online");

}

void loop() {
  TBMessage msg;

  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("cek")) {
      cek_waktu();
      myBot.sendMessage(msg.sender.id, "Jam Pagi = " + string_pagi);// cek status waktu
      myBot.sendMessage(msg.sender.id, "Jam Sore = " + string_sore);
      myBot.sendMessage(msg.sender.id, "Menit = " + substringku1);
    }
    else {
      substringku0 = getValue(msg.text, ' ', 0);
      substringku1 = getValue(msg.text, ' ', 1);
      substringku2 = getValue(msg.text, ' ', 2);

      myBot.sendMessage(msg.sender.id, "Data telah di perbaharui");
      if (substringku2.toInt() == 1) {
        string_pagi = substringku0;
        makan_pagi = substringku0.toInt();
        myBot.sendMessage(1513186151, "Jam Pagi = " + substringku0);
      }
      if (substringku2.toInt() == 2) {
        string_sore = substringku0;
        makan_sore = substringku0.toInt();
        myBot.sendMessage(1513186151, "Jam Sore = " + substringku0);
      }
      myBot.sendMessage(1513186151, "Menit = " + substringku1);
      menit_makan = substringku1.toInt();
    }
  }

  ketinggian();
  cek_waktu();

  if (jarak > 10) {
    //Serial.println("Pakan Habis");
    myBot.sendMessage(1513186151, alert);
  }

  if (jam == makan_pagi) {
    if (menit == menit_makan) {
      if (kunci == 0) {
        myBot.sendMessage(1513186151, pesan_pagi);
        Serial.println("1");
        kunci = 1;
      }
    }
    else {
      Serial.println("0");
      kunci = 0;
    }
  }
  if (jam == makan_sore) {
    if (menit == menit_makan) {
      if (kunci == 0) {
        myBot.sendMessage(1513186151, pesan_sore);
        Serial.println("1");
        kunci = 1;
      }
    }
    else {
      Serial.println("0");
      kunci = 0;
    }
  }

}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex &  found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void ketinggian() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = (duration / 2) / 29.1;
  /*
    Serial.print("jarak :");
    Serial.print(jarak);
    Serial.println(" cm");
  */
  delay(500);
}


void cek_waktu() {
  DateTime now = rtc.now();       //Menampilkan RTC pada variable now
  tahun = now.year();
  bulan = now.month();
  hari = now.day();
  jam = now.hour();
  menit = now.minute();
  detik = now.second();

  /* Serial.print("Tanggal : ");
    Serial.print(now.day());        //Menampilkan Tanggal
    Serial.print("/");
    Serial.print(now.month());      //Menampilkan Bulan
    Serial.print("/");
    Serial.print(now.year());       //Menampilkan Tahun
    Serial.print(" ");
    Serial.print("Jam : ");
    Serial.print(now.hour());       //Menampilkan Jam
    Serial.print(":");
    Serial.print(now.minute());     //Menampilkan Menit
    Serial.print(":");
    Serial.print(now.second());     //Menampilkan Detik
    Serial.println();
  */
}
