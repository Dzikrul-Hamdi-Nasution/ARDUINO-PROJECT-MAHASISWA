#include <SoftwareSerial.h>
SoftwareSerial SIM800L(5, 4); // RX | TX
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SIM800L.begin(9600);
  Serial.print("Mengirim SMS....");
  SIM800L.write("AT+CMGF=1\r\n");
  delay(1000);
  SIM800L.write("AT+CMGS=\"087790805593\"\r\n");
  delay(1000);
  SIM800L.write("Mahasiswa BANGKIT telah hadir " );
  delay(1000);
  SIM800L.write((char)26);
  delay(1000);
  Serial.print(" SMS Terkirim ");
}

void loop() {
  // put your main code here, to run repeatedly:

}
