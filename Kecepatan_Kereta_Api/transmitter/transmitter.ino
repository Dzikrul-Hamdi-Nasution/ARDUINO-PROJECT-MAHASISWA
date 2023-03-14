#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN

const byte address[6] = "00001";
const int sensor_jarak_A = A0;
const int sensor_jarak_B = A1;
int sensorValue_A, sensorValue_B;
int data_sensor_A, data_sensor_B;
int rata_rata_A, rata_rata_B;
float counting_speed;
int led = 7;
String command;

void setup() {
  Serial.begin(9600);
  radio.begin();
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  const char text[] = "Speed Check";
  radio.write(&text, sizeof(text));
}

void loop() {

  //cek_jarak();
  cek_speed();

  //tester();
}

void cek_speed() {
  for (int i = 0; i <= 25; i++) {
    sensorValue_A = analogRead(sensor_jarak_A);
    data_sensor_A = data_sensor_A + sensorValue_A;
  }
  rata_rata_A = data_sensor_A / 25;
  data_sensor_A = 0;
  Serial.print("Sensor A ");
  Serial.println(rata_rata_A);
  digitalWrite(led, HIGH);
  if (rata_rata_A > 110) {
    digitalWrite(led, LOW);
    while (rata_rata_B < 110) {
      for (int i = 0; i <= 25; i++) {
        sensorValue_B = analogRead(sensor_jarak_B);
        data_sensor_B = data_sensor_B + sensorValue_B;
        counting_speed++;
      }
      rata_rata_B = data_sensor_B / 25;
      data_sensor_B = 0;
      Serial.print("counting ");
      Serial.println(counting_speed);
    }
    Serial.print("counting ");
    Serial.println(counting_speed);
    float kecepatan = 1900 / counting_speed;
    float konversi = kecepatan * 3.6;

    String str = String(kecepatan, 2);
    int str_len = str.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
    radio.write(&char_array, sizeof(char_array));
    Serial.print("Kecepatan ");
    Serial.print(kecepatan, 2);
    Serial.println(" m/detik");
    Serial.print("Kecepatan ");
    Serial.print(konversi, 2);
    Serial.println(" Km/Jam");
    counting_speed = 0;
    rata_rata_B = 0;
    delay(5000);
  }
}


void tester() {

  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    Serial.print("Kecepatan ");
    Serial.println(command);
  }

  String str = command;
  int str_len = str.length() + 1;
  char char_array[str_len];
  str.toCharArray(char_array, str_len);
  radio.write(&char_array, sizeof(char_array));
  command = "";

}

void cek_jarak() {

  for (int i = 0; i <= 25; i++) {
    sensorValue_A = analogRead(sensor_jarak_A);
    data_sensor_A = data_sensor_A + sensorValue_A;
  }
  rata_rata_A = data_sensor_A / 25;
  data_sensor_A = 0;
  Serial.print("Sensor A ");
  Serial.println(rata_rata_A);

  for (int i = 0; i <= 25; i++) {
    sensorValue_B = analogRead(sensor_jarak_B);
    data_sensor_B = data_sensor_B + sensorValue_B;
    counting_speed++;
  }
  rata_rata_B = data_sensor_B / 25;
  data_sensor_B = 0;
  Serial.print("Sensor B ");
  Serial.println(rata_rata_B);
  Serial.println();
  Serial.println();
  delay(500);
}
