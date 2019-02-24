#include "DO_BLOCK.h"


DO_BLOCK::DO_BLOCK(int pin)
{
    set_io_pin_out(pin);
}

DO_BLOCK::~DO_BLOCK()
{
}

// scan implementation
void DO_BLOCK::write() {
    // write interfaces with IO Modules
    // Different IO outputs and communication protocols
    // produces different write function
    // this should be standardized once IO cards are finalized.
    digitalWrite(io_out.pin, out_d);
}
// setup implementation
void DO_BLOCK::setup() {
// set pin mode
    pinMode(io_out.pin, OUTPUT);
}

// loop implementation
void DO_BLOCK::loop () {
//  calculating mode information    
//  calculating pv_d
    pv_d = in_d;
//  calculate out
    out_d = pv_d;

    // write value to io_out
    write();
}

bool DO_BLOCK::getPv_d() {
    return pv_d;
}
bool DO_BLOCK::getOut_d() {
    return out_d;
}

//interfacing with IO
void DO_BLOCK::set_io_pin_out(int pin) {
    io_out.pin = pin;
}