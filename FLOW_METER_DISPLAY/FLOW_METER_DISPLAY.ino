#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "ComicSansMS18.h"




//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
float fx, rumus; float hasil_baca_1, hasil_baca, kalibrasi_ulang, kalibrasi_ulang_2;

void ScanDMD()
{
  dmd.scanDisplayBySPI();
}

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;

void setup(void)
{

  //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
  Timer1.initialize( 3000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
  Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

  //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  Serial.begin(9600);
}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
  --------------------------------------------------------------------------------------*/
char pesanDisplay[10];

void loop(void) {
  sensorValue = analogRead(analogInPin);
  //hasil_baca_1 = 0.349455 * sensorValue;
  //hasil_baca = hasil_baca_1 - 5.21387;
  // turn the ledPin on

  for (int x = 0; x < 30; x++) {
    dmd.drawString( 0, -1, pesanDisplay, 3, GRAPHICS_NORMAL );
    sensorValue = analogRead(analogInPin);
    hasil_baca = hasil_baca + sensorValue;
    delay(50);
    dmd.drawString( 0, -1, pesanDisplay, 3, GRAPHICS_NORMAL );
  }

  //kalibrasi_ulang = 0.40042921 * sensorValue;
  //kalibrasi_ulang_2 = kalibrasi_ulang - 68.9770152;

  Serial.println(sensorValue);
  hasil_baca_1 = hasil_baca / 30;
  hasil_baca = 0;
  Serial.println(hasil_baca_1);

  kalibrasi_ulang = map(hasil_baca_1, 58, 1015, 0, 378);

  if (hasil_baca_1 < 55) {
    kalibrasi_ulang = 0; 
 }


  //Serial.println(rumus);
  dtostrf(kalibrasi_ulang, 2, 1, pesanDisplay);
  dmd.selectFont(ComicSansMS18);
  Serial.print("Display : ");
  Serial.println(kalibrasi_ulang);

  dmd.drawString( 0, -1, pesanDisplay, 3, GRAPHICS_NORMAL );

  //delay(7000);
  dmd.clearScreen( true );

}

float mapi(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
