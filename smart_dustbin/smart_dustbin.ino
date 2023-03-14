#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>
#include <WiFi.h>
#include <Servo.h>

#define FIREBASE_HOST "smart-dustbin-viewer-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "sALSuL5DVz9WvOR8q1azHILIHomGR85Ac147886p"
#define WIFI_SSID "Server Project"
#define WIFI_PASSWORD "Master75wew"
Servo sortir;

char kamera;

const int organik_trigPin = 5;
const int organik_echoPin = 18;

const int non_organik_trigPin = 19;
const int non_organik_echoPin = 21;
int level_organik;
int level_non_organik;
long organik_duration, non_organik_duration;
int organik_distance, non_organik_distance;



void setup() {
  Serial.begin(9600); // Starts the serial communication
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  sortir.attach(2);


  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST);
  pinMode(organik_trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(organik_echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(non_organik_trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(non_organik_echoPin, INPUT); // Sets the echoPin as an Input

  //cek sampah / failsafe
  sortir.write(45);
  delay(2000);
  sortir.write(100);
  delay(2000);
  sortir.write(45);


}

void loop() {
  cek_sensor_organik();
  cek_sensor_non_organik();
  klasifikasi();
  kirim_database();

  kamera = Serial.read();
  if (kamera == '1')
  {
    //organik
    sortir.write(0);
    delay(5000);
    sortir.write(45);
    Serial.flush();
  }
  else if (kamera == '2')
  {
    //non-organik
    sortir.write(100);
    delay(5000);
    sortir.write(45);
    Serial.flush();
  } else {
    //diam
    sortir.write(45);
    Serial.flush();
  }


}

void klasifikasi() {
  if (organik_distance > 40 ) {
    level_organik = 10;
  }
  if (organik_distance > 37 and organik_distance < 40 ) {
    level_organik = 20;
  }
  if (organik_distance > 34 and organik_distance < 37 ) {
    level_organik = 30;
  }
  if (organik_distance > 31 and organik_distance < 34 ) {
    level_organik = 40;
  }
  if (organik_distance > 28 and organik_distance < 31 ) {
    level_organik = 50;
  }
  if (organik_distance > 25 and organik_distance < 28 ) {
    level_organik = 60;
  }
  if (organik_distance > 22 and organik_distance < 25 ) {
    level_organik = 70;
  }
  if (organik_distance > 19 and organik_distance < 22 ) {
    level_organik = 80;
  }
  if (organik_distance > 16 and organik_distance < 19 ) {
    level_organik = 90;
  }
  if (organik_distance < 16 ) {
    level_organik = 100;
  }


  if (non_organik_distance > 40 ) {
    level_non_organik = 10;
  }
  if (non_organik_distance > 37 and non_organik_distance < 40 ) {
    level_non_organik = 20;
  }
  if (non_organik_distance > 34 and non_organik_distance < 37 ) {
    level_non_organik = 30;
  }
  if (non_organik_distance > 31 and non_organik_distance < 34 ) {
    level_non_organik = 40;
  }
  if (non_organik_distance > 28 and non_organik_distance < 31 ) {
    level_non_organik = 50;
  }
  if (non_organik_distance > 25 and non_organik_distance < 28 ) {
    level_non_organik = 60;
  }
  if (non_organik_distance > 22 and non_organik_distance < 25 ) {
    level_non_organik = 70;
  }
  if (non_organik_distance > 19 and non_organik_distance < 22 ) {
    level_non_organik = 80;
  }
  if (non_organik_distance > 16 and non_organik_distance < 19 ) {
    level_non_organik = 90;
  }
  if (non_organik_distance < 16 ) {
    level_non_organik = 100;
  }

}


void kirim_database() {
  Firebase.setInt("organik", level_organik);
  Firebase.setInt("non-organik", level_non_organik);
}




void cek_sensor_organik() {
  digitalWrite(organik_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(organik_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(organik_trigPin, LOW);
  organik_duration = pulseIn(organik_echoPin, HIGH);
  organik_distance = organik_duration * 0.034 / 2;


  Serial.print("Ketinggian Organik: ");
  Serial.println(organik_distance);

}


void cek_sensor_non_organik() {
  digitalWrite(non_organik_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(non_organik_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(non_organik_trigPin, LOW);
  non_organik_duration = pulseIn(non_organik_echoPin, HIGH);
  non_organik_distance = non_organik_duration * 0.034 / 2;


  Serial.print("Ketinggian Non-Organik: ");
  Serial.println(non_organik_distance);

}
