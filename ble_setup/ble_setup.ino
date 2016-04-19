//This sketch will dump out the Bluefruit device's address and name
//over the serial port.

#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>

Adafruit_BluefruitLE_SPI ble(8,7,6); //pins

void setup() {
  //Only using Serial for debugging.
  Serial.begin(9600);

  ble.begin(true); //verbose moode will echo commands to Serial port

  ble.setMode(BLUEFRUIT_MODE_COMMAND);

  ble.println("AT+BLEGETADDR");

  ble.readline();
  //Serial.println("Address:");
  //Serial.println(ble.buffer);
  ble.waitForOK();

  ble.println("AT+GAPDEVNAME");
  ble.waitForOK();

  ble.println("ATI");
  ble.waitForOK();

  while(true); //loop forever
}

void loop() {

}

