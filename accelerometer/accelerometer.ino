
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

void loop() {

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

  float roll = calcRollDegreesFromG(accel.x_g, accel.y_g, accel.z_g);
  float pitch = calcPitchDegreesFromG(accel.x_g, accel.y_g, accel.z_g);

    Serial.print(roll); Serial.print(",");
    Serial.print(pitch);
    Serial.println();




    delay(100); 


}


