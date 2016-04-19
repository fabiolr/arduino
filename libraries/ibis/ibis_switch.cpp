//
// Created by Daniel Dickinson on 1/27/16.
//

#include <Arduino.h>

#include "ibis_switch.h"

IbisSwitch::IbisSwitch()
        : _lastDebouncedState(HIGH)
{

}

void IbisSwitch::begin(int pin, int mode, int debounceIntervalMs)
{
    _lastTransitionTime = millis();
    _pin = pin;
    _debounceIntervalMs = debounceIntervalMs;

    pinMode(pin, mode);
}

int IbisSwitch::read(int * rawValueOut) {
    long now = millis();
    int raw = readRaw();
    *rawValueOut = raw;

    int debounced = raw;
    if (raw != _lastDebouncedState) {
        if (now - _lastTransitionTime >= _debounceIntervalMs) {
            //enough time has passed
            debounced = raw;
            _lastDebouncedState = raw;
        }
        else {
            //Not enough time has passed, so we'll chalk this up to noise.
            debounced = _lastDebouncedState;
        }
    }
    //else, the state has not changed, so there's no issue with debouncing.

    return debounced;
}

int IbisSwitch::read() {
    int raw;
    return read(&raw);
}

int IbisSwitch::readRaw() {
    return digitalRead(_pin);
}