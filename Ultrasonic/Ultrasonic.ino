#include <HardwareSerial.h>
// defines pins numbers
const int trigPin = 9;
const int echoPin = 8;

const int greenLed = 28;
const int redLed = 30;

String credentials = "{Radionice/1112131415/kth/5ddbd425-6b97-4cbd-b670-c221222ac694/}";

// defines variables

bool flagRed = false;
bool flagGreen = false;
bool pusteno = false;


long duration;
int distance = 0;
void setup() {
  delay(3000);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
  Serial1.begin(9600);
  delay(100);
  Serial1.print(credentials);
  delay(4000);
}
void loop() {
// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial1.print(distance);
  delay(2000);

 if(distance < 20)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  }
  if(distance >=20)
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
/*
  if(flagRed == true)
  {
    Serial1.write("RED");
    flagRed = false;
    delay(500);
  }
  if(flagGreen == true)
  {
    Serial1.write("GREEN");
    flagGreen = false;
    delay(500);
  }*/

  delay(500);
}
