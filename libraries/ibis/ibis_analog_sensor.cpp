//
// Created by Daniel Dickinson on 1/27/16.
//
#include <Arduino.h>
#include <stdlib.h>

#include "ibis_analog_sensor.h"

IbisAnalogSensor::IbisAnalogSensor()
{
    //zero the buffer.

}

void IbisAnalogSensor::begin(int pin, int filterBeta)
{
    pinMode(pin, INPUT);
    _pin = pin;

    _beta = filterBeta;
}

// Reads the value and runs it through a low-pass filter to smooth it out.
// Reference:
//  Chatterjee, Kirit. "A Simple Digital Low-Pass Filter in C."
//   https://kiritchatterjee.wordpress.com/2014/11/10/a-simple-digital-low-pass-filter-in-c/
//   accessed Jan 2016
//
int IbisAnalogSensor::read(int * rawValueOut)
{
    long raw = readRaw();
    *rawValueOut = (int) raw;

    //Note: this is the basic formula if we are using floating point math.
    //_smoothed = _smoothed – (_beta * (_smoothed – raw));

    //However the ATMega processors don't have an FPU, so we will do fixed-point math,
    //which is really just integer math involve shifting around to simulate decimals.

    raw <<= _fixedPointShift; // Shift to fixed point

    _smoothed = (_smoothed << _beta) - _smoothed;
    _smoothed += raw;
    _smoothed >>= _beta;


    return (int) (_smoothed >> _fixedPointShift);

}

int IbisAnalogSensor::read()
{
    int raw;
    return read(&raw);
}

//Reads the raw, unsmoothed value.
int IbisAnalogSensor::readRaw()
{
    return analogRead(_pin);
}
