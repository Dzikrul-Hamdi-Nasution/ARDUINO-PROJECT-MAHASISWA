#include <TinyGPS++.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
#define FIREBASE_HOST "monitoring-tegangan-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "ZyeExvG8VOrIvPQGClWAwoJ3473vV9gkHVRAGihA"
//#define WIFI_SSID "Linux Wpa2"
//#define WIFI_PASSWORD "qwerty12345"
#define WIFI_SSID "Server Project"
#define WIFI_PASSWORD "Salamproject2022"
#define relay_kontrol D5
String dataIn;
String dt[10];
int i, batas;
boolean parsing = false;
String data;

String set_arus, set_suhu, set_kwh, manual, relay_db, set_tegangan_min, set_tegangan_max;

void setup()
{

  Serial.begin(9600);
  pinMode(relay_kontrol, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  digitalWrite(relay_kontrol, LOW);
  Serial.println("Connected...");

}

int x;

void loop()
{

}
