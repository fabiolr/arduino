
#include <Adafruit_LIS3DH.h>
#include <ibis.h>

Adafruit_LIS3DH accel;

void setup() {
  // put your setup code here, to run once:
  
    Serial.begin(9600);

    accel.begin(0x18);                  //0x18 is the i2c address. 
                                      //This board can also use an address of 0x19,
                                      //but it requires different wiring.

    accel.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!


}


const int SectorN = 1;
const int SectorNW = 2;
const int SectorW = 3;
const int SectorOther = 0;

const int GestureNone = 0;
const int GestureTwistLeft = 1;

const long MaxGestureDuration = 400; //milliseconds
const long BounceDuration = 200;
const float RollError = 15.0;

int _lastSector = SectorOther;
long _lastTimeNorth = 0;
long _lastTimeWest = 0;




void loop() {

    long now = millis();
    accel.read();

    float roll = calcRollDegreesFromG(accel.x_g, accel.y_g, accel.z_g);

    Serial.print(roll); Serial.print(",");
//    Serial.print(pitch);
    Serial.println();

    


    // tell the accelerometer to read the X Y and Z data.
    accel.read();

    //  print out the raw data, which will between -32768 and 32767 (which is 16 bits)
    
    //Serial.print(accel.x); Serial.print(" ");
    //Serial.print(accel.y); Serial.print(" ");
    //Serial.print(accel.z); Serial.print(" ");

    //The accelerometer also gives us the value in g's 
    //(1g = acceleration due to gravity)
    //Serial.print(accel.x_g); Serial.print(" ");
    //Serial.print(accel.y_g); Serial.print(" ");
    //Serial.print(accel.z_g); Serial.print(" ");

    // float roll = calcRollDegreesFromG(accel.x_g, accel.y_g, accel.z_g);


    float pitch = calcPitchDegreesFromG(accel.x_g, accel.y_g, accel.z_g);

     
    
    if (gesture != 0) {
      Serial.print(roll); Serial.print(",");
      Serial.print(pitch);
      Serial.println();
    }
    
    int newSector = SectorOther;

      //First, determine our sector.
  //Our start point is roughly 0 degrees roll. We'll use a margin of error 
  //of 15 degrees in either direction
  if (roll >= - RollError && roll <= RollError) {  
    //we are in our starting point.
    newSector = SectorN;
  }
      else if (roll >= -90 - RollError && roll <= -90 + RollError) {
        newSector = SectorW;
  }
      else if (roll < - RollError && roll > -90 + RollError) {
        newSector = SectorNW;
  }
      else {
        newSector = SectorOther;
  }

  


  //Determine the gesture we detected, if any. Start by
  //assuming that we didn't detect one.
  int gesture = GestureNone;

  if (newSector == SectorW) {
    if ((_lastSector == SectorN || _lastSector == SectorNW) //check previous sector
        && now - _lastTimeNorth <= MaxGestureDuration
        && now - _lastTimeWest >= BounceDuration   //see how long it took
       )
    {
      gesture = GestureTwistLeft;
    }
  }

  if (gesture != GestureNone) {
    Serial.print(roll); Serial.print(" ");
    Serial.print(gesture); Serial.print(" ");

    Serial.println();
  }

  //remember our last values
  _lastSector = newSector;
  if (newSector == SectorN) {
    _lastTimeNorth = now;
  }
  else if (newSector == SectorW) {
    _lastTimeWest = now;
  }

  delay(50);
}



