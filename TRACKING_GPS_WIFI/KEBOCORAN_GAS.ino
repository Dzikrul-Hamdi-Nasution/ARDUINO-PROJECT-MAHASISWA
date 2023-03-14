#include "CTBot.h"                                                  // Memanggil library CTBot
CTBot myBot;                                                        // Objek untuk mengakses library CTBot

#include <Wire.h>                                                   // Memanggil library Wire
#include <LiquidCrystal_I2C.h>                                      // Memanggil library LCD i2C
LiquidCrystal_I2C lcd(0x27, 16, 2);                                 // Deklarasi alamat dan ukuran LCD i2c

String ssid  = "ELEKTRONIKA KELAS";                                // ganti ini dengan nama jaringannya
String pass  = "3lektronikapolmed";                                 // ganti ini dengan password wifinya
String token = "2098818619:AAEIeg-guP9XxD1Ug1gRi2QUQcyLIOgslOc";     // token telegram

String pesan = "Terjadi Kebocoran GAS !!!";                          // Pesan yang akan dikirim ke telegram
int kunci = 1;
float nilaiMQ5 ;                                                     // Variable penampung adc MQ5
float batas = 800 ;                                                  // Variable menampung batas pembacaan agar dikirim notifikasi
const int lampu = D7 ;

void setup() {
  Serial.begin(9600);                                                  // Deklarasi baudrate komunikasi serial
  lcd.begin();                                                         // Memulai komunikasi dengan LCD
  lcd.backlight();                                                     // Menyalakan backlight LCD
  pinMode(lampu , OUTPUT);
  digitalWrite(lampu , HIGH);
  myBot.wifiConnect(ssid, pass);                                     // Menghubungkan ke jaringan internet
  myBot.setTelegramToken(token);                                     // Menghubungkan ke telegram

  if (myBot.testConnection()) {                                      // Jika terhubung dengan jaringan internet, maka
    Serial.println("\ntestConnection OK");                           // Tampil "testConnection OK" pada serial monitor
  }
  else {                                                             // Jika tidak, maka
    Serial.println("\ntestConnection NOK");                          // Tampil "testConnection NOK" pada serial monitor
  }
}





void loop() {
  TBMessage msg;                                                    // Objek untuk menggunakan TBmessage
  nilaiMQ5 = analogRead(A0);                                        // Hasil pembacaan MQ5 disimpan pada variable nilaiMQ5
  Serial.println(nilaiMQ5);                                         // Menampilkan  isi variable nilaiMQ5 pada serial monitor
  if (nilaiMQ5 >= batas) {
    if (kunci == 1) {
      lcd.setCursor( 0 , 0);                               // Mengatur cursor pada baris 1 kolom 1
      lcd.print("     SEND       ");
      myBot.sendMessage(1600696941, pesan);                             // Kirim pesan ke telegram Telegram dengan id (ganti angka dengan id telegram)
      myBot.sendMessage(1600696941, "Pembacaan Nilai Sensor :");
      myBot.sendMessage(1600696941, String(nilaiMQ5));
      kunci = 2;
      lcd.setCursor( 0 , 0);                               // Mengatur cursor pada baris 1 kolom 1
      lcd.print("     SUKSES     ");
    }
    alarm();
    lcd.setCursor( 0 , 0);                               // Mengatur cursor pada baris 1 kolom 1
    lcd.print("     BAHAYA     ");                       // Menampilkan "     BAHAYA     " pada LCD
    lcd.setCursor( 0 , 1);                               // Mengatur cursor pada baris 2 kolom 1
    lcd.print("Nilai MQ5 :");                            // Menampilkan "Nilai MQ5 :" pada LCD
    lcd.setCursor( 11 , 1);                              // Mengatur cursor pada baris 2 kolom 12
    lcd.print(nilaiMQ5);                                 // Menampilkan nilai variable nilaiMQ5 pada LCD
  }
  else {
    kunci = 1;
    lcd.setCursor( 0 , 0);                               // Mengatur cursor pada baris 1 kolom 1
    lcd.print("      AMAN      ");                       // Menampilkan "      AMAN      " pada LCD
    lcd.setCursor( 0 , 1);                               // Mengatur cursor pada baris 2 kolom 1
    lcd.print("Nilai MQ5 :");                            // Menampilkan "Nilai MQ5 :" pada LCD
    lcd.setCursor( 11 , 1);                              // Mengatur cursor pada baris 2 kolom 12
    lcd.print(nilaiMQ5);                                 // Menampilkan nilai variable nilaiMQ5 pada LCD
  }

}


void alarm() {
  digitalWrite(lampu , HIGH);
  tone(D8 , 3500 , 1000);                                          // Buzzer menyala
  delay(1000);
  digitalWrite(lampu , LOW);
  tone(D8 , 0);                                          // Buzzer menyala
  delay(1000);
}
