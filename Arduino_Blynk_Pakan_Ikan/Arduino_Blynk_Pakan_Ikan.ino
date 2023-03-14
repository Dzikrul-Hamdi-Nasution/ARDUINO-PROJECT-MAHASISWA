

#include <Wire.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include "HX711.h"

#include <DS3231.h>

RTClib myRTC;



#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);            // Pass the oneWire reference to Dallas Temperature.

#define DOUT  4
#define CLK  3
HX711 scale(DOUT, CLK);
float calibration_factor = 221;
float GRAM;
float suhu;

int pHSense = A0;
int samples = 10;
float adc_resolution = 1024.0, ph_act;

int jam, menit, takaran, kunci = 0;;
int jam_pagi, jam_sore, menit_pagi, menit_sore;

float ph (float voltage) {
  return 7 + ((2.5 - voltage) / 0.18);
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  sensors.begin();
  
  scale.set_scale();
  scale.tare();
  Serial.println("Pakan Ikan Blynk Arduino ");

  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  cek_ph();
  cek_berat();
  cek_suhu();
  waktu();



}




void cek_berat() {
  scale.set_scale(calibration_factor);
  float data_berat = abs(scale.get_units());
  GRAM = (data_berat - 1760), 4;
  GRAM = GRAM * (-1);
  Serial.print("Berat : ");
  Serial.println(GRAM);
}

void cek_suhu() {
  sensors.requestTemperatures();                // Send the command to get temperatures
  suhu = sensors.getTempCByIndex(0);
  Serial.print("Suhu : ");
  Serial.println(suhu);
}


void waktu() {
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
