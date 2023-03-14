#include <SPI.h>
#include <LoRa.h>

#define ss 5
#define rst 0
#define dio0 4

String dataIn;
String dt[10];
int i;
boolean parsing = false;

String inString = "";    // string to hold input


void setup() {
  Serial.begin(9600);
  while (!Serial);
  LoRa.setPins(ss, rst, dio0);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {

  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // read packet
    while (LoRa.available())
    {
      char inChar = LoRa.read();
      dataIn += inChar;
      if (inChar == '\n') {
        parsing = true;
      }
    }
    inString = "";
    LoRa.packetRssi();
  }
  if (parsing)
  {
    parsingData();
    dataIn = "";
  }


  //delay(1000);
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

  Serial.print("Sensor Suhu ");
  Serial.println(dt[0]);
  Serial.print("Sensor Kelembapan ");
  Serial.println(dt[1]);
  Serial.print("Sensor Angin ");
  Serial.println(dt[2]);
  Serial.print("Sensor Tekanan ");
  Serial.println(dt[3]);
  Serial.print("Sensor Tanah ");
  Serial.println(dt[4]);
  Serial.print("Sensor Hujan ");
  Serial.println(dt[5]);
  Serial.println();

}

