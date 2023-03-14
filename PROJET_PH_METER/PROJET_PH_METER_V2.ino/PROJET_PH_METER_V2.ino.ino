#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include "SystemFont5x7.h"
#include "My32x15Font.h"



//byte DataPins[2] = {33, 35}; //pin jalur out
SPIDMD dmd(2, 2, 9, 6, 7, 8);
DMD_TextBox box1(dmd, 0, 0, 78, 32);
DMD_TextBox box(dmd, 0, 16, 78, 32);

String pesanDisplay;

float x;
int y = 110;
float a;
char b[4];

void setup() {
  Serial.begin(9600);
  dmd.setBrightness(100);
  dmd.begin();
  //pesanDisplay = "12,34";
  dmd.selectFont(My32x15Font);

}

void loop()
{


  a = 0;
  a = analogRead(A0);
  a = (5.0 * a * 100.0) / 1024.0;
  //Serial.println(a);
  //dtostrf(x, 2, 0, pesanDisplay);

  pesanDisplay = String(x);

  dmd.drawString(0, 0, pesanDisplay);
  delay(1000);
 

  x = x + 0.1;
  dmd.clearScreen( true );

}
