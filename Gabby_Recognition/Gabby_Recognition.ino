#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#define FIREBASE_HOST "absensi-suhu-pegawai-default-rtdb.firebaseio.com"
#define WIFI_SSID "Server Project"
#define WIFI_PASSWORD "Master75wew"


int y = 0;
String dataIn;
String dt[10];
int i;
boolean parsing = false;

void setup() {
  Serial.begin(9600);
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
  Firebase.begin(FIREBASE_HOST);

}

String nama, devisi, denda, status_hadir, suhu, waktu, hari;

int kunci = 0;



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
    parsing = false;
    dataIn = "";
  }

}

void kirim() {



  String id_hari = hari;
  int randNumber = random(300);
  String id = String(randNumber) ;

  Serial.println("mengirim data");

  Firebase.setString(id_hari + "/" + id + "/" + "nama", nama);
  //Firebase.setString(id_hari + "/" + id + "/" + "devisi", devisi);
  Firebase.setString(id_hari + "/" + id + "/" + "denda", denda);
  Firebase.setString(id_hari + "/" + id + "/" + "keterangan", status_hadir);
  Firebase.setString(id_hari + "/" + id + "/" + "suhu", suhu);
  Firebase.setString(id_hari + "/" + id + "/" + "waktu", waktu);

  int tampung = Firebase.getInt("data_karyawan/" + nama + "/total_denda");
  int tampung2 = tampung / 1000;
  int update_denda = tampung2 + (denda.toInt() / 1000);
  Firebase.setInt("data_karyawan/" + nama + "/total_denda", update_denda * 1000);

  delay(1000);

  /*
    do {
      if (Serial.available() > 0)
      {
        char inChar = (char)Serial.read();
        if (inChar == '-') {
          kunci = 500;
        }
      }
      Serial.println("menunggu reset");
    } while (kunci < 200);
  */


}


void parsingData()
{
  kunci = 0;
  int j = 0;
  //kirim data yang telah diterima sebelumnya
  //Serial.print("data masuk : ");
  //Serial.print(dataIn);
  //Serial.print("\n");
  //inisialisasi variabel, (reset isi variabel)
  dt[j] = "";
  //proses parsing data
  for (i = 1; i < dataIn.length(); i++)
  {
    //pengecekan tiap karakter dengan karakter (#) dan (,)
    if ((dataIn[i] == '#') || (dataIn[i] == ','))
    {
      //increment variabel j, digunakan untuk merubah index array penampung
      j++;
      dt[j] = ""; //inisialisasi variabel array dt[j]
    }
    else
    {
      //proses tampung data saat pengecekan karakter selesai.
      dt[j] = dt[j] + dataIn[i];
    }
  }

  nama = dt[0];
  devisi = dt[1];
  suhu = dt[2];
  waktu = dt[3];
  denda = dt[4];
  hari = dt[5];
  status_hadir = dt[6];

  kirim();

}
