#include <Servo.h>
Servo tuas_kiri;
Servo tuas_kanan;

void setup() {
  // put your setup code here, to run once:
  tuas_kiri.attach(5);
  tuas_kanan.attach(6);
  pinMode(12, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(12) == 0) {
    tuas_kanan.write(190);
    tuas_kiri.write(700);
  }
  if (digitalRead(12) == 1) {
    tuas_kanan.write(700);
    tuas_kiri.write(190);
  }
 

}
