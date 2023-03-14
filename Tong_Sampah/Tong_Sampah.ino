
#include <Servo.h>
#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>
#include <WiFi.h>
#define FIREBASE_HOST "tong-sampah-usu-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "v2sgMWbVi144TLtmvfUON9c7pwV3dXMGLGF2LHQr"
#define WIFI_SSID "Server Project"
#define WIFI_PASSWORD "Master75wew"

int y = 0;
Servo myservo;
const int buttonPin = 4;
int buttonState = 0;
void setup() {
  Serial.begin(9600);
  myservo.attach(13);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    y++;
    if (y > 30) {
      break;
      y = 0;
    }
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(buttonPin, INPUT);
  // initialize the LED pin as an output

}

void loop() {


  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);



  if (buttonState == HIGH) {
    // turn LED on:
    myservo.write(90);//buka
  }
  if (buttonState == LOW) {
    // turn LED off:
    myservo.write(180);//tutup
    delay(2000);
  }

}
