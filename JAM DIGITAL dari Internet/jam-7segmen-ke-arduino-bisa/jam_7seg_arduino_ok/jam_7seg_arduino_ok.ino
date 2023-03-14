/*
Author: Danny van den Brande, arduinosensors.nl. BlueCore Tech.
This code is written for the AT24C32/DS1307 RTC Module and
4 digit Seven Segment displays.
Be sure to check if you have a common anode or cathode display.(change @ line 26)

MODIFIED BY : WWW.ROKHMAD.COM   ; ADA BEBERAPA MODIFIKASI, MULAI DARI LED KEDIP DAN PENAMBAHAN TOMBOL UNTUK SETTING JAMNYA !!
 */
#include "Wire.h"
#include "SevSeg.h" //https://github.com/sparkfun/SevSeg/tree/master/src
#include <DS3231.h>
#define DS1307_ADDRESS 0x68
DS3231  rtc(SDA, SCL);

///////////////////////////////// Mendifinisikan Pin Tombol ////////////////////////////////////////

#define tombol_bOK A2             // Tombol OK sesuaikan dengan PIN di arduino anda mana  klo ini terhubung dengan PIN analog2
#define Jam_bDN A3           //tombol setting   sesuaikan dengan PIN di arduino anda mana  klo ini terhubung dengan PIN analog 3

int langkah;

//Create an instance
SevSeg display7seg;

int valor = 0;
byte zero = 0x00;
unsigned long timer;
void setup()
{
  rtc.begin();
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  Wire.begin();
  //Comment this line after you have set the date @ void TimeSelection() below
  //   TimeSelection(); Uncomment this line when your setting the time. Set time @ (line 66)
  /////tombol


  pinMode(tombol_bOK, INPUT_PULLUP);                                 // Mode Pin Sebagai Input dengan Pull Up Internal
  pinMode(Jam_bDN, INPUT_PULLUP);                                    // Mode Pin Sebagai Input dengan Pull Up Internal

  //attachInterrupt(0, Setting, FALLING);
  ///end tombol codingan




  //Change to COMMON_ANODE OR  COMMON_CATHODE  if you have a Common display.
  int displayType = COMMON_ANODE;
  pinMode(9, OUTPUT);
  int digit1 = 10;
  int digit2 = 11;
  int digit3 = 12;
  int digit4 = 13;

  int segA = 2;
  int segB = 3;
  int segC = 4;
  int segD = 5;
  int segE = 6;
  int segF = 7;
  int segG = 8;
  int segDP = A0;

  int numberOfDigits = 4;

  //Initialize display
  display7seg.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);

  //Set brightness
  display7seg.SetBrightness(35);
  timer = millis();
}

void loop()
{
  char tempString[10]; //Used for sprintf
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);
  int seconds = ConvertToDecimal(Wire.read());
  int minutes = ConvertToDecimal(Wire.read());
  int hours = ConvertToDecimal(Wire.read() & 0b111111);

  //////kodimgku set menit

  if (digitalRead(Jam_bDN) == LOW) {                               // Tombol Setting menit
    delay(10); minutes++;
    rtc.setTime(hours, minutes, 0);
    if (minutes >= 60) {
      minutes = 0; // Batas Nilai menit Lebih dari 59 Kembali ke 0
      rtc.setTime(hours, minutes, 0);
    }
  }
  while (digitalRead(Jam_bDN) == LOW) {}                          // Kunci Tombol Settingmenit Sampai Lepas Tombol


  //////kodimgku set jam

  if (digitalRead(tombol_bOK) == LOW) {                               // Tombol Setting jam
    delay(10);
    hours++;
    rtc.setTime(hours, minutes, 0);
    if (hours >= 24) {

      hours = 0; // Batas Nilai jam Lebih dari 23 Kembali ke 0
      rtc.setTime(hours, minutes, 0);
    }
  }
  while (digitalRead(tombol_bOK) == LOW) {}                          // Kunci Tombol Setting jam Sampai Lepas Tombol

  //////

  //rtc.setTime(hours, minutes, 0);
  sprintf(tempString, "%02d%02d", hours, minutes);

  display7seg.DisplayString(tempString, 3);
  if (seconds == 1 || seconds == 3 || seconds == 5 || seconds == 7 || seconds == 9 || seconds == 11 || seconds == 13 || seconds == 15 || seconds == 17 || seconds == 19 || seconds == 21 ||
      seconds == 23 || seconds == 25 || seconds == 27 || seconds == 29 || seconds == 31 || seconds == 33 || seconds == 35 || seconds == 37 || seconds == 39
      || seconds == 41 || seconds == 43 || seconds == 45 || seconds == 47 || seconds == 49 ||
      seconds == 51 || seconds == 53 || seconds == 55 || seconds == 57 || seconds == 59 ) {
    digitalWrite(9, LOW);
  } else  {
    digitalWrite(9, HIGH);

  }


}

void TimeSelection()   //Select date and time here below!!(line 69,70,71)
//after setting time also comment time TimeSelection() @ void setup
{
  byte seconds = 10; //Valores de 0 a 59
  byte minutes = 38; //Valores de 0 a 59
  byte hours = 3; //Valores de 0 a 23
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); //Stop no CI para que o mesmo possa receber os dados

  //As linhas abaixo escrevem no CI os valores de
  //data e hora que foram colocados nas variaveis acima
  Wire.write(ConvertToPCD(seconds));
  Wire.write(ConvertToPCD(minutes));
  Wire.write(ConvertToPCD(hours));
  Wire.write(zero);
  Wire.endTransmission();
}

byte ConvertToPCD(byte val)
{
  //Convert Decimal to binary
  return ( (val / 10 * 16) + (val % 10) );
}

byte ConvertToDecimal(byte val)
{
  //Convert binary to decimal
  return ( (val / 16 * 10) + (val % 16) );
}
