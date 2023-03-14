

int blade_1[] = {A0, A1, A2, A3, A4};
int selenoid_1[] = {A5, A6, A7, A8, A9};
int blade_var[] = {0, 0, 0, 0, 0};
int selenoid_var[] = {0, 0, 0, 0, 0};
int kondisi_blade[] = {0, 0, 0, 0, 0};
int kondisi_selenoid[] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop() {

  for (int x = 0; x < 5; x++) {
    blade_var[x] = analogRead(blade_1[x]);
    selenoid_var[x] = analogRead(selenoid_1[x]);
    
  }

  for (int y = 0; y < 5; y++) {
    if (blade_var[y] > 512) {
      kondisi_blade[y] = 1;
    } else {
      kondisi_blade[y] = 0;
    }

    if (selenoid_var[y] > 512) {
      kondisi_selenoid[y] = 1;
    } else {
      kondisi_selenoid[y] = 0;
    }

  }

  Serial1.print("*");
  Serial1.print(kondisi_blade[0]);
  Serial1.print(",");
  Serial1.print(kondisi_blade[1]);
  Serial1.print(",");
  Serial1.print(kondisi_blade[2]);
  Serial1.print(",");
  Serial1.print(kondisi_blade[3]);
  Serial1.print(",");
  Serial1.print(kondisi_blade[4]);
  Serial1.print(",");
  Serial1.print(kondisi_selenoid[5]);
  Serial1.print(",");
  Serial1.print(kondisi_selenoid[6]);
  Serial1.print(",");
  Serial1.print(kondisi_selenoid[7]);
  Serial1.print(",");
  Serial1.print(kondisi_selenoid[8]);
  Serial1.print(",");
  Serial1.print(kondisi_selenoid[9]);
  Serial1.println("#");


  Serial.print("*");
  Serial.print(kondisi_blade[0]);
  Serial.print(",");
  Serial.print(kondisi_blade[1]);
  Serial.print(",");
  Serial.print(kondisi_blade[2]);
  Serial.print(",");
  Serial.print(kondisi_blade[3]);
  Serial.print(",");
  Serial.print(kondisi_blade[4]);
  Serial.print(",");
  Serial.print(kondisi_selenoid[5]);
  Serial.print(",");
  Serial.print(kondisi_selenoid[6]);
  Serial.print(",");
  Serial.print(kondisi_selenoid[7]);
  Serial.print(",");
  Serial.print(kondisi_selenoid[8]);
  Serial.print(",");
  Serial.print(kondisi_selenoid[9]);
  Serial.println("#");
  Serial.println();

  delay(10000);
}
