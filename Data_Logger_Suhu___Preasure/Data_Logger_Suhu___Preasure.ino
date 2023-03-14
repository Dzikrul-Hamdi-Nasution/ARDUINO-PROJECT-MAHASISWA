#include <OneWire.h>
#include <DallasTemperature.h>

#include "HX711.h"
#define DOUT 3
#define CLK 2

#define DOUT_A 4
#define CLK_A 5

#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
HX711 scale_Preasure_8(DOUT, CLK);
HX711 scale_Preasure_9(DOUT_A, CLK_A);
float calibration_factor = 31960;

int Preasure_8, Preasure_9;
int Preasure_1, Preasure_2, Preasure_3, Preasure_4, Preasure_5, Preasure_6, Preasure_7;
int deviceCount = 0;
DeviceAddress Thermometer;
float tempC, tegangan_sensor, arus_sensor;

uint8_t sensor1[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x85, 0x11, 0x1E, 0x96 };
uint8_t sensor2[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x85, 0xF5, 0xA9, 0x69 };
uint8_t sensor3[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x87, 0x24, 0x87, 0x86 };
uint8_t sensor4[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x87, 0x3C, 0xA4, 0xDD };
uint8_t sensor5[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x87, 0x25, 0x1D, 0x2D };
uint8_t sensor6[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x87, 0x55, 0xE1, 0x4C };
uint8_t sensor7[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x87, 0x23, 0x24, 0xA5 };
uint8_t sensor8[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x87, 0x23, 0x49, 0x3D };
uint8_t sensor9[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x87, 0x23, 0xB3, 0x37 };
uint8_t sensor10[8] = { 0x28, 0xFF, 0x64, 0x1E, 0x87, 0x27, 0x35, 0x5D };

float suhu_1, suhu_2, suhu_3, suhu_4, suhu_5, suhu_6, suhu_7, suhu_8, suhu_9, suhu_10;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  scale_Preasure_8.set_scale();
  scale_Preasure_9.set_scale();
  // scale_Preasure_8.tare();
  //scale_Preasure_9.tare();
  //Serial.println("Locating devices...");
  //Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  //Serial.print(deviceCount, DEC);
  //Serial.println(" devices.");
  // Serial.println("");

  Serial.println("LABEL,TIME,Tegangan ,Arus");
}

void loop() {

 // cek_preasure();
 // cek_suhu();
  cek_tegangan();
  cek_arus();
  send_logger();
  // delay(300000);
  delay(1000);
}

void send_logger() {
  Serial.print("DATA,TIME,");
  Serial.print(tegangan_sensor, 2);
  Serial.print(",");
  Serial.println(arus_sensor,2);
}




void tampil_logger() {

  Serial.print("Tekanan 1 : ");
  Serial.print(Preasure_1);
  Serial.print(" pa   |  ");
  Serial.print("Suhu 1 : ");
  Serial.print(suhu_1);
  Serial.println(" C");

  Serial.print("Tekanan 2 : ");
  Serial.print(Preasure_2);
  Serial.print(" pa   |  ");
  Serial.print("Suhu 2 : ");
  Serial.print(suhu_2);
  Serial.println(" C");

  Serial.print("Tekanan 3 : ");
  Serial.print(Preasure_3);
  Serial.print(" pa   |  ");
  Serial.print("Suhu 3 : ");
  Serial.print(suhu_3);
  Serial.println(" C");

  Serial.print("Tekanan 4 : ");
  Serial.print(Preasure_4);
  Serial.print(" pa   |  ");
  Serial.print("Suhu 4 : ");
  Serial.print(suhu_4);
  Serial.println(" C");

  Serial.print("Tekanan 5 : ");
  Serial.print(Preasure_5);
  Serial.print(" pa   |  ");
  Serial.print("Suhu 5 : ");
  Serial.print(suhu_5);
  Serial.println(" C");

  Serial.print("Tekanan 6 : ");
  Serial.print(Preasure_6);
  Serial.print(" pa   |  ");
  Serial.print("Suhu 6 : ");
  Serial.print(suhu_6);
  Serial.println(" C");

  Serial.print("Tekanan 7 : ");
  Serial.print(Preasure_7);
  Serial.print(" pa   |  ");
  Serial.print("Suhu 7 : ");
  Serial.print(suhu_7);
  Serial.println(" C");

  Serial.print("Tekanan 8 : ");
  Serial.print(Preasure_8);
  Serial.print(" pa   |  ");
  Serial.print("Suhu 8 : ");
  Serial.print(suhu_8);
  Serial.println(" C");

  Serial.print("Tekanan 9 : ");
  Serial.print(Preasure_9);
  Serial.print(" pa   |  ");
  Serial.print("Suhu 9 : ");
  Serial.print(suhu_9);
  Serial.println(" C");

  Serial.print("Tekanan 10 : - ");
  Serial.print(" pa   |  ");
  Serial.print("Suhu 10 : ");
  Serial.print(suhu_10);
  Serial.println(" C");


  Serial.println();
  Serial.println();
}

void cek_preasure() {
  Preasure_1 = analogRead(A0);
  Preasure_2 = analogRead(A1);
  Preasure_3 = analogRead(A2);
  Preasure_4 = analogRead(A3);
  Preasure_5 = analogRead(A4);
  Preasure_6 = analogRead(A5);
  Preasure_7 = analogRead(A6);

  scale_Preasure_8.set_scale(calibration_factor);
  Preasure_8 = scale_Preasure_8.get_units(), 4;
  Preasure_8 = Preasure_8 + 230;

  scale_Preasure_9.set_scale(calibration_factor);
  Preasure_9 = scale_Preasure_9.get_units(), 4;
  Preasure_9 = Preasure_9 + 259;
}


void cek_suhu() {
  sensors.requestTemperatures();

  suhu_1 = sensors.getTempC(sensor1);
  suhu_2 = sensors.getTempC(sensor2);
  suhu_3 = sensors.getTempC(sensor3);
  suhu_4 = sensors.getTempC(sensor4);
  suhu_5 = sensors.getTempC(sensor5);
  suhu_6 = sensors.getTempC(sensor6);
  suhu_7 = sensors.getTempC(sensor7);
  suhu_8 = sensors.getTempC(sensor8);
  suhu_9 = sensors.getTempC(sensor9);
  suhu_10 = sensors.getTempC(sensor10);
}

void cek_tegangan() {
  int tegangan = A7;                             // pin signal dari sensor masuk ke pin A0 arduino
  float Vsensor = 0.0;                           //nilai masukan sensor                       //nilai hasil rumus
  float R1 = 30000.0;                            //30k ohm resistor (sesuai dengan nilai resistor di sensor)
  float R2 = 7500.0;                             //7.5k ohm resistor (sesuai dengan nilai resistor di sensor)
  int nilaiTegangan = analogRead(tegangan);      //pembacaan sensor
  Vsensor = (nilaiTegangan * 5.0) / 1024.0;      //rumus mengubah nilai baca sensor
  tegangan_sensor = Vsensor / (R2 / (R1 + R2));  //hasil akhir
}


void cek_arus() {
  int pinADC = A8;
  int sensitivitas = 66;  //tegantung sensor arus yang digunakan, yang ini 30A
  int nilaiadc = 00;
  int teganganoffset = 80;  //nilai pembacaan offset saat tidak ada arus yang lewat
  double tegangan = 00;
  double nilaiarus = 00;
  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas);
  arus_sensor = nilaiarus;
}