#include <SoftwareSerial.h>
#include <Servo.h>
#include "HX711.h"
#define DOUT  A1
#define CLK  A0
#define ARDUINO_RX 3  //should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 2  //connect to RX of the module
SoftwareSerial mp3(ARDUINO_RX, ARDUINO_TX);

HX711 scale(DOUT, CLK);
float calibration_factor = 360;
float GRAM;
int sensor_telur = A2, data_sensor;
int relay = 7, IR = 5, kunci = 0, kunci2 = 0;
int motor_1 = 10, motor_2 = 11;
Servo sortir;
Servo timbangan;
Servo bagus;
static int8_t Send_buf[8] = {0}; // Buffer for Send commands.  // BETTER LOCALLY
static uint8_t ansbuf[10] = {0}; // Buffer for the answers.    // BETTER LOCALLY

String mp3Answer;           // Answer from the MP3.

String sanswer(void);
String sbyte2hex(uint8_t b);

/************ Command byte **************************/
#define CMD_NEXT_SONG     0X01  // Play next song.
#define CMD_PREV_SONG     0X02  // Play previous song.
#define CMD_PLAY_W_INDEX  0X03
#define CMD_VOLUME_UP     0X04
#define CMD_VOLUME_DOWN   0X05
#define CMD_SET_VOLUME    0X06

#define CMD_SNG_CYCL_PLAY 0X08  // Single Cycle Play.
#define CMD_SEL_DEV       0X09
#define CMD_SLEEP_MODE    0X0A
#define CMD_WAKE_UP       0X0B
#define CMD_RESET         0X0C
#define CMD_PLAY          0X0D
#define CMD_PAUSE         0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F

#define CMD_STOP_PLAY     0X16  // Stop playing continuously. 
#define CMD_FOLDER_CYCLE  0X17
#define CMD_SHUFFLE_PLAY  0x18 //
#define CMD_SET_SNGL_CYCL 0X19 // Set single cycle.

#define CMD_SET_DAC 0X1A
#define DAC_ON  0X00
#define DAC_OFF 0X01

#define CMD_PLAY_W_VOL    0X22
#define CMD_PLAYING_N     0x4C
#define CMD_QUERY_STATUS      0x42
#define CMD_QUERY_VOLUME      0x43
#define CMD_QUERY_FLDR_TRACKS 0x4e
#define CMD_QUERY_TOT_TRACKS  0x48
#define CMD_QUERY_FLDR_COUNT  0x4f

/************ Opitons **************************/
#define DEV_TF            0X02


void setup() {
  Serial.begin(9600);
  mp3.begin(9600);
  sendCommand(CMD_SEL_DEV, 0, DEV_TF);
  sortir.attach(6);
  timbangan.attach(12);
  bagus.attach(4);
  timbangan.write(60);//idle
  bagus.write(20);//idle

  pinMode(relay, OUTPUT);
  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
  pinMode(IR, INPUT);
  pinMode(sensor_telur, INPUT);
  digitalWrite(relay, HIGH);
  scale.set_scale();
  scale.tare();
  digitalWrite(motor_1, LOW);
  delay(4000);
  //sortir.write(64);//busuk
  // bagus.write(30);//idle
  //timbangan.write(110);//bagus
  //sendCommand(0x03, 0, 1);//3=buruk,2=baik,1=sangat baik
}

void loop() {





}

void cek_telur() {
  digitalWrite(relay, LOW);
  data_sensor = analogRead(sensor_telur);
  //Serial.println(data_sensor);
  if (data_sensor > 500) {
    //Serial.println("Telur Busuk");
    sortir.write(64);//busuk
    sendCommand(0x03, 0, 3);//3=buruk,2=baik,1=sangat baik
    Serial.println("*Telur Busuk,-#");
  }
  else {
    //Serial.println("Telur Bagus");
    sortir.write(0);//bagus
  }
}



void cek_berat() {
  scale.set_scale(calibration_factor);
  GRAM = abs(scale.get_units());
  GRAM = GRAM, 4;
  //Serial.println(GRAM);
}







void sendCommand(byte command) {
  sendCommand(command, 0, 0);
}

void sendCommand(byte command, byte dat1, byte dat2) {
  delay(20);
  Send_buf[0] = 0x7E;    //
  Send_buf[1] = 0xFF;    //
  Send_buf[2] = 0x06;    // Len
  Send_buf[3] = command; //
  Send_buf[4] = 0x01;    // 0x00 NO, 0x01 feedback
  Send_buf[5] = dat1;    // datah
  Send_buf[6] = dat2;    // datal
  Send_buf[7] = 0xEF;    //
  //Serial.print("Sending: ");
  for (uint8_t i = 0; i < 8; i++)
  {
    mp3.write(Send_buf[i]) ;
    // Serial.print(sbyte2hex(Send_buf[i]));
  }
  //Serial.println();
}
String sbyte2hex(uint8_t b)
{
  String shex;

  shex = "0X";

  if (b < 16) shex += "0";
  shex += String(b, HEX);
  shex += " ";
  return shex;
}


/********************************************************************************/
/*Function: shex2int. Returns a int from an HEX string.                         */
/*Parameter: s. char *s to convert to HEX.                                      */
/*Parameter: n. char *s' length.                                                */
/*Return: int                                                                   */

int shex2int(char *s, int n) {
  int r = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] >= '0' && s[i] <= '9') {
      r *= 16;
      r += s[i] - '0';
    } else if (s[i] >= 'A' && s[i] <= 'F') {
      r *= 16;
      r += (s[i] - 'A') + 10;
    }
  }
  return r;
}


/********************************************************************************/
/*Function: sanswer. Returns a String answer from mp3 UART module.          */
/*Parameter:- uint8_t b. void.                                                  */
/*Return: String. If the answer is well formated answer.                        */

String sanswer(void)
{
  uint8_t i = 0;
  String mp3answer = "";

  // Get only 10 Bytes
  while (mp3.available() && (i < 10))
  {
    uint8_t b = mp3.read();
    ansbuf[i] = b;
    i++;

    mp3answer += sbyte2hex(b);
  }

  // if the answer format is correct.
  if ((ansbuf[0] == 0x7E) && (ansbuf[9] == 0xEF))
  {
    return mp3answer;
  }

  return "???: " + mp3answer;
}
