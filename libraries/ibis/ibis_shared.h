//
// Created by Daniel Dickinson on 1/7/16.
//

#ifndef ARDUINO_IBIS_SHARED_H
#define ARDUINO_IBIS_SHARED_H

// Constants
#define SENSORS_GRAVITY_EARTH             (9.80665F)              /**< Earth's gravity in m/s^2 */
#define SENSORS_GRAVITY_MOON              (1.6F)                  /**< The moon's gravity in m/s^2 */
#define SENSORS_GRAVITY_SUN               (275.0F)                /**< The sun's gravity in m/s^2 */
#define SENSORS_GRAVITY_STANDARD          (SENSORS_GRAVITY_EARTH)
#define SENSORS_MAGFIELD_EARTH_MAX        (60.0F)                 /**< Maximum magnetic field on Earth's surface */
#define SENSORS_MAGFIELD_EARTH_MIN        (30.0F)                 /**< Minimum magnetic field on Earth's surface */
#define SENSORS_PRESSURE_SEALEVELHPA      (1013.25F)              /**< Average sea level pressure is 1013.25 hPa */
#define SENSORS_DPS_TO_RADS               (0.017453293F)          /**< Degrees/s to rad/s multiplier */
#define SENSORS_GAUSS_TO_MICROTESLA       (100)                   /**< Gauss to micro-Tesla multiplier */

struct IbisXYZFloat {
    union {
        float v[3];
        struct {
            float x;
            float y;
            float z;
        };
    };
};

struct IbisOrientation {
    union {
        float v[3];
        struct {
            float roll;
            float pitch;
            float heading;
        };
    };
};

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);

float calcRollDegreesFromG(float x, float y, float z);

float calcPitchDegreesFromG(float x, float y, float z);



#endif //ARDUINO_IBIS_SHARED_H
