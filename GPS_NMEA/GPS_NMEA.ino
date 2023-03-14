#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Fingerprint.h>
#include "CTBot.h"                                                  // Memanggil library CTBot
CTBot myBot;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(14, 12);

SoftwareSerial fingerprint_sensor(13, 15);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerprint_sensor);
uint8_t id;

String ssid  = "Server Project";
String pass  = "Master75wew";
String token = "5597830843:AAG4eH4zmopRdrXQAz20O9VLgY73N2skZZQ";

String bujur, timur;
int year , month , date, hour , minute , second;
String DateString , TimeString , LatitudeString , LongitudeString;

int relay = 5;

WiFiServer server(80);
void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(9600);
  finger.begin(57600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  Serial.println();
  Serial.print("Connecting");
  myBot.wifiConnect(ssid, pass);                                     // Menghubungkan ke jaringan internet
  myBot.setTelegramToken(token);                                     // Menghubungkan ke telegram
  if (myBot.testConnection()) {                                      // Jika terhubung dengan jaringan internet, maka
    Serial.println("System Online ");                           // Tampil "testConnection OK" pada serial monitor
    myBot.sendMessage(1441844129, "System Online");
  } else {
    Serial.println("System OFFLINE ");
    delay(3000);
  }
  digitalWrite(relay, LOW);
}


void loop() {

  //ENROLL();
  getFingerprintID();


  cek_gps();
  TBMessage msg;



  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("cek")) {
      myBot.sendMessage(msg.sender.id, "https://www.google.com/maps/place/" + bujur + "," + timur);
      Serial.println("Mengirim Lokasi");
    }
    if (msg.text.equalsIgnoreCase("on")) {
      digitalWrite(relay, HIGH);
      Serial.println("Aktifkan Relay");
    }
    if (msg.text.equalsIgnoreCase("off")) {
      digitalWrite(relay, LOW);
      Serial.println("Non-Aktifkan Relay");
    }
  }

}


void cek_gps() {
  if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print(F("- latitude: "));
        bujur = gps.location.lat();
        Serial.println(bujur);
        timur = gps.location.lng();
        Serial.print(F("- longitude: "));
        Serial.println(timur);

        Serial.print(F("- altitude: "));
        if (gps.altitude.isValid())
          Serial.println(gps.altitude.meters());
        else
          Serial.println(F("INVALID"));
      } else {
        Serial.println(F("- location: INVALID"));
      }


      Serial.println();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}






uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  // OK success!
  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("ID yang ditemukan #"); Serial.print(finger.fingerID);
  Serial.print(" dengan ketepatan "); Serial.println(finger.confidence);
  return finger.fingerID;
}
