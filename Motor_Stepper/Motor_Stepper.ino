
const int steping = 2;
const int arah = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(steping, OUTPUT);
  pinMode(arah, OUTPUT);
  digitalWrite(arah, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:


  digitalWrite(steping, HIGH);
  delayMicroseconds(1000);
  digitalWrite(steping, LOW);
  delayMicroseconds(1000);


}
