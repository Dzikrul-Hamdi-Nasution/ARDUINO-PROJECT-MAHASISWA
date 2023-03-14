#include <virtuabotixRTC.h>   
virtuabotixRTC myRTC(2, 3, 4); // CLK, DAT, RST | RTC Connection
String dayOfTheWeek = "   ";
int x =0;
int hr1,hr12;

#include<dht.h>
dht DHT;
int out = 5; // Connect DHT11 OUT Pin to Pin 5 of Arduino
#include <Wire.h>

#include <SPI.h>        
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup()
{ 
   Timer1.initialize( 5000 );
   Timer1.attachInterrupt( ScanDMD ); 
   dmd.clearScreen( true ); 
   Serial.begin(9600);
   Wire.begin();
}

void loop()
{ 
  int value = DHT.read11(out);  
  int temp = DHT.temperature;
  int hum = DHT.humidity;
  Serial.println(temp);
  Serial.println(hum);
   
  myRTC.updateTime();  
  String Date = String(myRTC.year) + "/" + String(myRTC.month) + "/" + String(myRTC.dayofmonth);
  char d[10];
  String str1;
  str1=String(Date);
  str1.toCharArray(d,10);
  char t [3];
  String str2;
  str2=String(temp);
  str2.toCharArray(t,3);
  char h [3];
  String str3;
  str3=String(hum);
  str3.toCharArray(h,3);
  hr1=myRTC.hours;               
  if(hr1>=13)                      
  hr12=hr1-12;                    
  else                            
  hr12=hr1;
  String Time = String(hr12) + ":" + String (myRTC.minutes);
  char b[8];
  String str;
  str=String(Time);
  str.toCharArray(b,8);
  int x = myRTC.dayofweek;                                      
 
      switch (x) 
      {
      case 1:
             dayOfTheWeek = "SUN";
        break;
      case 2:
             dayOfTheWeek = "MON";
        break;
      case 3:
             dayOfTheWeek = "TUE";
        break;
      case 4:
             dayOfTheWeek = "WED";
        break;
      case 5:
             dayOfTheWeek = "THU";
        break;
      case 6:
             dayOfTheWeek = "FRI";
        break;
      case 7:
             dayOfTheWeek = "SAT";
        break;
      default:
        Serial.println(" ");       
       }

  char dy[4];
  String str5;
  str5=String(dayOfTheWeek);
  str5.toCharArray(dy,4);

   //displaying Time
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16);
   dmd.drawMarquee(b,8,(32*DISPLAYS_ACROSS)-1,1);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret)
   {
     if ((timer+30) < millis()) 
     {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }



   //displaying Day
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16);
   dmd.drawMarquee(dy,4,(32*DISPLAYS_ACROSS)-1,1);
   long start1=millis();
   long timer1=start1;
   boolean ret1=false;
   while(!ret1)
   {
     if ((timer1+30) < millis()) 
     {
       ret1=dmd.stepMarquee(-1,0);
       timer1=millis();
     }
   } 

   //displaying Date
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16);
   dmd.drawMarquee(d,10,(32*DISPLAYS_ACROSS)-1,1);
   long start2=millis();
   long timer2=start2;
   boolean ret2=false;
   while(!ret2)
   {
     if ((timer2+30) < millis()) 
     {
       ret2=dmd.stepMarquee(-1,0);
       timer2=millis();
     }
   }

     // display temp and humidity
     dmd.clearScreen( true );
     dmd.selectFont(System5x7);
     for (byte x=0;x<DISPLAYS_ACROSS;x++) {
     for (byte y=0;y<DISPLAYS_DOWN;y++)   {
     dmd.drawString(  0+(32*x),  0+(16*y), "T:", 2, GRAPHICS_NORMAL );
     dmd.drawString(  0+(32*x),  9+(16*y), "H:", 2, GRAPHICS_NORMAL );
     }
     }
    
     dmd.selectFont(System5x7);
     for (byte x=0;x<DISPLAYS_ACROSS;x++) {
     for (byte y=0;y<DISPLAYS_DOWN;y++)   {
     dmd.drawString(  11+(32*x),  0+(16*y), t, 3, GRAPHICS_NORMAL );
     dmd.drawString(  11+(32*x),  9+(16*y), h, 3, GRAPHICS_NORMAL );
     }
     }

     dmd.drawCircle( 24,  1,  1, GRAPHICS_NORMAL );
     
     dmd.selectFont(System5x7);
     for (byte x=0;x<DISPLAYS_ACROSS;x++) {
     for (byte y=0;y<DISPLAYS_DOWN;y++)   {
     dmd.drawString(  27+(32*x),  0+(16*y), "C", 2, GRAPHICS_NORMAL );
     dmd.drawString(  27+(32*x),  9+(16*y), "%", 2, GRAPHICS_NORMAL );
     }
     }

     delay(5000);

 }
