#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <virtuabotixRTC.h>
#include <EEPROM.h>

virtuabotixRTC myRTC(7, 6, 5);//clk,dat,rst
#define DHTPIN_1 8
#define DHTPIN_2 9
#define DHTPIN_3 10
#define DHTTYPE DHT11
DHT dht_1(DHTPIN_1, DHTTYPE);
DHT dht_2(DHTPIN_2, DHTTYPE);
DHT dht_3(DHTPIN_3, DHTTYPE);

float humi_1, temp_1;
float humi_2, temp_2;
float humi_3, temp_3;


String waktu;
int tanggal, bulan, tahun, jam, menit, detik;
int buzzer = 13;
int relay_1 = 11;
int relay_2 = 12;
int pos = 1;

int tombol_up = 4, tombol_down = 3, tombol_menu_1 = 2, tombol_menu_2 = 1, tombol_mode = 0;

int offset_hm = 60;
int offset_suhu = 33;
int jam_offset_pagi = 8;
int jam_offset_sore = 15;


void setup() {

  Serial.begin(9600);
  //myRTC.setDS1302Time(00, 32, 18, 6, 20, 1, 2023);
  dht_1.begin();
  dht_2.begin();
  dht_3.begin();
  pinMode(buzzer, OUTPUT);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(tombol_mode, INPUT_PULLUP);
  pinMode(tombol_menu_2, INPUT_PULLUP);
  pinMode(tombol_menu_1, INPUT_PULLUP);
  pinMode(tombol_down, INPUT_PULLUP);
  pinMode(tombol_up, INPUT_PULLUP);
  digitalWrite(buzzer, HIGH);
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Config System");
  lcd.setCursor(0, 1);
  lcd.print("Loading....");
  delay(2000);
  digitalWrite(buzzer, HIGH);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("System Active");
  lcd.setCursor(5, 1);
  lcd.print("Ready");
  delay(2000);
  lcd.clear();
}

void loop() {

  while (digitalRead(tombol_mode) == LOW) {
    tampilan_menu();
    
  }

  cek_sensor_1();
  cek_sensor_2();
  cek_sensor_3();
  cek_waktu();
  //cek_failure();
  cek_status();

  if (digitalRead(tombol_up) == LOW) {
    delay(500);
    lcd.clear();
    pos++;
    if (pos > 3) {
      pos = 1;
    }
  }
  if (digitalRead(tombol_down) == LOW) {
    delay(500);
    lcd.clear();
    pos--;
    if (pos < 1) {
      pos = 3;
    }
  }

  if (pos == 1) {
    tampilan_hm();
  }
  if (pos == 2) {
    tampilan_suhu();
  }
  if (pos == 3) {
    tampilan_jam();
  }
}

void tampilan_menu() {
  offset_hm =  EEPROM.read(1);
  offset_suhu =  EEPROM.read(2);
  lcd.setCursor(0, 0);
  lcd.print("Offset RH   = ");
  lcd.print(offset_hm);
  lcd.setCursor(0, 1);
  lcd.print("Offset Suhu = ");
  lcd.print(offset_suhu);

  if (digitalRead(tombol_menu_1) == LOW) {
    delay(500);
    int x = 1;
    int new_var =  EEPROM.read(1);
    lcd.clear();
    while (x < 5) {

      lcd.setCursor(0, 0);
      lcd.print("Change Humidity");
      lcd.setCursor(0, 1);
      lcd.print("Offset RH   = ");
      lcd.print(new_var);
      if (digitalRead(tombol_up) == LOW) {
        new_var ++;
        delay(100);
      }
      if (digitalRead(tombol_down) == LOW) {
        new_var --;
        delay(100);
      }
      if (digitalRead(tombol_menu_2) == LOW) {
        EEPROM.write(1, new_var);
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Completed");
        delay(2000);
        x = 6;
      }
    }
  }

  if (digitalRead(tombol_menu_2) == LOW) {
    delay(500);
    int x = 1;
    int new_var =  EEPROM.read(2);
    lcd.clear();
    while (x < 5) {

      lcd.setCursor(0, 0);
      lcd.print("New Temperature");
      lcd.setCursor(0, 1);
      lcd.print("Celcius = ");
      lcd.print(new_var);
      if (digitalRead(tombol_up) == LOW) {
        new_var ++;
        delay(100);
      }
      if (digitalRead(tombol_down) == LOW) {
        new_var --;
        delay(100);
      }
      if (digitalRead(tombol_menu_2) == LOW) {
        EEPROM.write(2, new_var);
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("Completed");
        delay(2000);
        x = 6;
      }
    }
  }



}




