#include <Servo.h>
Servo mulut, horizontal, vertikal;
int pos_mulut = 150;
int pos_horizontal = 100;
int pos_vertikal = 90;



void setup() {
  Serial.begin(9600);
  vertikal.attach(13);    //horizontal
  horizontal.attach(26);  //vertikal
  mulut.attach(25);       //mulut

  cek();
}

void loop() {
  int dari_vision = Serial.read();
  if (dari_vision == '1') {
    pos_horizontal = pos_horizontal - 2;
    horizontal.write(pos_horizontal);
    if (pos_horizontal < 70) {
      pos_horizontal = 70;
    }
  }
  if (dari_vision == '2') {
    pos_horizontal = pos_horizontal + 2;
    if (pos_horizontal > 130) {
      pos_horizontal = 130;
    }
    horizontal.write(pos_horizontal);
  }
  if (dari_vision == '4') {
    horizontal.write(100);
  }
  if (dari_vision == '3') {
    berbicara();
  }
  if (dari_vision == '5') {
    mengangguk();
  }
}


void berbicara() {
  for (int i = 0; i <= 10; i++) {
    mulut.write(170);  //buka
    delay(200);
    mulut.write(150);  //tutup
    delay(500);
  }
}

void mengangguk() {
  vertikal.write(90);  //buka
  delay(300);
  vertikal.write(80);  //buka
  delay(600);
  vertikal.write(100);  //tutup
  delay(900);
  vertikal.write(90);  //buka
  delay(200);
}

void cek() {

  horizontal.write(130);  //kiri
  delay(1000);
  horizontal.write(70);  //kanan
  delay(1000);
  horizontal.write(100);  //tengah
  delay(500);
  vertikal.write(100);  //turun
  delay(1000);
  vertikal.write(80);  //naik
  delay(1000);
  vertikal.write(90);  //tengah
  delay(500);
  mulut.write(170);  //buka
  delay(1000);
  mulut.write(150);  //tutup
}