#include <Servo.h>
Servo sensing;
long duration, jarak;
int kiri_status, kanan_status, cek = 0;
#define triggerPin  10
#define echoPin     11

#define roda_kanan_A 7
#define roda_kanan_B 6  //pwm

#define roda_kiri_B 4
#define roda_kiri_A 5 //pwm

void setup() {
  Serial.begin(9600);
  sensing.attach(9);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(roda_kiri_A, OUTPUT);
  pinMode(roda_kiri_B, OUTPUT);
  pinMode(roda_kanan_A, OUTPUT);
  pinMode(roda_kanan_B, OUTPUT);
  sensing.write(90); //hadap depan
  delay(1000);
  sensing.write(180); //hadap kiri
  delay(1000);
  sensing.write(0); //hadap kanan
  delay(2000);
  sensing.write(90); //hadap depan


}

void loop() {
  cek_jarak();

  if (jarak < 12) {
    berhenti();
    delay(1500);
    sensing.write(180); //Cek kiri
    kiri_status = 0;
    cek = 1;
    delay(1000);
    cek_jarak();
    if (jarak > 12) {
      kiri_status = 0;
    }
    else {
      kiri_status = jarak;
    }

    sensing.write(0); //Cek kanan
    kanan_status = 0;
    cek = 2;
    delay(1000);
    cek_jarak();
    if (jarak > 12) {
      kanan_status = 0;
    }
    else {
      kanan_status = jarak;
    }
    sensing.write(90);
    delay(1000);
    if (kiri_status > kanan_status) {
      belok_kanan();
      kanan_status = 0;
      kiri_status = 0;
      Serial.println("Belok kanan");
    } else {
      belok_kiri();
      kanan_status = 0;
      kiri_status = 0;
      Serial.println("Belok Kiri");
    }
    berhenti();
    delay(1000);
  }
  else {
    maju_lurus();
    //Serial.println("Maju Lurus");
    kanan_status = 0;
    kiri_status = 0;
    cek = 0;
  }







}

void belok_kanan() {
  analogWrite(roda_kanan_B, 100);
  digitalWrite(roda_kanan_A, HIGH);
  analogWrite(roda_kiri_A, 100);
  digitalWrite(roda_kiri_B, LOW);
  delay(400);
}

void belok_kiri() {
  analogWrite(roda_kanan_B, 115);
  digitalWrite(roda_kanan_A, LOW);
  analogWrite(roda_kiri_A, 100);
  digitalWrite(roda_kiri_B, HIGH);
  delay(400);
}

void maju_lurus() {
  analogWrite(roda_kanan_B, 120);
  digitalWrite(roda_kanan_A, HIGH);
  analogWrite(roda_kiri_A, 120);
  digitalWrite(roda_kiri_B, HIGH);
}

void berhenti() {
  analogWrite(roda_kanan_B, 255);
  digitalWrite(roda_kanan_A, HIGH);
  analogWrite(roda_kiri_A, 255);
  digitalWrite(roda_kiri_B, HIGH);
}






void cek_jarak() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = (duration / 2) / 29.1;
  /*
    if (cek == 1) {
    Serial.print("jarak kiri :");
    Serial.print(jarak);
    Serial.println(" cm");
    }
    else if (cek == 2) {
    Serial.print("jarak kanan :");
    Serial.print(jarak);
    Serial.println(" cm");
    } else {
    Serial.print("jarak :");
    Serial.print(jarak);
    Serial.println(" cm");
    }
  */


  delay(10);
}
