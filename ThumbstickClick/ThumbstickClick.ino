#include <SPI.h>
#include <HardwareSerial.h>

#define SELPIN 53    // chip-select
#define DATAOUT 51   // MOSI
#define DATAIN 50    // MISO
#define SPICLOCK 52  // Clock
#define BTN 11

#define UP 24
#define DOWN 26
                   
String credentials = "{AndroidAP2/execom123/kth/5ddbd425-6b97-4cbd-b670-c221222ac694/}"; // change depending on your WiFi and device { SSID /  wifi password / device key / device password  }

int readvalue;
int readvalue_LR;
//String incoming = "";
int flagUp = 0;
int flagDown = 0;
int hold = 0;

void setup() {
  //set pin modes
  delay(3000);
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);

  pinMode(SELPIN, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK, OUTPUT);
  digitalWrite(SELPIN, HIGH);
  digitalWrite(DATAOUT, LOW);
  digitalWrite(SPICLOCK, LOW);

  Serial.begin(9600);
  Serial1.begin(9600);
  delay(100);
  Serial1.print(credentials);
}

void loop() {
  readvalue = read_adc(1);
  //readvalueLR = read_adc(2);  // read value left/right - help for additional task  

  if (readvalue > 3500)
  {
    digitalWrite(UP, HIGH);
    flagUp = 1;
  }
  else if (readvalue < 200)
  {
    digitalWrite(DOWN, HIGH);
    flagDown = 1;
  }
  else
  {
    digitalWrite(UP, LOW);
    digitalWrite(DOWN, LOW);
    hold = 0;
    flagUp = 0;
    flagDown = 0;
  }
  if (flagUp == 1 && hold == 0)
  {
    Serial1.write("NAPRED");
    flagUp = 0;
    hold = 1;
  }
  if (flagDown == 1 && hold == 0)
  {
    Serial1.write("NAZAD");
    flagDown = 0;
    hold = 1;
  }
}

int read_adc(int channel) {
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits |= ((channel - 1) << 3);

  digitalWrite(SELPIN, LOW); //Select adc
  // setup bits to be written
  for (int i = 7; i >= 3; i--) {
    digitalWrite(DATAOUT, commandbits & 1 << i);

    //cycle clock
    digitalWrite(SPICLOCK, HIGH);
    digitalWrite(SPICLOCK, LOW);
  }

  digitalWrite(SPICLOCK, HIGH);   //ignores 2 null bits
  digitalWrite(SPICLOCK, LOW);
  digitalWrite(SPICLOCK, HIGH);
  digitalWrite(SPICLOCK, LOW);

  //read bits from adc
  for (int i = 11; i >= 0; i--) {
    adcvalue += digitalRead(DATAIN) << i;
    //cycle clock
    digitalWrite(SPICLOCK, HIGH);
    digitalWrite(SPICLOCK, LOW);

  }
  digitalWrite(SELPIN, HIGH); //turn off device
  return adcvalue;
}
