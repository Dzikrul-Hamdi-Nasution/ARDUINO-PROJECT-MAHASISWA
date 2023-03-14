#define BLYNK_TEMPLATE_ID "TMPLzcOO5mVm"
#define BLYNK_DEVICE_NAME "Monitor Daya"
#define BLYNK_AUTH_TOKEN "YTf0hYwydKCVnsiQhynsfXqLFcBtVuNe"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>        // Memanggil library Wire  
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>                                      // Memanggil library LCD i2C
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <PZEM004Tv30.h>

PZEM004Tv30 pzem(12, 14); // Software Serial pin GPIO  12 (RX) & 14 (TX)
float arus, daya, Power;
int tegangan;
char auth[] = "YTf0hYwydKCVnsiQhynsfXqLFcBtVuNe";
char ssid[] = "Server Project";
char pass[] = "Salamproject2022";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                                  // Deklarasi baudrate komunikasi serial
  lcd.begin();                                                         // Memulai komunikasi dengan LCD
  lcd.backlight();
  lcd.setCursor( 0 , 0);
  lcd.print("Connecting...");
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  baca_daya();
  tampilan();
  Blynk.run();
  Blynk.virtualWrite(V1, tegangan);
  Blynk.virtualWrite(V5, arus);
  Blynk.virtualWrite(V6, Power , " Watt");
  Blynk.virtualWrite(V7, daya , " Kwh");

}


void tampilan() {
  lcd.clear();
  lcd.setCursor( 0 , 0);
  lcd.print("Power ");
  lcd.setCursor( 6 , 0);
  lcd.print(Power);
  lcd.setCursor( 11 , 0);
  lcd.print("W");

  lcd.setCursor( 0 , 1);
  lcd.print("Energy ");
  lcd.setCursor( 7 , 1);
  lcd.print(daya);
  lcd.setCursor( 12 , 1);
  lcd.print("KWh");

  delay(2000);

  lcd.clear();
  lcd.setCursor( 0 , 0);
  lcd.print("Voltase ");
  lcd.setCursor( 8 , 0);
  lcd.print(tegangan);
  lcd.setCursor( 12 , 0);
  lcd.print("V");

  lcd.setCursor( 0 , 1);
  lcd.print("Arus ");
  lcd.setCursor( 5 , 1);
  lcd.print(arus);
  lcd.setCursor( 10 , 1);
  lcd.print("A");

  delay(2000);
}


void baca_daya() {
  float voltage = pzem.voltage();
  if (voltage != NAN) {
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("V");
  } else {
    Serial.println("Error reading voltage");
  }
  tegangan = voltage;

  float current = pzem.current();
  if (current != NAN) {
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println("A");
  } else {
    Serial.println("Error reading current");
  }
  arus = current;

  float power = pzem.power();
  if (current != NAN) {
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println("W");
  } else {
    Serial.println("Error reading power");
  }
  Power = power;

  float energy = pzem.energy();
  if (current != NAN) {
    Serial.print("Energy: ");
    Serial.print(energy, 3);
    Serial.println("kWh");
  } else {
    Serial.println("Error reading energy");
  }
  daya = energy;

  float frequency = pzem.frequency();
  if (current != NAN) {
    Serial.print("Frequency: ");
    Serial.print(frequency, 1);
    Serial.println("Hz");
  } else {
    Serial.println("Error reading frequency");
  }

  float pf = pzem.pf();
  if (current != NAN) {
    Serial.print("PF: ");
    Serial.println(pf);
  } else {
    Serial.println("Error reading power factor");
  }

  Serial.println();
  delay(1000);
}
