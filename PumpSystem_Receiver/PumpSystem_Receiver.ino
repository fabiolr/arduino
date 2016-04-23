
#include <Adafruit_SleepyDog.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_FONA.h"

/****************************** Pins ****************************************/
#define RELAY_SET   10
#define RELAY_UNSET   11
#define FONA_RX     9
#define FONA_TX     8
#define FONA_RST    4
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

/*************************** Cellular APN *************************************/

#define FONA_APN       "wholesale"
#define FONA_USERNAME  ""
#define FONA_PASSWORD  ""

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "fabiolr"
#define AIO_KEY         "3f6755568fdf48359cde614c679539e0"

/************ Global State (you don't need to change this!) ******************/

// Store the MQTT server, client ID, username, and password in flash memory.
const char MQTT_SERVER[] PROGMEM    = AIO_SERVER;
// Set a unique MQTT client ID 
const char MQTT_CLIENTID[] PROGMEM  = __TIME__ AIO_USERNAME;
const char MQTT_USERNAME[] PROGMEM  = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = AIO_KEY;

// Setup the FONA MQTT
Adafruit_MQTT_FONA mqtt(&fona, MQTT_SERVER, AIO_SERVERPORT, MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);
#define halt(s) { Serial.println(F( s )); while(1);  }
// FONAconnect is a helper function that sets up the FONA and connects to GPRS
boolean FONAconnect(const __FlashStringHelper *apn, const __FlashStringHelper *username, const __FlashStringHelper *password);


/****************************** Feeds ***************************************/

// Setup a feed called 'pump' for subscribing to changes.
const char PUMP_FEED[] PROGMEM = AIO_USERNAME "/feeds/pump";
Adafruit_MQTT_Subscribe pump = Adafruit_MQTT_Subscribe(&mqtt, PUMP_FEED);

// Setup a feed called 'ack_pumpon' for publishing ack messages.
const char ACK_PUMPON_FEED[] PROGMEM = AIO_USERNAME "/feeds/ack_pumpon";
Adafruit_MQTT_Publish ack_pumpon = Adafruit_MQTT_Publish(&mqtt, ACK_PUMPON_FEED);

/*************************** Sketch Code ************************************/

void setup() {

  // set power switch tail pin as an output
  pinMode(RELAY_SET, OUTPUT);
  pinMode(RELAY_UNSET, OUTPUT);

  Serial.begin(115200);

  Serial.println(F("Adafruit IO Example:"));

  // Initialise the FONA module
  while (! FONAconnect(F(FONA_APN), F(FONA_USERNAME), F(FONA_PASSWORD)))
    halt("Retrying FONA");

  Serial.println(F("Connected to Cellular!"));

  Watchdog.reset();
  delay(3000);  // wait a few seconds to stabilize connection
  Watchdog.reset();

  // listen for events on the pump feed
  mqtt.subscribe(&pump);

  // connect to adafruit io
  connect();

}

void loop() {

  Adafruit_MQTT_Subscribe *subscription;

  Watchdog.reset();

  // ping adafruit io to make sure we remain connected
  if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }

  // this is our 'wait for incoming subscription packets' busy subloop
  while (subscription = mqtt.readSubscription(1000)) {

    // we only care about the pump events
    if (subscription == &pump) {

      // convert mqtt ascii payload to int
      char *value = (char *)pump.lastread;
      Serial.print(F("Received: "));
      int current = atoi(value);
      Serial.println(current);

      if (current == 1) {

          // we need to turn the pump on
            digitalWrite(RELAY_SET, HIGH);
            delay(50);
            digitalWrite(RELAY_SET, LOW);
            Serial.println("Relay Set");
            sendACK("1");

      }
      
      if (current == 0) {

          // we need to turn the pump OF
            digitalWrite(RELAY_UNSET, HIGH);
            delay(50);
            digitalWrite(RELAY_UNSET, LOW);
            Serial.println("Relay Unlatched");
            sendACK("0");

      }

      // write the current state to the power switch tail
   //   digitalWrite(PUMP, current == 1 ? HIGH : LOW);

      

    }

  }

}

// connect to adafruit io via MQTT
void connect() {

  Serial.print(F("Connecting to Adafruit IO... "));

  int8_t ret, retries = 5;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    retries--;

    if (retries == 0)
      halt("Resetting system");

    Serial.println(F("Retrying connection..."));
    delay(5000);

  }

  Serial.println(F("Adafruit IO Connected!"));

}

void sendACK(char* msg) {

           //Let's tell the server we turned the pump on.
          Serial.print(F("\nSending ACK"));
           if (! ack_pumpon.publish(msg))
           Serial.println(F("Failed."));
           else
           Serial.println(F("Success!"));

}

