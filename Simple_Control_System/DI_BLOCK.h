#ifndef DI_BLOCK_h
#define DI_BLOCK_h

#include "Function_Block.h"

class DI_BLOCK: public Function_Block
{
private:
    bool field_val_d;
    bool alarm_enable = false;
    bool alarm_act = false;
    bool alarm_lim_d = false;
    bool inverted = false;
    bool simulate_enable = false;
    bool simulate_d = 0;
    bool pv_d;
    bool out_d;
    IO_IN io_in;

public:
    DI_BLOCK(int);
    ~DI_BLOCK();
    bool scan();
    void loop();
    void setup();
    void setSimulateMode(bool);
    void setAlarmMode(bool);
    void setAlarmLim(bool);
    void setSimulateValue(bool);
    void setSimulateValue(int);
    bool getPv_d();
    bool getOut_d();
    bool getFieldVal();
    
    // interfacing with IO
    void set_io_pin_in(int);
};

#endif