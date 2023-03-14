#include <SPI.h>
#include <LoRa.h>

int sensor_suhu ;
int sensor_kelembapan;
int  sensor_angin ;
int  sensor_tekanan ;
int  sensor_tanah;
int sensor_hujan ;
String data_sensor;

void setup() {
  Serial.begin(9600);


  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  LoRa.beginPacket();
  kirim();
  LoRa.print(data_sensor);
  LoRa.endPacket();
  delay(50);

}


void kirim() {
  sensor_suhu = 45;
  sensor_kelembapan = 20;
  sensor_angin = 100;
  sensor_tekanan = 67;
  sensor_tanah = 23;
  sensor_hujan = 59;

  data_sensor = "*" + String(sensor_suhu) + "," + String(sensor_kelembapan) + "," + String(sensor_angin) + "," + String(sensor_tekanan) + "," + String(sensor_tanah) + "," + String(sensor_hujan) + "#";

  Serial.println(data_sensor);
}

