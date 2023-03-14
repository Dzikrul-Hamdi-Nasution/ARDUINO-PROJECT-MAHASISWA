#include "RTClib.h"
RTC_DS1307 rtc;
#include "PrayerTimes.h"
double waktu[sizeof(TimeName) / sizeof(char*)];

float _lat = 3.61492;    // lintang
float _lng = 98.66485;   // bujur

int _tahun ;
int _bulan ;
int _tanggal ;

int wilayah = 7;        //  WIB=7, WITA=8, WIT=9
int koreksi_imsak    = -8;
int koreksi_subuh    = 2;
int koreksi_terbit   = -3;
int koreksi_dhuha    = 24;
int koreksi_zuhur    = 3;
int koreksi_ashar    = 3;
int koreksi_terbenam = 1;
int koreksi_magrib   = 3;
int koreksi_isya     = 1;
int _sudut_subuh = 20;
int _sudut_isyak = 18;
int hours, minutes;

#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>
#include <WiFi.h>
#define FIREBASE_HOST "jam-masjid-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "DvgxynZ7dACFW9Qq6CpuxH2KI1AIoLnRsvaxvulw"
#define WIFI_SSID "SALAM ELECTRONICS"
#define WIFI_PASSWORD "btn-primary"

//initialize pin in 4094
#define clock_Pin 18    //pin for clock
#define data_Pin 19   //Send data
#define strob_Pin 5  //STB 
#define clock_Pin_subuh 14    //pin for clock
#define data_Pin_subuh 13   //Send data
#define strob_Pin_subuh 12  //STB 
#define clock_Pin_dzuhur 25    //pin for clock
#define data_Pin_dzuhur 27   //Send data
#define strob_Pin_dzuhur 26  //STB 

byte Chr_1[11] = {
  B01000000,
  B11101100,
  B10000010,
  B10001000,
  B00101100,
  B00011000,
  B00010000,
  B11001100,
  B00000000,
  B00001000,
  B11111110
};

byte Chr_2[11] = {
  B00100000,
  B11100110,
  B00010100,
  B10000100,
  B11000010,
  B10000001,
  B00000001,
  B11100100,
  B00001000,
  B10000000,
  B11111111
};
int tahun ;
int bulan ;
int tanggal;
int jam ;
int menit ;
int detik ;


int y = 0;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  set_calc_method(ISNA);  // metode perhitungan
  set_asr_method(Shafii); // madzhab?
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(_sudut_subuh);     // sudut waktu subuh
  set_isha_angle(_sudut_isyak);     // sudut waktu isyak

  //rtc.adjust(DateTime(tahun, bulan, tanggal, jam, menit, detik));
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    y++;
    if (y > 30) {
      break;
      y = 0;
    }
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(clock_Pin, OUTPUT);
  pinMode(strob_Pin, OUTPUT);
  pinMode(data_Pin, OUTPUT);
  pinMode(clock_Pin_subuh, OUTPUT);
  pinMode(strob_Pin_subuh, OUTPUT);
  pinMode(data_Pin_subuh, OUTPUT);
  pinMode(clock_Pin_dzuhur, OUTPUT);
  pinMode(strob_Pin_dzuhur, OUTPUT);
  pinMode(data_Pin_dzuhur, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
}

String waktu_detik, waktu_detik_1, waktu_detik_2;
String waktu_menit, waktu_menit_1, waktu_menit_2;
String waktu_jam, waktu_jam_1, waktu_jam_2;

String waktu_tanggal, waktu_tanggal_1, waktu_tanggal_2;
String waktu_bulan, waktu_bulan_1, waktu_bulan_2;
String waktu_tahun, waktu_tahun_1, waktu_tahun_2;

String waktu_imsak_jam, waktu_imsak_menit;
String waktu_dzuhur_jam, waktu_dzuhur_menit;
String waktu_ashar_jam, waktu_ashar_menit;
String waktu_magribh_jam, waktu_magribh_menit;
String waktu_isya_jam, waktu_isya_menit;
String waktu_subuh_jam, waktu_subuh_menit;

