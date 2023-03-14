#include <SoftwareSerial.h>
const int buzzer = 8;
const int relay = 9;
String Jevois ;
String dataIn;

SoftwareSerial Jevois_data(4, 3); // RX, TX

void setup() {
  Serial.begin(115200);
  Jevois_data.begin(115200);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(relay, LOW);
  delay(2000);
  digitalWrite(buzzer, HIGH);
  digitalWrite(relay, HIGH);
}

void loop() {
  //alarm();

  int dari_jevois = Jevois_data.parseInt();
  if (dari_jevois == 1) {
    while (dari_jevois == 1) {
      dari_jevois = Jevois_data.parseInt();
      Serial.println("Akses Diterima");
      pinMode(relay, HIGH);
      delay(100);
    }
    delay(3000);
    dari_jevois = 0;
  } else {
    Serial.println("Akses Ditolak");
    pinMode(relay, LOW);
  }






}

void alarm() {
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(100);

}
