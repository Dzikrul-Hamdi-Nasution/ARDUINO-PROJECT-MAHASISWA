#define BLYNK_TEMPLATE_ID "TMPLo3iI_V-U"
#define BLYNK_DEVICE_NAME "TACE"
#define BLYNK_AUTH_TOKEN "Vevtqxhk4fypS1_-Izvjf1j2X3vMOGad"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Servo.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "HX711.h"

#include <NTPClient.h>
#include <WiFiUdp.h>
const long utcOffsetInSeconds = 25200;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);


Servo servo;

char auth[] = "Vevtqxhk4fypS1_-Izvjf1j2X3vMOGad";
char ssid[] = "Server Project";
char pass[] = "Salamproject2022";

int jam, menit, takaran, kunci = 0;;
int jam_pagi, jam_sore, menit_pagi, menit_sore;

#define ONE_WIRE_BUS 17
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);            // Pass the oneWire reference to Dallas Temperature.

#define DOUT  0
#define CLK  2
HX711 scale(DOUT, CLK);
float calibration_factor = 120;
float GRAM;
float suhu;

int pHSense = 34;
int samples = 10;
float adc_resolution = 1024.0, ph_act;


float ph (float voltage) {
  return 27 + ((2.5 - voltage) / 0.18);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servo.attach(13);
  servo.write(100);
  Blynk.begin(auth, ssid, pass);

  Serial.println("Pakan Ikan Blynk ");
  Blynk.logEvent("notify", "System Online");
  Wire.begin();
  sensors.begin();
  timeClient.begin();

  scale.set_scale();
  scale.tare();

  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  cek_ph();
  cek_berat();
  cek_suhu();
  waktu();
  otomatis();

  String data_berat, data_suhu;
  data_berat.concat(GRAM);
  data_suhu.concat(suhu);
  Serial.print("Berat : ");
  Serial.println(data_berat);

  Blynk.run();
  Blynk.virtualWrite(V1, ph_act);
  Blynk.virtualWrite(V9, data_berat);
  Blynk.virtualWrite(V10, data_suhu);
  Blynk.virtualWrite(V2, jam);
  Blynk.virtualWrite(V3, menit);



}

void otomatis() {
  if (jam == jam_pagi) {
    if (menit == menit_pagi) {
      if (kunci == 0) {
        Blynk.logEvent("notify", "Telah diberi pakan Pagi");
        Serial.println("Pemberian pakan Pagi Selesai");

        int berat_fix = GRAM - takaran;
        while (GRAM > berat_fix) {
          cek_berat();
          servo.write(0);
          delay(30);
        }

        kunci = 1;
        servo.write(100);
      }
    } else {
      kunci = 0;
    }
  }

  if (jam == jam_sore) {
    if (menit == menit_sore) {
      if (kunci == 0) {
        Blynk.logEvent("notify", "Telah diberi pakan Sore");
        Serial.println("Pemberian pakan Sore Selesai");

        int berat_fix = GRAM - takaran;
        while (GRAM > berat_fix) {
          cek_berat();
          servo.write(0);
          delay(30);
        }

        kunci = 1;
        servo.write(100);
      }
    } else {
      kunci = 0;
    }
  }



}


void cek_berat() {
  scale.set_scale(calibration_factor);
  float data_berat = abs(scale.get_units());
  GRAM = (data_berat), 4;
  //GRAM = GRAM * (-1);
}

void cek_suhu() {
  sensors.requestTemperatures();                // Send the command to get temperatures
  suhu = sensors.getTempCByIndex(0);
  Serial.print("Suhu : ");
  Serial.println(suhu);
}


void waktu() {
  timeClient.update();
  int currentHour = timeClient.getHours();
  jam = currentHour;
  Serial.print("Hour: ");
  Serial.println(currentHour);

  int currentMinute = timeClient.getMinutes();
  menit = currentMinute;
  Serial.print("Minutes: ");
  Serial.println(currentMinute);

  int currentSecond = timeClient.getSeconds();
  Serial.print("Seconds: ");
  Serial.println(currentSecond);


  Serial.println("");
  Serial.println("");
  delay(1000);
}

void cek_ph() {
  int measurings = 0;

  for (int i = 0; i < samples; i++)
  {
    measurings += analogRead(pHSense);
    delay(10);

  }

  float voltage = 5 / adc_resolution * measurings / samples;
  ph_act = ph(voltage);
  Serial.print("pH Val: ");
  Serial.println(ph_act);


}



BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  takaran = pinValue;
  Serial.print("Takaran: ");
  Serial.println(takaran);
}

BLYNK_WRITE(V5)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  jam_pagi = pinValue;
  Serial.print("Jam Pagi: ");
  Serial.println(jam_pagi);
}
BLYNK_WRITE(V6)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  menit_pagi = pinValue;
  Serial.print("Menit Pagi: ");
  Serial.println(menit_pagi);
}

BLYNK_WRITE(V7)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  jam_sore = pinValue;
  Serial.print("Jam Sore: ");
  Serial.println(jam_sore);
}
BLYNK_WRITE(V8)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  menit_sore = pinValue;
  Serial.print("Menit Sore: ");
  Serial.println(menit_sore);
}
