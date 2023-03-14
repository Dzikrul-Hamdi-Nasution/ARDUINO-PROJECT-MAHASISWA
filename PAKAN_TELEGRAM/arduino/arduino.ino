#include <Servo.h>
Servo servo_takaran, servo_utama;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo_takaran.attach(9); //D3
  servo_utama.attach(10); //D4
  servo_takaran.write(90);
  servo_utama.write(90);
  delay(1500);
  servo_takaran.write(175); //tutup
  servo_utama.write(174); //tutup
}

void loop() {
  // put your main code here, to run repeatedly:
  int jam_makan = Serial.parseInt();
  if(jam_makan==1){
    proses_pakan();
  }
}

void proses_pakan() {
  Serial.println("Membuka katup takaran");
  servo_takaran.write(90);
  servo_utama.write(174);
  delay(5000);
  Serial.println("Membuka katup buang");
  servo_takaran.write(175);
  servo_utama.write(90);
  delay(5000);
  servo_utama.write(174);
  servo_takaran.write(175);
}
