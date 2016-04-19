
#include "Adafruit_DRV2605.h"
Adafruit_DRV2605 drv;


const int pinPot = A0;
const int pinButton = 13;
int state = 0;
int counter = 0;
int incomingByte = 0;

void setup() {

// setup the heptic driver
  drv.begin();
  drv.setMode(DRV2605_MODE_INTTRIG); // default, internal trigger when sending GO command
  drv.selectLibrary(1);
  drv.setWaveform(0, 118);  // ramp up medium 1, see datasheet part 11.2
  drv.setWaveform(1, 1);  // strong click 100%, see datasheet part 11.2
  drv.setWaveform(2, 0);  // end of waveforms


  // start serial port
  Serial.begin(9600);

  // initialize used pins
  pinMode(pinPot, INPUT);
  pinMode(pinButton, INPUT);

  
}


void loop() {

  
  int levelPot = analogRead(pinPot);
  buttonState = digitalRead(pinButton);

   if (buttonState == HIGH) {

       Serial.println("B");
       
   }

//  check incoming serial to activate heptic
 
 //See if there is any data waiting to be read.
    if (Serial.available() > 0) {
      
       
        
        // read the first byte in the serial buffer:
        int incomingByte = Serial.read();
        
        if (incomingByte == 'H') {

            //play our vibrations
        drv.go();
        delay(75);
        drv.writeRegister8(DRV2605_REG_GO, 0);
        delay(3000);

        }

    }


//    Serial.print("Button: ");
//    Serial.print(state);
//    Serial.print(" Pot: ");
//    Serial.println(levelPot);


  
} // end loop


