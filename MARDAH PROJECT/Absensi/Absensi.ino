#include <LiquidCrystal.h>
const int rs = 14, en = 15, d4 = 16, d5 = 17, d6 = 18, d7 = 19;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <SoftwareSerial.h>
SoftwareSerial SIM800L(5, 4); // RX | TX
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SIM800L.begin(9600);
  lcd.begin(16, 2);
  SPI.begin();      // Initiate  SPI bus

  mfrc522.PCD_Init();   // Initiate MFRC522

  pinMode(7, OUTPUT); //merah
  pinMode(6, OUTPUT); //hijau
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);


}
String data;
void loop() {
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  // put your main code here, to run repeatedly:
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
  lcd.setCursor(0, 0);
  lcd.print("Absensi Wajah");
  lcd.setCursor(0, 1);
  lcd.print("ID : ");
  lcd.setCursor(5, 1);
  lcd.print(data);

  if (data == "1") {
    nomor_1();
  }
  if (data == "2") {
    nomor_2();
  }
  if (data == "3") {
    nomor_3();
  }
  if (data == "4") {
    nomor_4();
  }



  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  //Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "BB 3B 04 7E") //change here the UID of the card/cards that you want to give access
  {
    nomor_1();
  }
  if (content.substring(1) == "EB D5 A3 1C") //change here the UID of the card/cards that you want to give access
  {
    nomor_2();
  }
  if (content.substring(1) == "61 B0 01 1F") //change here the UID of the card/cards that you want to give access
  {
    nomor_3();
  }
  if (content.substring(1) == "FB 09 1C FF") //change here the UID of the card/cards that you want to give access
  {
    nomor_4();
  }

}












void nomor_1() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ID 1 Hadir");
  lcd.setCursor(0, 1);
  lcd.print("Mengirim SMS....");
  SIM800L.write("AT+CMGF=1\r\n");
  delay(1500);
  SIM800L.write("AT+CMGS=\"082297249501\"\r\n");
  delay(1500);
  SIM800L.write("Mahasiswa BANGKIT telah hadir " );
  delay(1500);
  SIM800L.write((char)26);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SMS Terkirim ");
  delay(4000);
  lcd.clear();
  data = "";
}

void nomor_2() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ID 2 Hadir");
  lcd.setCursor(0, 1);
  lcd.print("Mengirim SMS....");
  SIM800L.write("AT+CMGF=1\r\n");
  delay(1500);
  SIM800L.write("AT+CMGS=\"082297249501\"\r\n");
  delay(1500);
  SIM800L.write("Mahasiswa DAVID telah hadir " );
  delay(1500);
  SIM800L.write((char)26);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SMS Terkirim ");
  delay(4000);
  lcd.clear();
  data = "";
}

void nomor_3() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ID 3 Hadir");
  lcd.setCursor(0, 1);
  lcd.print("Mengirim SMS....");
  SIM800L.write("AT+CMGF=1\r\n");
  delay(1500);
  SIM800L.write("AT+CMGS=\"082297249501\"\r\n");
  delay(1500);
  SIM800L.write("Mahasiswa MARDALENA telah hadir " );
  delay(1500);
  SIM800L.write((char)26);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SMS Terkirim ");
  delay(4000);
  lcd.clear();
  data = "";
}

void nomor_4() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ID 4 Hadir");
  lcd.setCursor(0, 1);
  lcd.print("Mengirim SMS....");
  SIM800L.write("AT+CMGF=1\r\n");
  delay(1500);
  SIM800L.write("AT+CMGS=\"082297249501\"\r\n");
  delay(1500);
  SIM800L.write("Mahasiswa WINDA telah hadir " );
  delay(1500);
  SIM800L.write((char)26);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SMS Terkirim ");
  delay(4000);
  lcd.clear();
  data = "";
}
