#include <DHT.h>
#include <DHT_U.h>


#define DHT11_PIN 3
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHT11_PIN, DHTTYPE);
int ledPower = 2;
int measurePin = A0;
int samplingTime = 176;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
float voltDensity = 0;

int data_co2;
int data_so2;
int data_suhu;




void setup() {
  Serial.begin(115200);
  pinMode(ledPower, OUTPUT);
  dht.begin();
}

void loop() {
  debu();
  co2();
  so2();
  suhu();

  kirim();
  delay(5000);
}




int kirim() {
  Serial.print("*");
  Serial.print(dustDensity);
  Serial.print(",");
  Serial.print(data_co2);
  Serial.print(",");
  Serial.print(data_so2);
  Serial.print(",");
  Serial.print(data_suhu);
  Serial.println("#");


}


int debu() {
  digitalWrite(ledPower, LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value
  delayMicroseconds(40);
  digitalWrite(ledPower, HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  calcVoltage = ( ( voMeasured * 5 ) / 1024);
  //voltDensity = calcVoltage - 0.6;
  voltDensity = calcVoltage * 0.166;
  //dustDensity = voltDensity * 0.17;
  dustDensity = voltDensity + 2.129;

  //Serial.print(" - Dust Density: ");
  //Serial.print(dustDensity);
  //Serial.println(" Kg/m3");
}

int so2() {
  data_so2 = analogRead(A1);
}

int co2() {
  data_co2 = analogRead(A2);
}

int suhu() {
  //data_suhu = analogRead(A3);
  //int chk = DHT.read11(DHT11_PIN);
  float t = dht.readTemperature();
  float humidity_1 = dht.readHumidity();
  float fahrenheit_1 = dht.readTemperature(true);

  //mengecek pembacaan apakah terjadi kegagalan atau tidak
  if (isnan(humidity_1) || isnan(t) || isnan(fahrenheit_1)) {
    Serial.println("Pembacaan data dari module sensor gagal!");
    return;
  }
  float htoc = dht.computeHeatIndex(t, humidity_1, false);
  data_suhu = t;
}


