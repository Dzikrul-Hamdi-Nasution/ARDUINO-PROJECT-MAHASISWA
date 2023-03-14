#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int trig = 3;
int echo = 2;
int buzzer = 4;
long durasi, jarak;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();


void setup() {
  Serial.begin(9600);
  mlx.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(trig, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(buzzer, HIGH);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Alert Covid");
  display.display();
  delay(2000);

}

void loop() {

  float suhu = mlx.readObjectTempC();
  //Serial.println(suhu);
  cek_jarak();
  if (jarak <= 100 ) {
    if (jarak <= 25 ) {
      float suhu = mlx.readObjectTempC() + 3;
      Serial.println(suhu);
      digitalWrite(buzzer, LOW);
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("WARNING");
      display.println(suhu);
      display.display();
    }
    else {
      Serial.println("jarak melebihi batas");
      digitalWrite(buzzer, HIGH);
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("WARNING");
      display.display();
    }
  }
  else {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("SAFE");
    display.display();
  }
}

void cek_jarak() {
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  digitalWrite(trig, HIGH);
  delayMicroseconds(8);
  digitalWrite(trig, LOW);
  delayMicroseconds(8);

  durasi = pulseIn(echo, HIGH);
  jarak = (durasi / 2) / 29.1;
  //Serial.println(jarak);
}
