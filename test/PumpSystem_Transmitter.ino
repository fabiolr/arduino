// mynumber: 786-543-8766

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_CC3000.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_MQTT_FONA.h>

#include <Adafruit_FONA.h>

#define FONA_RX  9
#define FONA_TX  8
#define FONA_RST 4
#define FONA_RI  7

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


void setup() {

  
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }

  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

