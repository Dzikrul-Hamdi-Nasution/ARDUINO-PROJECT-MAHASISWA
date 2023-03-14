#include "max6675.h"  //libary senor suhu type k
#include <Servo.h>    //library servo
#include <LiquidCrystal.h>  //library LCD

LiquidCrystal lcd(A1, A0, A5, A4, A3, A2);  //inisialisasi pin LCD ke Arduino
Servo Kuas, Pembalik, heater_servo;         //inisialisasi nama servo

int relay = 7, buzzer = 11;    //inisialiisasi pin utk output Arduino
int waktu;    //inisilisasi variabel waktu untuk data waktu pemanggangan

int batas_suhu_max;   //inisialisasi variabel batas suhu pemanggang




// Temperature Sensor Heater
int thermo1D0 = 6; // so
int thermo1CS = 5;
int thermo1CLK = 4; // sck
float temp1 = 0;
MAX6675 thermocouple1(thermo1CLK, thermo1CS, thermo1D0);

// Temperature Sensor Pemanggang
int thermo2D0 = 10; // so
int thermo2CS = 9;
int thermo2CLK = 8; // sck
float temp2 = 0;
MAX6675 thermocouple2(thermo2CLK, thermo2CS, thermo2D0);

int vision;   //inisialisasi variabel vision untuk status ikan dari laptop secara serial

void setup() {
  // setting parameter arduino dan sistem
  Serial.begin(9600);   //set kecepatan data serial antara arduino dengan laptop yaitu 9600
  Kuas.attach(12);      //inisialisasi pin 12 sebagai pin servo kuas
  Pembalik.attach(13);  //inisialisasi pin 13 sebagai pin servo Pemanggang
  heater_servo.attach(3);   //inisialisasi pin 3 sebagai pin servo heater
  lcd.begin(16, 2);     //setting jenis LCD yang digunakan adalah 16 kolom 2 baris
  lcd.setCursor(6, 0);    //set tulisan awal LCD di baris 0 dan kolom 6
  lcd.print("PEMANGGANG");    //tampilkan tulisan "PEMANGGANG" di LCD
  lcd.setCursor(8, 0);    //set tulisan awal LCD di baris 0 dan kolom 8
  lcd.print("OTOMATIS");  //tampilkan tulisan "OTOMATIS" di LCD
  Kuas.write(130);  //kondisi idle servo kuas
  Pembalik.write(180);   //kondisi idle servo pemanggang
  heater_servo.write(0);  //kondisi idle servo  heater
  pinMode(relay, OUTPUT);   //set  relay sebagi Output Arduino
  pinMode(buzzer, OUTPUT);  //set Buzzer sebagai Output Arduino

  digitalWrite(relay, HIGH);  //non aktifkan relay
  digitalWrite(buzzer, LOW);  //aktifkan buzzer
  delay(1000);    //jeda watku 1 detik sebelum sistem mulai
  digitalWrite(buzzer, HIGH);   //non aktifkan atau matikan buzzer
  lcd.clear();    //hapus tampilan LCD
}

