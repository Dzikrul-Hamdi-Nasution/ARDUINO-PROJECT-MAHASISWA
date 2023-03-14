#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7, D8);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
void setup()  
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\nMendeteksi Fingerpint yang terdaftar");
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Sensor Terdeteksi!");
  } else {
    Serial.println("Sensor Tidak Terdeteksi :(");
    while (1) { delay(1); }
  }
  finger.getTemplateCount();
  Serial.print("Terdapat  "); Serial.print(finger.templateCount); Serial.println(" data sidik jari yang terdaftar");
  Serial.println("Tempatkan Jari Anda...");
}
void loop()                     // run over and over again
{
  //getFingerprintIDez();
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
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
