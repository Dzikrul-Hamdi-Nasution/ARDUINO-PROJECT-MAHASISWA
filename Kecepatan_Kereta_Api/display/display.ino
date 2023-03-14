#include <SPI.h>  //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial_Black_16.h>



String pesanDisplay;
float dataIn;
const int WIDTH = 1;  // jumlah panel led matrik yang digunakan
SoftDMD dmd(WIDTH, 1);
DMD_TextBox box(dmd);
int buzzer = 12;
int detik;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  dmd.setBrightness(40);
  dmd.selectFont(Arial_Black_16);
  dmd.begin();
  dmd.fillScreen(true);
  dmd.drawString(2, 0, "------", GRAPHICS_INVERSE);
  Serial.println("Receiver");
}

void loop() {

  if (Serial.available()) {
    dataIn = Serial.parseFloat();

    detik = 500 / dataIn;
    pesanDisplay = String(detik);
    dmd.fillScreen(true);
    dmd.drawString(2, 0, pesanDisplay, GRAPHICS_INVERSE);
    hitung_mundur();
    dataIn = 0;
  }
}



void hitung_mundur() {

  int perulangan = detik;
  for (int i = perulangan; i > 0; i--) {
    pesanDisplay = String(i);
    digitalWrite(buzzer, LOW);
    dmd.fillScreen(true);
    dmd.drawString(2, 0, pesanDisplay, GRAPHICS_INVERSE);
    delay(500);
    digitalWrite(buzzer, HIGH);
    delay(500);
  }
}