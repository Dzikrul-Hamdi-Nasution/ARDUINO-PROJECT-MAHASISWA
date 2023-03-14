#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#define roda_kiri_A 8
#define roda_kiri_B 9
#define roda_kanan_A 10
#define roda_kanan_B 11
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
static const int RXPin = 15, TXPin = 14;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
String data = "";
float latitude, longtitude;
float headingDegrees;
float lintang, bujur;

void setup(void) {
  Serial.begin(9600);
  ss.begin(9600);
  Serial.println("Kompas Test & GPS"); Serial.println("");
  if (!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }
  displaySensorDetails();
  pinMode(roda_kiri_A, OUTPUT);
  pinMode(roda_kiri_B, OUTPUT);
  pinMode(roda_kanan_A, OUTPUT);
  pinMode(roda_kanan_B, OUTPUT);
  Serial.println("tester bluetooth");
  delay(1000);

}

int kunci;
void loop(void) {



  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c != '/') {
      data += c;
    }
    else {
      Serial.println(data);
      lintang = data.toFloat() - latitude;
      //lintang = data.toFloat() - 3.6147422;
      Serial.println(lintang, 7);
      data = "";
    }
  }



  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      if (kunci == 0) {
        displayInfo();
        kompas();
      }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }



  if ((lintang - latitude) > 0.0000025) {
    if (lintang > 0.0000025) {
      if (headingDegrees < 270) {
        digitalWrite(roda_kiri_A, LOW);
        analogWrite(roda_kiri_B, 0);
        digitalWrite(roda_kanan_A, LOW);
        analogWrite(roda_kanan_B, 170);
      }
      else if (headingDegrees > 290) {
        digitalWrite(roda_kiri_A, LOW);
        analogWrite(roda_kiri_B, 170);
        digitalWrite(roda_kanan_A, LOW);
        analogWrite(roda_kanan_B, 0);
      }
      else {
        digitalWrite(roda_kiri_A, LOW);
        analogWrite(roda_kiri_B, 220);
        digitalWrite(roda_kanan_A, LOW);
        analogWrite(roda_kanan_B, 220);
      }
    }
  }
  else {
    digitalWrite(roda_kiri_A, LOW);
    analogWrite(roda_kiri_B, 0);
    digitalWrite(roda_kanan_A, LOW);
    analogWrite(roda_kanan_B, 0);
  }









}


void kompas() {
  sensors_event_t event;
  mag.getEvent(&event);  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = 0.22;
  heading += declinationAngle;

  if (heading < 0)    heading += 2 * PI;


  if (heading > 2 * PI)
    heading -= 2 * PI;

  headingDegrees = heading * 180 / M_PI;
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
  delay(5);
}

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(5);
}


void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    //Serial.print(gps.location.lat(), 6);
    latitude = gps.location.lat();
    //Serial.print(F(","));
    //Serial.print(gps.location.lng(), 6);
    longtitude = gps.location.lng();
    Serial.print(latitude, 7);
    Serial.print("--");
    Serial.println(longtitude, 7);

  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();



}
