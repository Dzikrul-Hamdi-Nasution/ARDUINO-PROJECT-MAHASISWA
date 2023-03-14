#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>



#define FIREBASE_HOST "test-iot-kos.firebaseio.com"
#define FIREBASE_AUTH "EVxPSBXAeKBPh46gGxMdMBUYzcBF4swWVJQxp50p"
//#define WIFI_SSID "KampungTongah"
//#define WIFI_PASSWORD "sayasiapaya"

#define WIFI_SSID "SALAM ELECTRONICS"
#define WIFI_PASSWORD "btn-primary"

String data2;

void setup() {
  
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {

  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c != '/') {
      data2 += c;
    }
    else {
      data2 = "";
    }
  }

  if (data2 == "b") {
    Firebase.setString("portal masuk/nilai", "0");
  }
  if (data2 == "c") {
    Firebase.setString("portal keluar/nilai", "0");
  }

  if (Firebase.getString("portal masuk/nilai") == ("1")) {
    Serial.print("a/");//kirim data serial utk buka portal masuk ke arduino melalui software serial
    if (Firebase.getString("yang dipilih/nilai") == ("1")) {
      Serial.print("a/");
      Serial.print("1/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("2")) {
      Serial.print("a/");
      Serial.print("2/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("3")) {
      Serial.print("a/");
      Serial.print("3/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("4")) {
      Serial.print("a/");
      Serial.print("4/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("5")) {
      Serial.print("a/");
      Serial.print("5/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("6")) {
      Serial.print("a/");
      Serial.print("6/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("7")) {
      Serial.print("a/");
      Serial.print("7/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    if (Firebase.getString("yang dipilih/nilai") == ("8")) {
      Serial.print("a/");
      Serial.print("8/");
      Firebase.setString("portal masuk/nilai", "0");
    }
    Serial.print("a/");
  }

  if (Firebase.getString("portal keluar/nilai") == ("A")) {
    Serial.print("1/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("1/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("B")) {
    Serial.print("2/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("2/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("C")) {
    Serial.print("3/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("3/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("D")) {
    Serial.print("4/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("4/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("E")) {
    Serial.print("5/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("5/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("F")) {
    Serial.print("6/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("6/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("G")) {
    Serial.print("7/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("7/");
  }
  if (Firebase.getString("portal keluar/nilai") == ("H")) {
    Serial.print("8/");//kirim data serial utk buka portal keluar ke arduino melalui software serial
    Firebase.setString("portal keluar/nilai", "0");
    Serial.print("8/");
  }



}
