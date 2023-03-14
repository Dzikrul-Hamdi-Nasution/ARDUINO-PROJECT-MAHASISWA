#include<SoftwareSerial.h>
#include <TinyGPS++.h>
//SoftwareSerial mySerial(8, 9); // (Rx,Tx  > Tx,Rx)
//SoftwareSerial gps_tracker(2, 3);
SoftwareSerial mySerial(2, 3); // (Rx,Tx  > Tx,Rx)
SoftwareSerial gps_tracker(8, 9);
int t_alarm = 5, t_mati = 6, buzzer = 4;
TinyGPSPlus gps;
char incomingByte;
String inputString;
String latitude, longtitude;
int relay = 4;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  //gps_tracker.begin(9600);
  
    while (!mySerial.available()) {
      mySerial.println("AT");
      delay(1000);
     // Serial.println("Connecting...");
    }
  
 // Serial.println("Connected!");
  mySerial.println("AT+CMGF=1");  //Set SMS to Text Mode
  delay(1000);
  mySerial.println("AT+CNMI=1,2,0,0,0");  //Procedure to handle newly arrived messages(command name in text: new message indications to TE)
  delay(1000);
  mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read Unread Messages
  pinMode(t_alarm, INPUT);
  pinMode(t_mati, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);

}

void loop()
{

  if (mySerial.available() > 0) {
    delay(100);

    // Serial Buffer
    while (mySerial.available() > 0) {
      incomingByte = mySerial.read();
      inputString += incomingByte;
      cek_tombol();
      cek_gps();
    }
    delay(10);
    //Serial.println(inputString);
    inputString.toUpperCase(); // Uppercase the Received Message

    //turn RELAY ON or OFF
    if (inputString.indexOf("OFF") > -1) {
      digitalWrite(buzzer, HIGH);
      mySerial.println("AT+CMGDA=\"DEL ALL\"");
    }
    if (inputString.indexOf("ON") > -1) {
      digitalWrite(buzzer, LOW);
      mySerial.println("AT+CMGDA=\"DEL ALL\"");
    }
    if (inputString.indexOf("YOP") > -1) {
      cek_gps();
      //Serial.print("Mengirim SMS....");
      mySerial.write("AT+CMGF=1\r\n");
      delay(1000);
      mySerial.write("AT+CMGS=\"08163144166\"\r\n");
      delay(1000);
      //https://maps.google.com/maps?q=loc:3.614664,98.664978
      mySerial.print("https://maps.google.com/maps?q=loc:");
      mySerial.print(latitude);
      mySerial.print(",");
      mySerial.print(longtitude);
      delay(1000);
      mySerial.write((char)26);
      delay(1000);
      // Serial.print(" SMS Terkirim ");
      mySerial.println("AT+CMGDA=\"DEL ALL\"");
    }

    delay(50);

    //Delete Messages & Save Memory

    inputString = "";
  }
  cek_tombol();
  cek_gps();

}







void cek_gps() {
  while (Serial.available() > 0) {
    gps.encode(Serial.read());
    if (gps.location.isUpdated()) {
      latitude = String(gps.location.lat(), 6);
      longtitude = String(gps.location.lng(), 6);
    }
  }
}


void cek_tombol() {
  if (digitalRead(t_alarm) == HIGH) {
    digitalWrite(buzzer, LOW);
  }
  if (digitalRead(t_mati) == HIGH) {
    cek_gps();
    mySerial.write("AT+CMGF=1\r\n");
    delay(1000);
    mySerial.write("AT+CMGS=\"08163144166\"\r\n");
    delay(1000);
    //https://maps.google.com/maps?q=loc:3.614664,98.664978
    mySerial.print("https://maps.google.com/maps?q=loc:");
    mySerial.print(latitude);
    mySerial.print(",");
    mySerial.print(longtitude);
    delay(1000);
    mySerial.write((char)26);
    delay(1000);
    // Serial.print(" SMS Terkirim ");
    mySerial.println("AT+CMGDA=\"DEL ALL\"");
    digitalWrite(buzzer, HIGH);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(2000);
  }
}
