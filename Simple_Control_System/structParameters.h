#ifndef structParameters_h
#define structParameters_h
#include <ADS1115_COMM.h>


struct IO_OUT
{
    int pin = 0;
};

struct Analog_IO_IN
{
    // IO_IN for all common IOs so i can't use ADS1115_COMM as card type. change this in the future
    ADS1115_COMM* card;
    int device;
    int channel;

};

struct Digital_IO_IN {
    int pin =  0;
};

struct SCALE
{
    float lowRange = 0;
    float highRange = 100;
    // add Unit information
};



#endif