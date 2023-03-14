#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "ComicSansMS18.h"




//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
float fx, rumus; float hasil_baca_1, hasil_baca, kalibrasi;

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
  //hasil_baca_1 = 0.017764 * sensorValue;
  //hasil_baca = hasil_baca_1 + 0.33137;
  // turn the ledPin on


  for (int x = 0; x < 10; x++) {
    dmd.drawString( 0, -1, pesanDisplay, 4, GRAPHICS_NORMAL );
    sensorValue = analogRead(analogInPin);
    hasil_baca = hasil_baca + sensorValue;
    delay(100);
    dmd.drawString( 0, -1, pesanDisplay, 4, GRAPHICS_NORMAL );
    
  }

  Serial.println(sensorValue);
  hasil_baca_1 = hasil_baca / 10;
  hasil_baca = 0;
  Serial.println(hasil_baca_1);

  //kalibrasi = map(hasil_baca, 80 , 768, 1.84, 14);
  float a = mapi(hasil_baca_1, 0, 770, 0, 14.0);
  a = a + 0.3;
  //Serial.println("Mapped Value:" + kalibrasi);

  //Serial.println(rumus);
  dtostrf(a, 3, 1, pesanDisplay);
  dmd.selectFont(ComicSansMS18);
  Serial.print("sensor : ");
  Serial.println(a);


  dmd.drawString( 0, -1, pesanDisplay, 4, GRAPHICS_NORMAL );

  //delay(1000);
  dmd.clearScreen( true );

}

float mapi(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
