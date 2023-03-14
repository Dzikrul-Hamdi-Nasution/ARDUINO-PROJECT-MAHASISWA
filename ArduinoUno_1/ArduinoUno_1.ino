#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Servo.h>
Servo servoku;
int pos = 0;
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);


#define trigpin 4
#define echopin 2
int duration, distance;
int ledlow = 5;
int ledmiddle = 6;
int ledhigh = 7;


void setup() {
  Serial.begin(9600);
  lcd.begin();
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(ledlow, OUTPUT);
  pinMode(ledmiddle, OUTPUT);
  pinMode(ledhigh, OUTPUT);

  mySerial.begin(9600); //Setting the baud rate of GSM Module
  delay(100);
  mySerial.println("AT");
  mySerial.println("AT+CMGF=1");
  mySerial.println("AT+CNMI=1,2,0,0,0");
  //SendSMSAwal();
  //delay(1000);

  digitalWrite(ledlow, LOW);
  digitalWrite(ledmiddle, LOW);
  digitalWrite(ledhigh, LOW);
  servoku.attach(9);
  delay(1000);
}

void loop() {
  datasenttoesp8266();
  delay(100);
  serialgsm();
}


void serialgsm() {
  ///Setup Serial GSM
  if (mySerial.available() > 0)
  {
    Serial.write(mySerial.read());
  }

  if (  (distance > 0) && (distance <= 5)  ) //Level Siaga
  {

    digitalWrite(ledlow, LOW);
    digitalWrite(ledmiddle, LOW);
    digitalWrite(ledhigh, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Status Siaga ");
    servoku.write(180);
    delay(500);
  }
  if (  (distance > 5) && (distance <= 10)  ) //Level Waspada
  {
    digitalWrite(ledlow, LOW);
    digitalWrite(ledmiddle, HIGH);
    digitalWrite(ledhigh, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status Waspada ");
  }
  if (  (distance > 10) && (distance <=15)   ) //Level Normal
  {
    digitalWrite(ledlow, HIGH);
    digitalWrite(ledmiddle, LOW);
    digitalWrite(ledhigh, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status Normal ");
    servoku.write(-180);
  }
  if (distance < 5) {
    SendSMSBuka();
  }
  if (distance == 15) {
    SendSMSTutup();
  }
  delay(500);
}
void SendSMSBuka()
{
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"081269637323\"\r"); ///Replace x with mobile number
  delay(1000);
  mySerial.println("PINTU AIR TERBUKA"); ///The SMS text you want to send
  delay(100);
  mySerial.println((char)26);  ////ASCII code of CTRL+Z
  delay(1000);
}
void SendSMSTutup()
{
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"081269637323\"\r"); ///Replace x with mobile number
  delay(1000);
  mySerial.println("PINTU AIR TUTUP"); ///The SMS text you want to send
  delay(100);
  mySerial.println((char)26);  ////ASCII code of CTRL+Z
  delay(1000);
}

void datasenttoesp8266() {
  digitalWrite(trigpin, HIGH);

  delayMicroseconds(1000);
  digitalWrite(trigpin, LOW);


  duration = pulseIn(echopin, HIGH);

  distance = ( duration / 2) / 29.1;
  //Serial.print("cm:");
  Serial.println(distance);


  lcd.setCursor(0, 0);
  lcd.print("Tinggi Air=");
  lcd.print(distance);       //Menampilkan jarak pada LCD 16x2
  lcd.print(" cm ");
}