String waktu_dzuhur_jam_1, waktu_dzuhur_jam_2;
String waktu_dzuhur_menit_1, waktu_dzuhur_menit_2;
String waktu_ashar_jam_1, waktu_ashar_jam_2;
String waktu_ashar_menit_1, waktu_ashar_menit_2;
String waktu_magribh_jam_1, waktu_magribh_jam_2;
String waktu_magribh_menit_1, waktu_magribh_menit_2;
String waktu_isya_jam_1, waktu_isya_jam_2;
String waktu_isya_menit_1, waktu_isya_menit_2;
String waktu_subuh_jam_1, waktu_subuh_jam_2;
String waktu_subuh_menit_1, waktu_subuh_menit_2;
String waktu_imsak_jam_1, waktu_imsak_jam_2;
String waktu_imsak_menit_1, waktu_imsak_menit_2;

int iqomah_1, iqomah_2;
int kunci, waktu_sekarang, waktu_down;
int alarm_subuh_on = 2, alarm_dzuhur_on = 2, alarm_ashar_on = 2, alarm_magribh_on = 2, alarm_isya_on = 2;

void loop() {

  if (Firebase.getString("Mode/nilai") == "1") {
    mode_setting();
  }
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.println(now.day(), DEC);
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);

  _tahun = now.year();
  _bulan = now.month();
  _tanggal = now.day();

  waktu_tanggal = now.day();
  waktu_tanggal_2 = waktu_tanggal.substring(1, 2);
  waktu_tanggal_1 = waktu_tanggal.substring(0, 1);
  if (waktu_tanggal.toInt() < 10) {
    waktu_tanggal_1 = "10";
    waktu_tanggal_2 = waktu_tanggal.substring(0, 1);
  }
  waktu_bulan = now.month();
  waktu_bulan_2 = waktu_bulan.substring(1, 2);
  waktu_bulan_1 = waktu_bulan.substring(0, 1);
  if (waktu_bulan.toInt() < 10) {
    waktu_bulan_1 = "10";
    waktu_bulan_2 = waktu_bulan.substring(0, 1);
  }
  waktu_tahun = now.year();
  waktu_tahun_2 = waktu_tahun.substring(3, 4);
  waktu_tahun_1 = waktu_tahun.substring(2, 3);
  waktu_detik = now.second();
  waktu_detik_2 = waktu_detik.substring(1, 2);
  waktu_detik_1 = waktu_detik.substring(0, 1);
  if (waktu_detik.toInt() < 10) {
    waktu_detik_1 = "10";
    waktu_detik_2 = waktu_detik.substring(0, 1);
    if (waktu_detik_2.toInt() == 0) {
      waktu_detik_1 = "0";
    }
  }
  waktu_menit = now.minute();
  waktu_menit_2 = waktu_menit.substring(1, 2);
  waktu_menit_1 = waktu_menit.substring(0, 1);
  if (waktu_menit.toInt() < 10) {
    waktu_menit_1 = "10";
    waktu_menit_2 = waktu_menit.substring(0, 1);
    if (waktu_menit_2.toInt() == 0) {
      waktu_menit_1 = "0";
    }
  }
  waktu_jam = now.hour();
  
  waktu_jam_2 = waktu_jam.substring(1, 2);
  waktu_jam_1 = waktu_jam.substring(0, 1);
  if (waktu_jam.toInt() < 10) {
    waktu_jam_1 = "10";
    waktu_jam_2 = waktu_jam.substring(0, 1);
    if (waktu_jam_2.toInt() == 0) {
      waktu_jam_1 = "0";
    }
  }
  Serial.println();
  tampil_waktu();
  tampil_waktu_subuh();
  tampil_waktu_dzuhur();
  waktu_sholat();

  alarm_subuh();
  alarm_dzuhur();
  alarm_ashar();
  alarm_magribh();
  alarm_isya();

  panel_dzuhur();
  panel_ashar();
  panel_magribh();
  panel_isya();
  panel_subuh();
  panel_imsak();

  delay(1000);


}

void alarm_subuh() {
  if (waktu_jam.toInt() == waktu_subuh_jam.toInt()) {
    if (waktu_menit.toInt() == waktu_subuh_menit.toInt()) {
      Serial.println("Masuk Waktu Sholat SUBUH");
      iqomah_1 = 0;
      iqomah_2 = 2;
      waktu_sekarang = waktu_menit.toInt();
      if (kunci == 0) {
        for (int q = 0; q < 9; q++) {
          alarm_subuh_on = 1;
          kunci = 2;
          flash_gambar();
        }
        alarm_subuh_on = 0;
      }
    }
    waktu_down = waktu_menit.toInt() - waktu_sekarang;
    if (waktu_down >= 1) {
      iqomah_2 = 1;
    }
    if (waktu_down >= 2) {
      iqomah_2 = 0;
      kunci = 0;
    }
  }
}


