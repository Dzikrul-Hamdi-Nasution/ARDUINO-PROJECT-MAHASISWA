#include <SPI.h>       
#include <DMD.h>       
#include <TimerOne.h>  
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

//Isi dengan jumlah panel DMD yang di susun dalam kolom dan baris
#define DISPLAY_COLUMN_COUNT  2
#define DISPLAY_ROW_COUNT     1

#define PIXELS_PER_COLUMN    32
#define PIXELS_PER_ROW        16


DMD dmd(DISPLAY_COLUMN_COUNT, DISPLAY_ROW_COUNT);
char Text[] = "123";
/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void ScanDMD()
{
  dmd.scanDisplayBySPI();
}

void setup(void)
{
   //inisialisasi Timer1 untuk menginterupsi pengeksekusian prosedur pindai DMD secara periodik
   Timer1.initialize( 1000 );           //perioda eksekusi pindai DMD selama 1 ms. Nilai yang lebih besar dapat menimbulkan efek flicker.
   Timer1.attachInterrupt( ScanDMD );   //terapkan prosedur interupsi pindai DMD
   dmd.clearScreen( true );   //normalnya true (semua piksel dalam keadaan mati), false (semua piksel dalam keadaan hidup)
}

void loop(void)
{  
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16);
  
   dmd.drawString( 0,  0, "oke", 3, GRAPHICS_NORMAL);  
  
      
}
 
