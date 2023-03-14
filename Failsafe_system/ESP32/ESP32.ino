#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>
#include <WiFi.h>

#define FIREBASE_HOST "failsafe-system-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "ygSByBmWYn6RJGXeJf0sc0D0azq5Jdg1ewQ4GAJz"
#define WIFI_SSID "Server Project"
#define WIFI_PASSWORD "Master75wew"

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TimeLib.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", 25200, 60000);
char Time[ ] = "00:00:00";
char Date[ ] = "00-00-2000";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;

String dataIn, waktu, trouble_pod_1, trouble_pod_2, trouble_pod_3, trouble_pod_4, trouble_pod_5;
String dt[10];
int i;
boolean parsing = false;

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST);


  timeClient.begin();

}

void loop() {

  if (Serial.available() > 0)
  {
    char inChar = (char)Serial.read();
    dataIn += inChar;
    if (inChar == '\n') {
      parsing = true;
    }
  }
  if (parsing)
  {
    parsingData();
    upload_data();
    history();
    parsing = false;
    dataIn = "";
  }



  printLocalTime();


}


void history() {

  Firebase.setString("history/pod_1/" + waktu + "/hari", waktu); //pod 1 hari
  Firebase.setString("history/pod_1/" + waktu + "/trouble", trouble_pod_1); //pod 1 trouble

  Firebase.setString("history/pod_2/" + waktu + "/hari", waktu); //pod 2 hari
  Firebase.setString("history/pod_2/" + waktu + "/trouble", trouble_pod_2); //pod 2 trouble

  Firebase.setString("history/pod_3/" + waktu + "/hari", waktu); //pod 3 hari
  Firebase.setString("history/pod_3/" + waktu + "/trouble", trouble_pod_3); //pod 3 trouble

  Firebase.setString("history/pod_4/" + waktu + "/hari", waktu); //pod 4 hari
  Firebase.setString("history/pod_4/" + waktu + "/trouble", trouble_pod_4); //pod 4 trouble

  Firebase.setString("history/pod_5/" + waktu + "/hari", waktu); //pod 5 hari
  Firebase.setString("history/pod_5/" + waktu + "/trouble", trouble_pod_5); //pod 5 trouble

}


void upload_data() {


  Firebase.setString("sensor/pod_1/kondisi_blade", dt[0]);
  Firebase.setString("sensor/pod_2/kondisi_blade", dt[1]);
  Firebase.setString("sensor/pod_3/kondisi_blade", dt[2]);
  Firebase.setString("sensor/pod_4/kondisi_blade", dt[3]);
  Firebase.setString("sensor/pod_5/kondisi_blade", dt[4]);

  Firebase.setString("sensor/pod_1/kondisi_selenoid", dt[5]);
  Firebase.setString("sensor/pod_2/kondisi_selenoid", dt[6]);
  Firebase.setString("sensor/pod_3/kondisi_selenoid", dt[7]);
  Firebase.setString("sensor/pod_4/kondisi_selenoid", dt[8]);
  Firebase.setString("sensor/pod_5/kondisi_selenoid", dt[9]);

}


void parsingData()
{

  int j = 0;

  dt[j] = "";

  for (i = 1; i < dataIn.length(); i++)
  {
    if ((dataIn[i] == '#') || (dataIn[i] == ','))
    {
      j++;
      dt[j] = ""; //inisialisasi variabel array dt[j]
    }
    else
    {
      dt[j] = dt[j] + dataIn[i];
    }
  }
  printLocalTime();



  if (dt[0] == "1") {
    if (dt[5] == "1") {
      trouble_pod_1 = "Blade & Selenoid";
    } else {
      trouble_pod_1 = "Blade";
    }
  } else if (dt[5] == "1") {
    trouble_pod_1 = "Selenoid";
  } else {
    trouble_pod_1 = "-";
  }

  if (dt[1] == "1") {
    if (dt[6] == "1") {
      trouble_pod_2 = "Blade & Selenoid";
    } else {
      trouble_pod_2 = "Blade";
    }
  } else if (dt[6] == "1") {
    trouble_pod_2 = "Selenoid";
  } else {
    trouble_pod_2 = "-";
  }


  if (dt[2] == "1") {
    if (dt[7] == "1") {
      trouble_pod_3 = "Blade & Selenoid";
    } else {
      trouble_pod_3 = "Blade";
    }
  } else if (dt[7] == "1") {
    trouble_pod_3 = "Selenoid";
  } else {
    trouble_pod_3 = "-";
  }


  if (dt[3] == "1") {
    if (dt[8] == "1") {
      trouble_pod_4 = "Blade & Selenoid";
    } else {
      trouble_pod_4 = "Blade";
    }
  } else if (dt[8] == "1") {
    trouble_pod_4 = "Selenoid";
  } else {
    trouble_pod_4 = "-";
  }

  if (dt[4] == "1") {
    if (dt[9] == "1") {
      trouble_pod_5 = "Blade & Selenoid";
    } else {
      trouble_pod_5 = "Blade";
    }
  } else if (dt[9] == "1") {
    trouble_pod_5 = "Selenoid";
  } else {
    trouble_pod_5 = "-";
  }



}


void printLocalTime()
{

  timeClient.update();
  unsigned long unix_epoch = timeClient.getEpochTime();    // Get Unix epoch time from the NTP server

  second_ = second(unix_epoch);
  if (last_second != second_) {


    minute_ = minute(unix_epoch);
    hour_   = hour(unix_epoch);
    day_    = day(unix_epoch);
    month_  = month(unix_epoch);
    year_   = year(unix_epoch);



    Time[7] = second_ % 10 + 48;
    Time[6] = second_ / 10 + 48;
    Time[4]  = minute_ % 10 + 48;
    Time[3]  = minute_ / 10 + 48;
    Time[1]  = hour_   % 10 + 48;
    Time[0]  = hour_   / 10 + 48;



    Date[0]  = day_   / 10 + 48;
    Date[1]  = day_   % 10 + 48;
    Date[3]  = month_  / 10 + 48;
    Date[4]  = month_  % 10 + 48;
    Date[8] = (year_   / 10) % 10 + 48;
    Date[9] = year_   % 10 % 10 + 48;

    String hari_online = Date;
    String jam_online = Time;
    waktu = hari_online + "-" + jam_online;
    Serial.println(waktu);

  }
}
