#ifndef DO_BLOCK_h
#define DO_BLOCK_h

#include "Function_Block.h"

class DO_BLOCK: public Function_Block
{
private:
    bool in_d;
    // Function Block Mode implementation
    bool pv_d;
    bool out_d;
    IO_OUT io_out;

public:
    DO_BLOCK(int);
    ~DO_BLOCK();
    void write();
    void loop();
    void setup();
    bool getPv_d();
    bool getOut_d();
    
    // interfacing with IO
    void set_io_pin_out(int);
};

#endif