void alarm_isya() {
  if (waktu_jam.toInt() == waktu_isya_jam.toInt()) {
    if (waktu_menit.toInt() == waktu_isya_menit.toInt()) {
      Serial.println("Masuk Waktu Sholat ISYA");
      iqomah_1 = 0;
      iqomah_2 = 2;
      waktu_sekarang = waktu_menit.toInt();
      if (kunci == 0) {
        for (int q = 0; q < 9; q++) {
          alarm_isya_on = 1;
          kunci = 2;
          flash_gambar();
        }
        alarm_isya_on = 0;
      }
    }
    waktu_down = waktu_menit.toInt() - waktu_sekarang;
    if (waktu_down >= 1) {
      iqomah_2 = 1;
    }
    if (waktu_down >= 2) {
      iqomah_2 = 0;
      kunci = 0;
    }
  }
}

void alarm_dzuhur() {
  if (waktu_jam.toInt() == waktu_dzuhur_jam.toInt()) {
    if (waktu_menit.toInt() == waktu_dzuhur_menit.toInt()) {
      Serial.println("Masuk Waktu Sholat DZUHUR");
      iqomah_1 = 0;
      iqomah_2 = 2;
      waktu_sekarang = waktu_menit.toInt();
      if (kunci == 0) {
        for (int q = 0; q < 9; q++) {
          alarm_dzuhur_on = 1;
          kunci = 2;
          flash_gambar();
        }
        alarm_dzuhur_on = 0;
      }
    }
    waktu_down = waktu_menit.toInt() - waktu_sekarang;
    if (waktu_down >= 1) {
      iqomah_2 = 1;
    }
    if (waktu_down >= 2) {
      iqomah_2 = 0;
      kunci = 0;
    }
  }
}

void alarm_ashar() {
  if (waktu_jam.toInt() == waktu_ashar_jam.toInt()) {
    if (waktu_menit.toInt() == waktu_ashar_menit.toInt()) {
      Serial.println("Masuk Waktu Sholat ASHAR");
      iqomah_1 = 0;
      iqomah_2 = 2;
      waktu_sekarang = waktu_menit.toInt();
      if (kunci == 0) {
        for (int q = 0; q < 9; q++) {
          alarm_ashar_on = 1;
          kunci = 2;
          flash_gambar();
        }
        alarm_ashar_on = 0;
      }
    }
    waktu_down = waktu_menit.toInt() - waktu_sekarang;
    if (waktu_down >= 1) {
      iqomah_2 = 1;
    }
    if (waktu_down >= 2) {
      iqomah_2 = 0;
      kunci = 0;
    }
  }
}

void alarm_magribh() {
  if (waktu_jam.toInt() == waktu_magribh_jam.toInt()) {
    if (waktu_menit.toInt() == waktu_magribh_menit.toInt()) {
      Serial.println("Masuk Waktu Sholat MAGRIBH");
      iqomah_1 = 0;
      iqomah_2 = 2;
      waktu_sekarang = waktu_menit.toInt();
      if (kunci == 0) {
        for (int q = 0; q < 9; q++) {
          alarm_magribh_on = 1;
          kunci = 2;
          flash_gambar();
        }
        alarm_magribh_on = 0;
      }
    }
    waktu_down = waktu_menit.toInt() - waktu_sekarang;
    if (waktu_down >= 1) {
      iqomah_2 = 1;
    }
    if (waktu_down >= 2) {
      iqomah_2 = 0;
      kunci = 0;
    }
  }
}

void mode_setting() {
  Serial.println("masuk mode setting waktu");
  while (Firebase.getString("Mode/nilai") == "1") {
    flash_gambar();
    tahun = Firebase.getString("Waktu/Tahun/nilai").toInt();
    bulan = Firebase.getString("Waktu/Bulan/nilai").toInt();
    tanggal = Firebase.getString("Waktu/Tanggal/nilai").toInt();
    jam = Firebase.getString("Waktu/Jam/nilai").toInt();
    menit = Firebase.getString("Waktu/Menit/nilai").toInt();
    detik = Firebase.getString("Waktu/Detik/nilai").toInt();

    if (Firebase.getString("Save/nilai") == "1") {
      rtc.adjust(DateTime(tahun, bulan, tanggal, jam, menit, detik));
      Serial.println("berhasil diupdate");
      delay(500);
      Firebase.setString("Mode/nilai", "0");
      Firebase.setString("Save/nilai", "0");
    }
  }

}

