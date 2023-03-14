#include <SoftwareSerial.h>
String data;
int a, b, c;
SoftwareSerial s(11, 12);

void setup() {
  pinMode(5, OUTPUT);//pompa air
  pinMode(4, OUTPUT);//pembuangan
  pinMode(3, OUTPUT);//motor kanan
  pinMode(2, OUTPUT);//motor kiri
  Serial.begin(9600);
  s.begin(9600);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);

}

void loop() {
  if (s.available() > 0) {
    char c = s.read();
    if (c != '/') {
      data += c;
    }
    else {
      data = "";
    }
  }
  if (data == "1") {
    digitalWrite(5, HIGH);
  }
  if (data == "0") {
    digitalWrite(5, LOW);
  }

  if (data == "C") {
    for (a = 0; a =107 ; a ++) {
      digitalWrite(3, HIGH);
      delay(5000);
      digitalWrite(3, LOW);
      delay(2000);
      digitalWrite(2, HIGH);
      delay(5000);
      digitalWrite(2, LOW);
      delay(2000);
    }
    digitalWrite(4, HIGH);
    delay(60000);
    digitalWrite(4, LOW);
  }

  if (data == "B") {
    digitalWrite(4, HIGH);
  }

  if (data == "D") {
    for (c = 0; c = 9 ; c ++) {
      digitalWrite(3, HIGH);
      delay(5000);
      digitalWrite(3, LOW);
      delay(2000);
      digitalWrite(2, HIGH);
      delay(5000);
      digitalWrite(2, LOW);
      delay(2000);
    }
    digitalWrite(4, HIGH);
    delay(60000);
    digitalWrite(4, LOW);
    
  }




  if (data == "K") {

    digitalWrite(4, HIGH);
    digitalWrite(3, HIGH);
    delay(90000);

    digitalWrite(3, LOW);
    delay(15000);


    digitalWrite(2, HIGH);
    delay(80000);

    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
  }

}

