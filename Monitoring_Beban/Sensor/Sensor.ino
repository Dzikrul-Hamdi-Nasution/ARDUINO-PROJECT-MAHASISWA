#include <Wire.h>                                                   // Memanggil library Wire
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>                                      // Memanggil library LCD i2C
#include "ZMPT101B.h"
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include "DS3231.h"
#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance
RTClib RTC;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
ZMPT101B voltageSensor(A0);
int jam, menit, detik, tahun, bulan, hari;
float suhu, daya_kwh;
int sensorValue_sensor_tegangan = 0, tegangan_PLN;
double sensorValue_sensor_arus = 0;
int buzzer = 4;
int relay = 5;
int kontrol_relay_pin = A2;
int set_suhu = 45, set_arus = 5000, set_kwh;
int status_beban;
String dataIn;
String dt[10];
int i, batas, kontrol_relay;
boolean parsing = false;
String data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mlx.begin();
  lcd.init();                                                         // Memulai komunikasi dengan LCD
  lcd.backlight();
  lcd.setCursor( 0 , 0);
  voltageSensor.calibrate();
  emon1.current(A1, 111.1);             // Current: input pin, calibration.
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(relay, LOW);
  lcd.print("Initialization");
  delay(1500);
  digitalWrite(buzzer, HIGH);
  digitalWrite(relay, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  tampilan_1();
  tampilan_2();
  kirim();
}

void baca() {

  kontrol_relay = analogRead(kontrol_relay_pin);
  if (kontrol_relay < 350) {
    digitalWrite(relay, HIGH);
  }
  else {
    digitalWrite(relay, LOW);
  }

}



void kirim() {
  Serial.print("*");
  Serial.print(tegangan_PLN);
  Serial.print("@");
  Serial.print(sensorValue_sensor_arus);
  Serial.print("@");
  Serial.print(daya_kwh);
  Serial.print("@");
  Serial.print(suhu);
  Serial.print("@");
  Serial.print(status_beban);
  Serial.print("@");
  Serial.print(jam);
  Serial.print("@");
  Serial.print(menit);
  Serial.print("@");
  Serial.print(detik);
  Serial.print("@");
  Serial.println("#");
  baca();
}

void tampilan_1() {
  lcd.clear();
  for (int i = 0; i <= 2; i++) {
    cek_waktu();
    lcd.setCursor( 0 , 0);
    lcd.print("Jam : ");
    lcd.print(jam);
    lcd.print(":");
    lcd.print(menit);
    lcd.print(":");
    lcd.print(detik);
    lcd.setCursor( 0 , 1);
    lcd.print("Tanggal : ");
    lcd.print(tahun);
    lcd.print("/");
    lcd.print(bulan);
    lcd.print("/");
    lcd.print(hari);
    lcd.setCursor( 0 , 2);
    if (status_beban == 1) {
      lcd.print("Status : On Load");
    } else {
      lcd.print("Status : No Load");
    }
    cek_beban();
    baca();
    delay(1000);
  }
}

void tampilan_2() {
  lcd.clear();
  for (int i = 0; i <= 2; i++) {
    cek_beban();
    baca();
    // lcd.clear();
    lcd.setCursor( 0 , 0);
    lcd.print("Tegangan : ");
    lcd.print(tegangan_PLN);
    lcd.print(" V ");
    lcd.setCursor( 0 , 1);
    lcd.print("Arus : ");
    lcd.print(sensorValue_sensor_arus);
    lcd.print(" mA ");
    lcd.setCursor( 0 , 2);
    lcd.print("Wh : ");
    lcd.print(daya_kwh);
    lcd.setCursor( 0 , 3);
    lcd.print("Suhu : ");
    lcd.print(suhu);
    delay(1000);
  }
}




void cek_beban() {
  float regresi_suhu = mlx.readObjectTempC();
  suhu = -0.2853 + (1.0258 * regresi_suhu);
  tegangan();
  arus();
  daya_kwh = daya_kwh + (tegangan_PLN * sensorValue_sensor_arus / 1000) / 3600  ;
}

void tegangan() {
  float U = voltageSensor.getVoltageAC();
  float regresi_tegangan = U * 10;
  tegangan_PLN = -0.6918 + (1.0292 * regresi_tegangan);
}
void arus() {
  double Irms = emon1.calcIrms(500);  // Calculate Irms only
  float regresi_arus = Irms * tegangan_PLN / 30;
  sensorValue_sensor_arus = -14.9729 + (1.2862 * regresi_arus);
  if (sensorValue_sensor_arus > 20) {
    status_beban = 1;
  }
  else {
    status_beban = 0;
  }
}

void cek_waktu() {
  DateTime now = RTC.now();
  tahun = now.year();
  bulan = now.month();
  hari = now.day();
  jam = now.hour();
  menit = now.minute();
  detik = now.second();
}
