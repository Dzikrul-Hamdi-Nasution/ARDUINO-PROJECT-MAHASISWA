#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>


Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
float latitude, longtitude;
float headingDegrees;
String data;


void setup() {
  Serial.begin (9600); //inisialiasasi komunikasi serial
  ss.begin(GPSBaud);
  if (!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }
  displaySensorDetails();




}



void loop(void) {

  
  

  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
  kompas();


  Serial.print(headingDegrees);
  Serial.print("/");
  Serial.print(latitude, 7);
  Serial.print("/");
  Serial.print(longtitude, 7);
  Serial.println("@");




}








void kompas() {
  sensors_event_t event;
  mag.getEvent(&event);  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = 0.22;
  heading += declinationAngle;

  if (heading < 0)
    heading += 2 * PI;


  if (heading > 2 * PI)
    heading -= 2 * PI;

  headingDegrees = heading * 180 / M_PI;
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);

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

  latitude = gps.location.lat();
  longtitude = gps.location.lng();
  Serial.print(latitude, 6);
  Serial.print("--");
  Serial.println(longtitude, 6);
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
  delay(500);
}
