#include "ibis_shared.h"
#include "ibis_private.h"
#include <math.h>

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float calcRollDegreesFromG(float x, float y, float z)
{
    return atan2(x, z) * 180.0 / M_PI;
}

float calcPitchDegreesFromG(float x, float y, float z)
{
    return atan2(-y, sqrt(x * x + z * z)) * 180.0 / M_PI;

    //return atan2(-x, z) * 180.0 / PI;
}

