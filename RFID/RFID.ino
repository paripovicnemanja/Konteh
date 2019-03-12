#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 53
#define RST_PIN 49

#define LED 28

String credentials = "{AndroidAP2/jurosevic/kth/5ddbd425-6b97-4cbd-b670-c221222ac694/}"; // change depending on your device and WiFi

MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class
void setup() {
   delay(3000);
   Serial.begin(9600);
   Serial1.begin(9600);
   delay(100);
   pinMode(LED, OUTPUT);
   SPI.begin();       // Init SPI bus
   mfrc522.PCD_Init(); // Init MFRC522
   Serial.println("RFID reading UID");
   Serial1.print(credentials);
}
void loop() {
if ( mfrc522.PICC_IsNewCardPresent())
    {
        if ( mfrc522.PICC_ReadCardSerial())
        {
           Serial.print("Tag UID:");
           for (byte i = 0; i < mfrc522.uid.size; i++) {
                  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                  Serial.print(mfrc522.uid.uidByte[i], HEX);
                  digitalWrite(LED, HIGH);
                  Serial1.print("Detected");
                  delay(1000);
                  digitalWrite(LED, LOW);
            }
         
            Serial.println();
            mfrc522.PICC_HaltA();
        }
}
} 