void flash_gambar() {
  DateTime now = rtc.now();
  digitalWrite(2, HIGH);
  waktu_jam_1 = "10";
  waktu_jam_2 = "10";
  waktu_menit_1 = "10";
  waktu_menit_2 = "10";
  Serial.println("flash gambar");
  if (alarm_subuh_on == 1) {
    waktu_subuh_menit_2 = "10";
    waktu_subuh_menit_1 = "10";
    waktu_subuh_jam_2 = "10";
    waktu_subuh_jam_1 = "10";
  }
  if (alarm_dzuhur_on == 1) {
    waktu_dzuhur_menit_2 = "10";
    waktu_dzuhur_menit_1 = "10";
    waktu_dzuhur_jam_2 = "10";
    waktu_dzuhur_jam_1 = "10";
  }
  if (alarm_ashar_on == 1) {
    waktu_ashar_menit_2 = "10";
    waktu_ashar_menit_1 = "10";
    waktu_ashar_jam_2 = "10";
    waktu_ashar_jam_1 = "10";
  }
  if (alarm_magribh_on == 1) {
    waktu_magribh_menit_2 = "10";
    waktu_magribh_menit_1 = "10";
    waktu_magribh_jam_2 = "10";
    waktu_magribh_jam_1 = "10";
  }
  if (alarm_isya_on == 1) {
    waktu_isya_menit_2 = "10";
    waktu_isya_menit_1 = "10";
    waktu_isya_jam_2 = "10";
    waktu_isya_jam_1 = "10";
  }

  tampil_waktu_subuh();
  tampil_waktu();
  tampil_waktu_dzuhur();

  delay(500);
  digitalWrite(2, LOW);
  waktu_menit = now.minute();
  waktu_menit_2 = waktu_menit.substring(1, 2);
  waktu_menit_1 = waktu_menit.substring(0, 1);
  if (waktu_menit.toInt() < 10) {
    waktu_menit_1 = "10";
    waktu_menit_2 = waktu_menit.substring(0, 1);
    if (waktu_menit_2.toInt() == 0) {
      waktu_menit_1 = "0";
    }
  }
  waktu_jam = now.hour();
  waktu_jam_2 = waktu_jam.substring(1, 2);
  waktu_jam_1 = waktu_jam.substring(0, 1);
  if (waktu_jam.toInt() < 10) {
    waktu_jam_1 = "10";
    waktu_jam_2 = waktu_jam.substring(0, 1);
    if (waktu_jam_2.toInt() == 0) {
      waktu_jam_1 = "0";
    }
  }
  if (alarm_subuh_on == 1) {
    panel_subuh();
  }
  if (alarm_dzuhur_on == 1) {
    panel_dzuhur();
  }
  if (alarm_ashar_on == 1) {
    panel_ashar();
  }
  if (alarm_magribh_on == 1) {
    panel_magribh();
  }
  if (alarm_isya_on == 1) {
    panel_isya();
  }

  tampil_waktu();
  tampil_waktu_subuh();
  tampil_waktu_dzuhur();

  delay(1000);
}

