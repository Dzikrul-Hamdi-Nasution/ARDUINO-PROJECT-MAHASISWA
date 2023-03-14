#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "Arial_Black_16_ISO_8859_1.h"
#include "Arial_black_16.h"
#include "BigNumber.h"
#include "My32x15Font.h"
#include "FIXEDNUMS7x15.h"



//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
float fx, rumus;
int kunci_1, kunci_2, kunci_3, kunci_4, kunci_5, kunci_6, kunci_7, kunci_0, kunci_puluhan;
int kunci_8, kunci_9, kunci_10, kunci_11, kunci_12, kunci_13, kunci_14, kunci_15;


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
  //dmd.clearScreen( true );
  sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);
  fx = 0.019812 * sensorValue;
  rumus = fx + 0.1458302 - 0.37 ;//0.2

  if (rumus < 0.01) {
    rumus = 0;
  }

  //Serial.println(rumus);
  dtostrf(12.6, 3, 1, pesanDisplay);
  dmd.selectFont(Arial_Black_16_ISO_8859_1);

  if (rumus > 15.06 && rumus < 15.15) {
    Serial.println("bisa");
    if (kunci_15 == 0) {
      dmd.clearScreen( true );
    }
    kunci_15 = 2;
  }
  if (rumus < 15.06) {
    kunci_15 = 0;
  }
  if (rumus > 15.15) {
    kunci_15 = 0;
  }
  if (rumus > 14.07 && rumus < 14.20) {
    Serial.println("bisa");
    if (kunci_14 == 0) {
      dmd.clearScreen( true );
    }
    kunci_14 = 2;
  }
  if (rumus < 14.07) {
    kunci_14 = 0;
  }
  if (rumus > 14.20) {
    kunci_14 = 0;
  }

  if (rumus > 13.07 && rumus < 13.20) {
    Serial.println("bisa");
    if (kunci_13 == 0) {
      dmd.clearScreen( true );
    }
    kunci_13 = 2;
  }
  if (rumus < 13.07) {
    kunci_13 = 0;
  }
  if (rumus > 13.20) {
    kunci_13 = 0;
  }

  if (rumus > 12.07 && rumus < 12.20) {
    Serial.println("bisa");
    if (kunci_12 == 0) {
      dmd.clearScreen( true );
    }
    kunci_12 = 2;
  }
  if (rumus < 12.07) {
    kunci_12 = 0;
  }
  if (rumus > 12.20) {
    kunci_12 = 0;
  }
  if (rumus > 11.07 && rumus < 11.20) {
    Serial.println("bisa");
    if (kunci_11 == 0) {
      dmd.clearScreen( true );
    }
    kunci_11 = 2;
  }
  if (rumus < 11.07) {
    kunci_11 = 0;
  }
  if (rumus > 11.20) {
    kunci_11 = 0;
  }
  if (rumus > 10.07 && rumus < 10.20) {
    Serial.println("bisa");
    if (kunci_10 == 0) {
      dmd.clearScreen( true );
    }
    kunci_10 = 2;
  }
  if (rumus < 10.07) {
    kunci_10 = 0;
    if (kunci_puluhan == 0) {
      dmd.clearScreen( true );
    }
    kunci_puluhan = 1;
  }
  if (rumus > 10.20) {
    kunci_10 = 0;
    kunci_puluhan = 0;
  }
  if (rumus > 9.07 && rumus < 9.20) {
    Serial.println("bisa");
    if (kunci_9 == 0) {
      dmd.clearScreen( true );
    }
    kunci_9 = 2;
  }
  if (rumus < 9.07) {
    kunci_9 = 0;
  }
  if (rumus > 9.20) {
    kunci_9 = 0;
  }
  if (rumus > 8.07 && rumus < 8.20) {
    Serial.println("bisa");
    if (kunci_8 == 0) {
      dmd.clearScreen( true );
    }
    kunci_8 = 2;
  }
  if (rumus < 8.07) {
    kunci_8 = 0;
  }
  if (rumus > 8.20) {
    kunci_8 = 0;
  }
  if (rumus > 7.07 && rumus < 7.20) {
    Serial.println("bisa");
    if (kunci_7 == 0) {
      dmd.clearScreen( true );
    }
    kunci_7 = 2;
  }
  if (rumus < 7.07) {
    kunci_7 = 0;
  }
  if (rumus > 7.20) {
    kunci_7 = 0;
  }
  if (rumus > 6.07 && rumus < 6.20) {
    Serial.println("bisa");
    if (kunci_6 == 0) {
      dmd.clearScreen( true );
    }
    kunci_6 = 2;
  }
  if (rumus < 6.07) {
    kunci_6 = 0;
  }
  if (rumus > 6.20) {
    kunci_6 = 0;
  }
  if (rumus > 5.07 && rumus < 5.20) {
    Serial.println("bisa");
    if (kunci_5 == 0) {
      dmd.clearScreen( true );
    }
    kunci_5 = 2;
  }
  if (rumus < 5.07) {
    kunci_5 = 0;
  }
  if (rumus > 5.20) {
    kunci_5 = 0;
  }
  if (rumus > 4.07 && rumus < 4.20) {
    Serial.println("bisa");
    if (kunci_4 == 0) {
      dmd.clearScreen( true );
    }
    kunci_4 = 2;
  }
  if (rumus < 4.07) {
    kunci_4 = 0;
  }
  if (rumus > 4.20) {
    kunci_4 = 0;
  }
  if (rumus > 3.07 && rumus < 3.20) {
    Serial.println("bisa");
    if (kunci_3 == 0) {
      dmd.clearScreen( true );
    }
    kunci_3 = 2;
  }
  if (rumus < 3.07) {
    kunci_3 = 0;
  }
  if (rumus > 3.20) {
    kunci_3 = 0;
  }
  if (rumus > 2.07 && rumus < 2.20) {
    Serial.println("bisa");
    if (kunci_2 == 0) {
      dmd.clearScreen( true );
    }
    kunci_2 = 2;
  }
  if (rumus < 2.07) {
    kunci_2 = 0;
  }
  if (rumus > 2.20) {
    kunci_2 = 0;
  }
  if (rumus > 1.07 && rumus < 1.20) {
    Serial.println("bisa");
    if (kunci_1 == 0) {
      dmd.clearScreen( true );
    }
    kunci_1 = 2;
  }
  if (rumus < 1.07) {
    kunci_1 = 0;
  }
  if (rumus > 1.20) {
    kunci_1 = 0;
  }
  if (rumus < 0.20) {
    Serial.println("bisa");
    if (kunci_0 == 0) {
      dmd.clearScreen( true );
    }
    kunci_0 = 2;
  }
  if (rumus < 1.00) {
    kunci_0 = 0;
  }










  dmd.drawString( 2, 0, pesanDisplay, 4, GRAPHICS_NORMAL );


  delay(500);
}
