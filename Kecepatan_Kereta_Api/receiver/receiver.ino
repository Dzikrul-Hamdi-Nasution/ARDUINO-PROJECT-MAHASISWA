#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";
const int sensor_jarak = A0;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    String data_masuk = text;
    Serial.println(data_masuk);
    
  } 
}

void cek_komunikasi() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    String data_masuk = text;
    if (data_masuk == "1") {
      sensorValue = analogRead(sensor_jarak);
      //Serial.println(sensorValue);
      Serial.println("Mulai Hitung");
    } else {
      Serial.println("Selesai");
    }

  }
}
