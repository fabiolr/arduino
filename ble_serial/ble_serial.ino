#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>

Adafruit_BluefruitLE_SPI ble(8,7,6); //pins

int val = 0;
const int potPin = A0;

void setup() {
  
  pinMode(potPin, INPUT);
   
  ble.begin(false);

  ble.setMode(BLUEFRUIT_MODE_DATA);
}

void loop() {
  
  // val = (val + 5) % 0x1000;
  int potValue = analogRead(potPin);




  ble.println(potPin);
  delay(250);

  if (ble.available() > 0) {
    int readValue = ble.read();
    if (readValue == 'r') {
      val = 0;
      Serial.println("Got a reset message. Value now reset.");
    }
  }
}