void panel_dzuhur() {
  waktu_dzuhur_jam_1 = waktu_dzuhur_jam.substring(0, 1);
  waktu_dzuhur_jam_2 = waktu_dzuhur_jam.substring(1, 2);
  waktu_dzuhur_menit_1 = waktu_dzuhur_menit.substring(0, 1);
  waktu_dzuhur_menit_2 = waktu_dzuhur_menit.substring(1, 2);
}
void panel_ashar() {
  waktu_ashar_jam_1 = waktu_ashar_jam.substring(0, 1);
  waktu_ashar_jam_2 = waktu_ashar_jam.substring(1, 2);
  waktu_ashar_menit_1 = waktu_ashar_menit.substring(0, 1);
  waktu_ashar_menit_2 = waktu_ashar_menit.substring(1, 2);
  if (waktu_ashar_menit.toInt() < 10) {
    waktu_ashar_menit_1 = "0";
    waktu_ashar_menit_2 = waktu_ashar_menit.substring(0, 1);
  }
}
void panel_magribh() {
  waktu_magribh_jam_1 = waktu_magribh_jam.substring(0, 1);
  waktu_magribh_jam_2 = waktu_magribh_jam.substring(1, 2);
  waktu_magribh_menit_1 = waktu_magribh_menit.substring(0, 1);
  waktu_magribh_menit_2 = waktu_magribh_menit.substring(1, 2);
}
void panel_isya() {
  waktu_isya_jam_1 = waktu_isya_jam.substring(0, 1);
  waktu_isya_jam_2 = waktu_isya_jam.substring(1, 2);
  waktu_isya_menit_1 = waktu_isya_menit.substring(0, 1);
  waktu_isya_menit_2 = waktu_isya_menit.substring(1, 2);
}
void panel_subuh() {
  waktu_subuh_jam_1 = waktu_subuh_jam.substring(0, 1);
  waktu_subuh_jam_2 = waktu_subuh_jam.substring(1, 2);
  waktu_subuh_menit_1 = waktu_subuh_menit.substring(0, 1);
  waktu_subuh_menit_2 = waktu_subuh_menit.substring(1, 2);
  if (waktu_subuh_jam.toInt() < 10) {
    waktu_subuh_jam_1 = "0";
    waktu_subuh_jam_2 = waktu_subuh_jam.substring(0, 1);
  }
  if (waktu_subuh_menit.toInt() < 10) {
    waktu_subuh_menit_1 = "0";
    waktu_subuh_menit_2 = waktu_subuh_menit.substring(0, 1);
  }
}
void panel_imsak() {
  waktu_imsak_jam_1 = waktu_imsak_jam.substring(0, 1);
  waktu_imsak_jam_2 = waktu_imsak_jam.substring(1, 2);
  waktu_imsak_menit_1 = waktu_imsak_menit.substring(0, 1);
  waktu_imsak_menit_2 = waktu_imsak_menit.substring(1, 2);
  if (waktu_imsak_jam.toInt() < 10) {
    waktu_imsak_jam_1 = "0";
    waktu_imsak_jam_2 = waktu_imsak_jam.substring(0, 1);
  }
  if (waktu_imsak_menit.toInt() < 10) {
    waktu_imsak_menit_1 = "0";
    waktu_imsak_menit_2 = waktu_imsak_menit.substring(0, 1);
  }
}


void tampil_waktu() {
  digitalWrite(strob_Pin, LOW);
  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_2[iqomah_2]);
  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_1[iqomah_1]);

  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_2[waktu_tahun_2.toInt()]);
  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_1[waktu_tahun_1.toInt()]);

  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_2[waktu_bulan_2.toInt()]);
  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_1[waktu_bulan_1.toInt()]);

  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_2[waktu_tanggal_2.toInt()]);
  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_1[waktu_tanggal_1.toInt()]);

  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_2[waktu_menit_2.toInt()]);
  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_1[waktu_menit_1.toInt()]);

  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_2[waktu_jam_2.toInt()]);
  shiftOut(data_Pin, clock_Pin, LSBFIRST, Chr_1[waktu_jam_1.toInt()]);
  digitalWrite(strob_Pin, HIGH);
}

void tampil_waktu_subuh() {
  digitalWrite(strob_Pin_subuh, LOW);
  shiftOut(data_Pin_subuh, clock_Pin_subuh, LSBFIRST, Chr_2[waktu_subuh_menit_2.toInt()]);//subuh
  shiftOut(data_Pin_subuh, clock_Pin_subuh, LSBFIRST, Chr_1[waktu_subuh_menit_1.toInt()]);

  shiftOut(data_Pin_subuh, clock_Pin_subuh, LSBFIRST, Chr_2[waktu_subuh_jam_2.toInt()]);
  shiftOut(data_Pin_subuh, clock_Pin_subuh, LSBFIRST, Chr_1[waktu_subuh_jam_1.toInt()]);

  shiftOut(data_Pin_subuh, clock_Pin_subuh, LSBFIRST, Chr_2[waktu_imsak_menit_2.toInt()]);//imsak
  shiftOut(data_Pin_subuh, clock_Pin_subuh, LSBFIRST, Chr_1[waktu_imsak_menit_1.toInt()]);

  shiftOut(data_Pin_subuh, clock_Pin_subuh, LSBFIRST, Chr_2[waktu_imsak_jam_2.toInt()]);
  shiftOut(data_Pin_subuh, clock_Pin_subuh, LSBFIRST, Chr_1[waktu_imsak_jam_1.toInt()]);

  digitalWrite(strob_Pin_subuh, HIGH);
}

