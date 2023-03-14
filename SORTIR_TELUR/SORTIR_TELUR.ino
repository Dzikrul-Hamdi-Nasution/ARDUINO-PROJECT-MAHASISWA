#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define WIFI_SSID "Galaxy A7118D6"
#define WIFI_PASSWORD "eben1234"


char auth[] = "Fif1an148Lo_W5h26ZoK-YDAoN_pScrO";       // You should get Auth Token in the Blynk App.
char ssid[] = "Server Project";                    // Your Wi-Fi Credentials
char pass[] = "Master75wew";

int y = 0;
String dataIn;
String dt[10];
int i;
boolean parsing = false;


void setup() {

  Serial.begin(9600);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Blynk.begin("Fif1an148Lo_W5h26ZoK-YDAoN_pScrO", ssid, pass);

  Blynk.virtualWrite(V1, "add", 1, "telur busuk", "-");
  Blynk.virtualWrite(V1, "add", 2, "telur super", "60");
  Blynk.virtualWrite(V1, "add", 3, "telur baik", "57");
  Blynk.virtualWrite(V1, "add", 4, "telur super", "60");
  Blynk.virtualWrite(V1, "add", 5, "telur super", "61");
  Blynk.virtualWrite(V1, "add", 6, "telur super", "63");
  Blynk.virtualWrite(V1, "add", 7, "telur busuk", "-");
  Blynk.virtualWrite(V1, "add", 8, "telur busuk", "-");
  Blynk.virtualWrite(V1, "add", 9, "telur busuk", "-");
  Blynk.virtualWrite(V1, "add", 10, "telur baik", "49");

}

int urut;
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



void parsingData()
{

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

  Blynk.run();
  Blynk.virtualWrite(V1, "add", urut, dt[0], dt[1]);

  urut++;


}
