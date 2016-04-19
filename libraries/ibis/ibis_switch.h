//
// Created by Daniel Dickinson on 1/27/16.
//

#ifndef ARDUINO_IBIS_SWITCH_H
#define ARDUINO_IBIS_SWITCH_H

class IbisSwitch {
public:
    IbisSwitch();

    void begin(int pin, int mode = INPUT_PULLUP, int debounceIntervalMs = 100);

    //Returns the current debounced value of the pin.
    int read();

    // Returns the current value of the pin, without debouncing.
    int readRaw();

    //Returns the debounced value, but also passes back the raw unsmoothed value.
    //This is mainly intended for debugging and troubleshooting. For most
    //uses you would use the regular "read" that takes no parameters.
    int read(int * rawValueOut);

private:
    long _lastTransitionTime = 0;
    int _lastDebouncedState;
    int _pin;
    int _debounceIntervalMs;
};

#endif //ARDUINO_IBIS_SWITCH_H