void tampil_waktu_dzuhur() {
  digitalWrite(strob_Pin_dzuhur, LOW);
  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_2[waktu_isya_menit_2.toInt()]);
  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_1[waktu_isya_menit_1.toInt()]);

  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_2[waktu_isya_jam_2.toInt()]);
  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_1[waktu_isya_jam_1.toInt()]);

  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_2[waktu_magribh_menit_2.toInt()]);
  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_1[waktu_magribh_menit_1.toInt()]);

  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_2[waktu_magribh_jam_2.toInt()]);
  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_1[waktu_magribh_jam_1.toInt()]);

  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_2[waktu_ashar_menit_2.toInt()]);
  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_1[waktu_ashar_menit_1.toInt()]);

  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_2[waktu_ashar_jam_2.toInt()]);
  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_1[waktu_ashar_jam_1.toInt()]);

  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_2[waktu_dzuhur_menit_2.toInt()]);
  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_1[waktu_dzuhur_menit_1.toInt()]);

  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_2[waktu_dzuhur_jam_2.toInt()]);
  shiftOut(data_Pin_dzuhur, clock_Pin_dzuhur, LSBFIRST, Chr_1[waktu_dzuhur_jam_1.toInt()]);
  digitalWrite(strob_Pin_dzuhur, HIGH);
}


void waktu_sholat() {
  get_prayer_times(_tahun, _bulan, _tanggal, _lat, _lng, wilayah, waktu);
  for (int i = 0; i < 9; i++) {
    get_float_time_parts(waktu[i], hours, minutes);
    if (i == 0) { //Imsak
      minutes = minutes + koreksi_imsak;
      cek_menit();
    }
    if (i == 1) { //Subuh
      minutes = minutes + koreksi_subuh ;
      cek_menit();
    }
    if (i == 2) { //Terbit
      minutes = minutes + koreksi_terbit;
      cek_menit();
    }

    if (i == 3) { //Dhuha
      minutes = minutes + koreksi_dhuha;
      cek_menit();
    }
    if (i == 4) { //Zhuhur
      minutes = minutes + koreksi_zuhur;
      cek_menit();
    }
    if (i == 5) { //Ashar
      minutes = minutes + koreksi_ashar;
      cek_menit();
    }
    if (i == 6) { //Terbenam
      minutes = minutes + koreksi_terbenam;
      cek_menit();
    }
    if (i == 7) { //Magrib
      minutes = minutes + koreksi_magrib;
      cek_menit();
    }
    if (i == 8) { //Isya
      minutes = minutes + koreksi_isya ;
      cek_menit();
      //hours = hours - 2;
    }
    Serial.print(i);
    Serial.print(". ");
    Serial.print(TimeName[i]);
    Serial.print("  ");
    Serial.print(hours);
    Serial.print(":");
    Serial.println(minutes);

    if (i == 0) {//waktu imsak
      waktu_imsak_jam = String(hours);
      waktu_imsak_menit = String(minutes);
    }
    if (i == 1) {//waktu subuh
      waktu_subuh_jam = String(hours);
      waktu_subuh_menit = String(minutes);
    }
    if (i == 4) {//waktu dzuhur
      waktu_dzuhur_jam = String(hours);
      waktu_dzuhur_menit = String(minutes);
    }
    if (i == 5) {//waktu ashar
      waktu_ashar_jam = String(hours);
      waktu_ashar_menit = String(minutes);
    }
    if (i == 7) {//waktu magribh
      waktu_magribh_jam = String(hours);
      waktu_magribh_menit = String(minutes);
    }
    if (i == 8) {//waktu isya
      waktu_isya_jam = String(hours);
      waktu_isya_menit = String(minutes);
    }
  }
  Serial.println();

}
void cek_menit() {
  if (minutes == 60) {
    minutes = 0;
    hours = hours + 1;
  }
  if (minutes <= -1) {
    minutes = 60 - (-minutes);
    hours = hours - 1;
  }
  if (minutes >= 61) {
    minutes = minutes - 60;
    hours = hours + 1;
  }
}