void loop() {
  if (Serial.available() > 0) {   //cek apakah ada data serial yang diterima, jika tidak, maka sistem tidak akan memulai
    int incomingByte = Serial.read();   //ambil data serial dari laptop dan tampung di variabel "incomingbyte"

    if (incomingByte == "1") {    //jika data serial yang diterima adalah 1, maka beri nilai variabel vision = 1 artinya sdah terdetksi ikan sudah kategori masak
      vision = 1;   //beri variabel vision dengan nilai 1
    } else {  //jika tidak, maka beri variabel vision = 2 yang menandakan ikan belum kategori dalam sudah masak
      vision = 2;   //beri variabel vision dengan nilai 2

    }
    temp1 = thermocouple1.readCelsius();    //fungsi untuk membaca sensor type k dan data nya ditampung dalam variabel temp1
    lcd.setCursor(1, 0);    //set penulisan suhu heater di baris 0 kolom 1
    lcd.print(temp1);   //tampilkan pembacaan sensor suhu heater
    temp2 = thermocouple2.readCelsius();
    lcd.setCursor(7, 0);    //set penulisan suhu panggangan di baris 0 kolom 7
    lcd.print("--");        //tampilkan "--" di LCD
    lcd.setCursor(10, 0);   //set penulisan suhu panggangan di baris 0 kolom 10
    lcd.print(temp2);     //tampilkan pembacaan sensor suhu panggangan

    lcd.setCursor(0, 1);     //set penulisan waktu di baris 1 kolom 0
    lcd.print("Waktu : ");  //tampilkan "Waktu" di LCD
    lcd.setCursor(8, 1);    //set penulisan waktu yang terbaca di baris 1 kolom 8
    lcd.print(waktu);     //tampilkan varaiabel waktu

    heater_servo.write(110);    //gerakkan servo heater ke sudut 110 derajat


    if (temp1 < 410) {    //jika suhu heater masih dibawah batas amabang, maka relay heater tetap menyala
      digitalWrite(relay, LOW);   //aktifkan relay heater
    } else {    //jika tidak, maka heater akan mati
      digitalWrite(relay, HIGH);    //heater mati
    }


    if (waktu == 900 or vision == 1 or temp2 > 80) {    //jika waktu sudah 900 detik atau vision terdeteksi sudah masak atau suhu panggangan lebih dari 80 derajat maka lakukan perintah balik ikan
      balik_ikan_bawah();   //fungsi pembalik ikan ke bawah
    }
    if (waktu == 1500 or vision == 1 or temp2 > 100) {     //jika waktu sudah 1500 detik atau vision terdeteksi sudah masak atau suhu panggangan lebih dari 100 derajat maka lakukan perintah balik ikan
      balik_ikan_atas();    //fungsi pembalik ikan ke atas
    }
    if (waktu > 1800) {   //jika sudah lebih dari 1800 detik, maka sistem menyatakan ikan sudah masak berdasarkan waktu
      for (int i = 1; i <= 22; i++) {   //perulangan untuk suara buzzer
        heater_servo.write(0);    //menurunkan servo heater
        digitalWrite(relay, HIGH);    //mematikan relay heater
        int x = i * 200;
        lcd.clear();    //hapus tampilan LCD
        lcd.setCursor(5, 0);  //awal penulisan di baris 0 kolom 5
        lcd.print("FINISH");    //tampilkan FINISH di LCD
        tone(buzzer , x , 500);   //Suara buzzer bervariasi ketika sudah selesai
        delay(100);   //jeda waktu 100 mili detik
      }
    }

    delay (1000); //jeda setiap detik
    waktu++;    //lakukan increament atau hitung berapa lama sdah berjalan waktu pemanggangan

  }

}



void oles_ikan() {
  lcd.clear();    //menghapus LCD
  lcd.setCursor(0, 0);  //mengatur awal tulisan LCD di baris 0 kolom 0
  lcd.print("Mengoles Ikan");   //menampilkan "megoles Ikan" di LCD
  for (int i = 0; i <= 1; i++) {  //melakukan perulangan 2 kali untuk pengolesan
    for (int i = 130; i >= 0; i--) {    //melakukan perulangan 130 kali utk mengatur kecepatan oles dan jarak oles ke tmepat bumbu adalah 130 deajat
      Kuas.write(i);    //menggerak kuas servo berdasarkan perulagnan 130 x dengan jeda waktu setiap detik 50 mili detik, semakin rendah jeda, maka akan semakin cepat servo oels bergerak
      delay(50);    //jeda waktu 50 detik
    }
    delay(200);     //jeda waktu 200 mili detik setiap selesai melakukan oles dari tempat bumbu ke panggangan
    for (int i = 0; i <= 130; i++) {    //menggerak kuas servo berdasarkan perulagnan 130 x dengan jeda waktu setiap detik 50 mili detik
      Kuas.write(i);        //jeda waktu 50 detik
      delay(50);
    }
    delay(2000);    //jeda waktu 2 detik setiap selesai melakukan pengolesan
  }
  lcd.clear();    //menghapus tampilan LCD
}



//fungsi untuk membalik ikan
void balik_ikan_atas() {
  lcd.clear();
  lcd.setCursor(2, 0);
  heater_servo.write(0);
  oles_ikan();
  lcd.print("Membalik Ikan");
  for (int i = 0; i <= 180; i++) {
    Pembalik.write(i);
    delay(30);
  }
  lcd.clear();
  heater_servo.write(110);
}


//fungsi untuk membalik ikan
void balik_ikan_bawah() {
  lcd.clear();    //menghapus tampilan LCD
  lcd.setCursor(2, 0);  //mengatur posisi tulisan di LCD di baris 1 di kolom 2
  heater_servo.write(0);  //sudut servo Heater 0 derajat atau heater diturunkan
  oles_ikan();    //panggil fungsi untuk olesin ikan
  lcd.print("Membalik Ikan");   //menampilkan kata "membalik Ikan" di  LCD
  for (int i = 180; i >= 0; i--) {    //lakukan perulangan 180 x untuk mengatur pergerakkan membalik ikan dengan lambat per step derajat nya di kasih jeda 30 mili detik
    Pembalik.write(i);    //pergerakkan sudut servo pembalik panggangan sesuai dengan jeda 30 mili detik
    delay(30);    //jeda 30 mili detik
  }
  lcd.clear();    //megnhapus tampilan LCD agar tidak bertimpa dengan tulisan LCD utama yaitu tulisan LCD menampilkan suhu dan waktu
  heater_servo.write(110);    //menaikkan Heater keatas atau menggerakkan sudut servo heater ke 110 derajat
}
