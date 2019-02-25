#ifndef AI_BLOCK_h
#define AI_BLOCK_h

#include "Function_Block.h"

class AI_BLOCK
{
private:
    Analog_IO_IN io_in;
    float field_val;
    ADS1115_COMM* card;
    SCALE xd_scale;
    bool simulate_enable = false;
    float simulate_val = 0;
    float pv;
    float out;
    SCALE out_scale;
public:
    AI_BLOCK(ADS1115_COMM*, int, int);
    ~AI_BLOCK();
    float scan();
    void loop();
    void setup();
    void setSimulateMode(bool);
    void setSimulateValue(float);
    float getPv();
    float getOut();
    float getFieldVal();
    void setXdScale(SCALE);
    void setXdScale(float, float);
    void setOutScale(SCALE);
    void setOutScale(float, float);
    // interfacing with IO
    void set_io_pin_in(ADS1115_COMM*, int, int);
};


#endif
