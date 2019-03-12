#include <HardwareSerial.h>

#define red_LED 28
#define yellow_LED 30
#define green_LED 32

#define button 38

bool buttonPressed = false;
bool buttonHold = false;
int counter = 0;
bool flag = false;

String credentials = "{Radionice/1112131415/kth/5ddbd425-6b97-4cbd-b670-c221222ac694/}"; // change depending on your device and WiFi

void setup() {
  // put your setup code here, to run once:
  delay(3000);
  pinMode(red_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(button, INPUT);

  digitalWrite(red_LED, HIGH);
  digitalWrite(yellow_LED, LOW);
  digitalWrite(green_LED, LOW);
  
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(100);
 
  Serial1.print(credentials);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  if(digitalRead(button) == HIGH)
  {
    buttonPressed = true;
  }
  if(digitalRead(button) == LOW)
  {
    buttonHold = false;
    buttonPressed = false;
  }

  if(buttonPressed && !buttonHold) 
  {
    buttonHold = true;

    counter++;
    flag = true;
    if(counter == 3)
    {
      counter = 0;
    }
  }

  if(counter == 0)
  {
    digitalWrite(red_LED, HIGH);
    digitalWrite(yellow_LED, LOW);
    digitalWrite(green_LED, LOW);
    if(flag == true)
    {
      Serial1.print("RED");
      flag = false;
    }
  }
  else if(counter == 1)
  {
    digitalWrite(red_LED, LOW);
    digitalWrite(yellow_LED, HIGH);
    digitalWrite(green_LED, LOW);
    if(flag == true)
    {
      Serial1.print("YELLOW");
      delay(50);
      flag = false;
    }
  }
  else
  {
    digitalWrite(red_LED, LOW);
    digitalWrite(yellow_LED, LOW);
    digitalWrite(green_LED, HIGH);
    if(flag == true)
    {
     Serial1.print("GREEN");
      flag = false;
    }
  }

  
}
