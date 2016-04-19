//
// Created by Daniel Dickinson on 1/27/16.
//

#ifndef ARDUINO_IBIS_ANALOG_SENSOR_H
#define ARDUINO_IBIS_ANALOG_SENSOR_H

class IbisAnalogSensor {
public:
    IbisAnalogSensor();

    // Intializes the pin for INPUT and optionally sets the filterBeta.
    // filterBeta must be between 0 and 10.
    // 0 is no filter, 10 is VERY smooth and lags way behind.
    // Anything 6 and below is practical, with 6 being very smooth and
    // removing most details without too much lag.
    // 2, 3, or 4 are better if you want to preserve more details.
    void begin(int pin, int filterBeta = 4);

    // Reads the smoothed value.
    int read();

    //Reads the raw, unsmoothed value.
    int readRaw();

    //Reads the smoothed value, but also passes back the raw unsmoothed value.
    //This is mainly intended for debugging and troubleshooting. For most
    //uses you would use the regular "read" that takes no parameters.
    int read(int * rawValueOut);

private:
    int _pin;
    long _smoothed = 0;
    int _beta = 4;
    int _fixedPointShift = 3;
};

#endif //ARDUINO_IBIS_ANALOG_SENSOR_H
