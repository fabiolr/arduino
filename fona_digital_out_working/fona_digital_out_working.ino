/***************************************************
  Adafruit MQTT Library FONA Example
  Designed specifically to work with the Adafruit FONA
  ----> http://www.adafruit.com/products/1946
  ----> http://www.adafruit.com/products/1963
  ----> http://www.adafruit.com/products/2468
  ----> http://www.adafruit.com/products/2542

  These cellular modules use TTL Serial to communicate, 2 pins are
  required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  Adafruit IO example additions by Todd Treece.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Adafruit_SleepyDog.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_FONA.h"

/****************************** Pins ****************************************/
#define PUMP        10
#define FONA_RX     9
#define FONA_TX     8
#define FONA_RST    4
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

/*************************** Cellular APN *************************************/

  // Optionally configure a GPRS APN, username, and password.
  // You might need to do this to access your network's GPRS/data
  // network.  Contact your provider for the exact APN, username,
  // and password values.  Username and password are optional and
  // can be removed, but APN is required.
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
// This is required for using the Adafruit MQTT library.
const char MQTT_SERVER[] PROGMEM    = AIO_SERVER;
// Set a unique MQTT client ID using the AIO key + the date and time the sketch
// was compiled (so this should be unique across multiple devices for a user,
// alternatively you can manually set this to a GUID or other random value).
const char MQTT_CLIENTID[] PROGMEM  = __TIME__ AIO_USERNAME;
const char MQTT_USERNAME[] PROGMEM  = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = AIO_KEY;

// Setup the FONA MQTT class by passing in the FONA class and MQTT server and login details.
Adafruit_MQTT_FONA mqtt(&fona, MQTT_SERVER, AIO_SERVERPORT, MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);

// You don't need to change anything below this line!
#define halt(s) { Serial.println(F( s )); while(1);  }

// FONAconnect is a helper function that sets up the FONA and connects to
// the GPRS network. See the fonahelper.cpp tab above for the source!
boolean FONAconnect(const __FlashStringHelper *apn, const __FlashStringHelper *username, const __FlashStringHelper *password);


/****************************** Feeds ***************************************/

// Setup a feed called 'pump' for subscribing to changes.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
const char PUMP_FEED[] PROGMEM = AIO_USERNAME "/feeds/pump";
Adafruit_MQTT_Subscribe pump = Adafruit_MQTT_Subscribe(&mqtt, PUMP_FEED);

/*************************** Sketch Code ************************************/

void setup() {

  // set power switch tail pin as an output
  pinMode(PUMP, OUTPUT);

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

  // Make sure to reset watchdog every loop iteration!
  Watchdog.reset();

  // ping adafruit io a few times to make sure we remain connected
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
      char x;
      Serial.print(F("Received: "));
      Serial.println(value);
      //int current = atoi(value);
      int current;
      if (String(value) == "ON") {

        Serial.println("Turn on the Pump now");
        current = 1;
      } 


      // write the current state to the power switch tail
      digitalWrite(PUMP, current == 1 ? HIGH : LOW);

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
