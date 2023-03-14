#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

// Set these to run example.
#define FIREBASE_HOST "drug-manage.firebaseio.com"
#define FIREBASE_AUTH "uAkN6v1No6vcKdqedzlAvmFFZKWOv9QLccnfOUOK"
#define WIFI_SSID "nura omar7"
#define WIFI_PASSWORD "777999888"

String myString;
char c;
byte Index1,Index2,Index3,Index4,Index5,Index6,Index7,Index8,Index9;
String NameA, NameB;
String duration1,duration2,quantity1,quantity2,monitor1,monitor2;

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(1000);

  //Firebase.setString("dataRun", "0");
}

int n = 0;

void loop() {

   data_FIREBASE();
   ReadSerial();
  delay(1000);


  // get value
  /* Serial.print("data Run: ");
   Serial.println(Firebase.getString("dataRun"));
   Serial.print("nama: ");
   Serial.println(Firebase.getString("nama"));
   Serial.print("kelamin: ");
   Serial.println(Firebase.getString("jenis kelamin"));
   Serial.print("umur: ");
   Serial.println(Firebase.getString("umur"));
   delay(1000);
   Serial.print("speed: ");
   Serial.println(Firebase.getString("speed"));
   delay(1000);
   Serial.print("durasi: ");
   Serial.println(Firebase.getString("durasi"));
   delay(1000);
  */
  // set string value
  //Firebase.setString("message", "hello world");
  // handle error
}

void ReadSerial(){
    while (Serial.available() > 0)
  {
    delay(10);
    c = Serial.read();
    myString += c;
  }
    if (myString.length() > 0)
    {
      Index1 = myString.indexOf('|');
      Index2 = myString.indexOf('|', Index1 + 1);
      Index3 = myString.indexOf('|', Index2 + 1);
      Index4 = myString.indexOf('|', Index3 + 1);
      Index5 = myString.indexOf('|', Index4 + 1);
      Index6 = myString.indexOf('|', Index5 + 1);
      Index7 = myString.indexOf('|', Index6 + 1);
      Index8 = myString.indexOf('|', Index7 + 1);
      Index9 = myString.indexOf('|', Index8 + 1);
      
      NameA = myString.substring(Index1 + 1, Index2);
      duration1 = myString.substring(Index2 + 1, Index3);
      quantity1 = myString.substring(Index3 + 1, Index4);
      monitor1 = myString.substring(Index4 + 1, Index5);
      
      NameB = myString.substring(Index5 + 1, Index6);
      duration2 = myString.substring(Index6 + 1, Index7);
      quantity2 = myString.substring(Index7 + 1, Index8);
      monitor2 = myString.substring(Index8 + 1, Index9);

      
     Firebase.setString("namaA", NameA);
     Firebase.setString("namaB", NameB);
     
     Firebase.setString("durasiA", duration1);
     Firebase.setString("durasiB", duration2);
     
     Firebase.setString("jumlahA", quantity1);
     Firebase.setString("jumlahB", quantity2);
     
     Firebase.setString("Obat A", monitor1);
     Firebase.setString("Obat B", monitor2);
      
      myString = "";
 }
 
}

//int Index1,Index2;
String Save;
void data_FIREBASE() {
  String Data = "";
  Data += Firebase.getString("save");
  Index1 = Data.indexOf('"');
  Index2 = Data.indexOf('"', Index1 + 1);
  Save = Data.substring(Index1 + 1, Index2);

if(Save == "BARU"){
  Data = "";
  Data += Firebase.getString("namaA");
  Index1 = Data.indexOf('"');
  Index2 = Data.indexOf('"', Index1 + 1);
  NameA = Data.substring(Index1 + 1, Index2);

  Data = "";
  Data += Firebase.getString("namaB");
  Index1 = Data.indexOf('"');
  Index2 = Data.indexOf('"', Index1 + 1);
  NameB = Data.substring(Index1 + 1, Index2);
  
  Data = "";
  Data += Firebase.getString("jumlahA");
  Index1 = Data.indexOf('"');
  Index2 = Data.indexOf('"', Index1 + 1);
  quantity1 = Data.substring(Index1 + 1, Index2);
  
  Data = "";
  Data += Firebase.getString("jumlahB");
  Index1 = Data.indexOf('"');
  Index2 = Data.indexOf('"', Index1 + 1);
  quantity2 = Data.substring(Index1 + 1, Index2);
  
  Data = "";
  Data += Firebase.getString("durasiA");
  Index1 = Data.indexOf('"');
  Index2 = Data.indexOf('"', Index1 + 1);
  duration1 = Data.substring(Index1 + 1, Index2);
  
  Data = "";
  Data += Firebase.getString("durasiB");
  Index1 = Data.indexOf('"');
  Index2 = Data.indexOf('"', Index1 + 1);
  duration2 = Data.substring(Index1 + 1, Index2);

  Data = "";
  Data += "|" + NameA +"|"+ duration1 +"|" + quantity1 +"|" + NameB +"|" + duration2 +"|" + quantity2 +"|"; 
  Serial.println(Data);
  
  delay(1000);
  Firebase.setString("save", "LAMA");
}
}

