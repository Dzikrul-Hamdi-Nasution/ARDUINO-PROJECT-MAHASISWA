#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
#include <Servo.h>
int buzzer = 7;
int sensor_pintu = 6;
int tombol = 5;
int relay = 4;
int kunci, kunci_2;
Servo portaL;

void setup () {
  Serial.begin(9600);
  portaL.attach(6);

}


String data;

void loop () {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c != '/') {
      data += c;
    }
    else {
      data = "";
    }
    //lcd.clear();
  }

  if (data == "1") {
    portaL.write(0);//idle
  }
  if (data == "2") {
    portaL.write(90);//idle
  }


}








