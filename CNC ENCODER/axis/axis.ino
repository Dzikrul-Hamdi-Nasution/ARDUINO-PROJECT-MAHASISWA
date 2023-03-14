#define ENCA 21
#define ENCB 20
#define PWM 8
#define IN2 6
#define IN1 7

int pos = 0;
long prevT = 0;
float eprev = 0;
float eintegral = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
  Serial.println("target pos");
}
String data;
void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c != '/') {
      data += c;
    }
    else {
      data = "";
    }
    //lcd.clear();
  }

  // set target position
  int target = 20000;
  //target = 250*sin(prevT/1e6);

  // PID constants
  float kp = 1;
  float kd = 0.025;
  float ki = 0.0;

  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;

  // error
  int e = pos - target;

  // derivative
  float dedt = (e - eprev) / (deltaT);

  // integral
  eintegral = eintegral + e * deltaT;

  // control signal
  float u = kp * e + kd * dedt + ki * eintegral;

  // motor power
  float pwr = fabs(u);
  if ( pwr > 255 ) {
    pwr = 255;
  }

  // motor direction
  int dir = 1;
  if (u < 0) {
    dir = -1;
  }

  // signal the motor
  setMotor(dir, pwr, PWM, IN1, IN2);

  // store previous error
  eprev = e;

  Serial.print(target);
  Serial.print(" ");
  Serial.print(pos);
  Serial.println();
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2) {
  analogWrite(pwm, pwmVal);
  if (dir == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if (dir == -1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    pos++;
  }
  else {
    pos--;
  }
}
