#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
const int phSensorPin  = A0;
float Po               = 0;  
float voltage;
float pHValue;
int adcPH;
int YsensorPin = A14;
int sensorvalue = 0;

#define analogInPin  A1 

int sensorValue;
float outputValueTDS; 
void setup()
{ 
  pinMode (phSensorPin, INPUT); 
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("volt:");
  lcd.setCursor(0, 1);
  lcd.print("Ph  :");
}

void loop()
{
   sensorValue = analogRead(analogInPin);
  outputValueTDS = (0.3417*sensorValue)+281.08;
  Serial.print("TDS(ppm)= ");
  Serial.println(outputValueTDS);
 
   sensorvalue =analogRead(A14);
  Serial.print("kelembaban : ");
   Serial.println(sensorvalue);

  
   int nilaiPengukuranPh = analogRead(phSensorPin);
   voltage = adcPH *5.0/1024;
  pHValue=(-0.04128*nilaiPengukuranPh)+7.667;
  Serial.print("Nilai PH cairan: ");
   Serial.println(pHValue, 3);
   lcd.setCursor(8, 1);
   lcd.print(Po);
   Serial.println(" ");
   delay(1 000);
}
