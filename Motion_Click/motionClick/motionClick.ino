#include <HardwareSerial.h>

#define greenDiode 28
#define redDiode 26
#define motionClick 36

String credentials = "{AndroidAP2/execom123/kth/5ddbd425-6b97-4cbd-b670-c221222ac694/}"; // change depending on your device and WiFi

bool flagMotion = false;
bool state = false;
bool sent = false;

void setup() {
  // put your setup code here, to run once:
  delay(3000);
  pinMode(greenDiode, OUTPUT);
  pinMode(redDiode, OUTPUT);
  pinMode(motionClick, INPUT);


  digitalWrite(greenDiode, HIGH);
  digitalWrite(redDiode, LOW);

  Serial.begin(9600);
  Serial1.begin(9600);
  delay(100);
  Serial1.print(credentials);
  delay(4000);
}

void loop() {
  // put your main code here, to run repeatedly:

  state = digitalRead(motionClick);
  
  if(state == HIGH)
  {
    digitalWrite(greenDiode, LOW);
    digitalWrite(redDiode, HIGH);
    flagMotion = true;
    sent = 1;
  }
  if(state == LOW)
  {
    digitalWrite(greenDiode, HIGH);
    digitalWrite(redDiode, LOW);
    sent = 0;
  }

  if (flagMotion == true && sent == 0)
  {
    Serial1.write("RED");
    flagMotion = false;
  }
}