void cek_waktu() {
  myRTC.updateTime();
  jam = myRTC.hours;
  menit = myRTC.minutes;
  detik = myRTC.seconds;
  waktu = String() + jam + ":" + menit + ":" + detik;
  Serial.println(waktu);
  if (jam == jam_offset_pagi and menit == 0  and detik == 0) {
    cek_status();
  }
  else if (jam == jam_offset_sore and menit == 0 and detik == 0) {
    cek_status();
  } else {
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay_1, HIGH);
  }

}

void cek_status() {
  offset_hm =  EEPROM.read(1);
  offset_suhu =  EEPROM.read(2);
  if (humi_1 < offset_hm or humi_2 < offset_hm or humi_3 < offset_hm) {
    digitalWrite(buzzer, LOW);
    digitalWrite(relay_1, LOW);
  }
  else if (temp_1 > offset_suhu and temp_2 > offset_suhu and temp_3 > offset_suhu) {
    digitalWrite(buzzer, LOW);
    digitalWrite(relay_1, LOW);
  } else {
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay_1, HIGH);
  }



}

void cek_failure() {
  if (isnan(humi_1) || isnan(temp_1) or isnan(humi_2) || isnan(temp_2) or isnan(humi_3) || isnan(temp_3) ) {
    lcd.noBacklight();
    digitalWrite(buzzer, LOW);
    return;
  } else {
    lcd.backlight();
    digitalWrite(buzzer, HIGH);
  }
}

void tampilan_jam() {
  lcd.setCursor(6, 0);
  lcd.print("TIME");
  lcd.setCursor(4, 1);
  lcd.print(waktu);


}



void tampilan_hm() {
  lcd.setCursor(0, 0);
  lcd.print("(1)%");
  lcd.setCursor(0, 1);
  lcd.print(humi_1, 1);
  lcd.setCursor(6, 0);
  lcd.print("(2)%");
  lcd.setCursor(6, 1);
  lcd.print(humi_2, 1);
  lcd.setCursor(12, 0);
  lcd.print("(3)%");
  lcd.setCursor(12, 1);
  lcd.print(humi_3, 1);
  lcd.setCursor(5, 0);
  lcd.print("|");
  lcd.setCursor(5, 1);
  lcd.print("|");
  lcd.setCursor(11, 0);
  lcd.print("|");
  lcd.setCursor(11, 1);
  lcd.print("|");
}


void tampilan_suhu() {
  lcd.setCursor(0, 0);
  lcd.print("(1)C");
  lcd.setCursor(0, 1);
  lcd.print(temp_1, 1);
  lcd.setCursor(6, 0);
  lcd.print("(2)C");
  lcd.setCursor(6, 1);
  lcd.print(temp_2, 1);
  lcd.setCursor(12, 0);
  lcd.print("(3)C");
  lcd.setCursor(12, 1);
  lcd.print(temp_3, 1);
  lcd.setCursor(5, 0);
  lcd.print("|");
  lcd.setCursor(5, 1);
  lcd.print("|");
  lcd.setCursor(11, 0);
  lcd.print("|");
  lcd.setCursor(11, 1);
  lcd.print("|");
}




void cek_sensor_1() {
  humi_1 = dht_1.readHumidity();//baca kelembaban
  temp_1 = dht_1.readTemperature();//baca suhu
}

void cek_sensor_2() {
  humi_2 = dht_2.readHumidity();//baca kelembaban
  temp_2 = dht_2.readTemperature();//baca suhu
}

void cek_sensor_3() {
  humi_3 = dht_3.readHumidity();//baca kelembaban
  temp_3 = dht_3.readTemperature();//baca suhu
}
