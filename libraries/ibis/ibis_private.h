//
// Created by Daniel Dickinson on 1/7/16.
//

#ifndef ARDUINO_IBIS_PRIVATE_H
#define ARDUINO_IBIS_PRIVATE_H

#if ARDUINO >= 100
#include "Arduino.h"
#else

#include "WProgram.h"

#endif

#ifdef __AVR_ATtiny85__
#include "TinyWireM.h"
#define Wire TinyWireM
#else

#include <Wire.h>

#endif

#endif //ARDUINO_IBIS_PRIVATE_H
