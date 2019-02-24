#ifndef structParameters_h
#define structParameters_h

struct IO_OUT
{
    int pin = 0;
};

struct IO_IN
{
    int pin = 0;
};

struct SCALE
{
    float lowRange = 0;
    float highRange = 100;
    // add Unit information
};



#endif