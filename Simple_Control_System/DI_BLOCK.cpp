#include "DI_BLOCK.h"

DI_BLOCK::DI_BLOCK(int pin)
{
    set_io_pin_in(pin);
}

DI_BLOCK::~DI_BLOCK()
{
}

// scan implementation
bool DI_BLOCK::scan() {
    bool result = 0;
    // scan interfaces with IO Modules
    // Different IO inputs and communication protocols
    // produces different scan function
    // this should be standardized once IO cards are finalized.
    result = digitalRead(io_in.pin);
    return result;
}
// setup implementation
void DI_BLOCK::setup() {
// set pin mode
    pinMode(io_in.pin, INPUT);
}

// loop implementation
void DI_BLOCK::loop () {
//  scan field value
    field_val_d = inverted ? !scan() : scan();
//  calculate pv
    pv_d = simulate_enable ? simulate_d : field_val_d;
//  generate alarm
    if (alarm_enable) {
        alarm_act = (pv_d == alarm_lim_d);
    } else {
        alarm_act = false;
    }
//  calculate out
    out_d = pv_d;
}

void DI_BLOCK::setSimulateMode(bool enable) {
    simulate_enable = enable;
}
void DI_BLOCK::setAlarmMode(bool enable) {
    alarm_enable = enable;
}
void DI_BLOCK::setAlarmLim(bool lim) {
    alarm_lim_d = lim;
}
void DI_BLOCK::setSimulateValue(bool val) {
    simulate_d = val;
}
void DI_BLOCK::setSimulateValue(int val) {
    simulate_d = val;
}
bool DI_BLOCK::getPv_d() {
    return pv_d;
}
bool DI_BLOCK::getOut_d() {
    return out_d;
}
bool DI_BLOCK::getFieldVal() {
    return field_val_d;
}

//interfacing with IO
void DI_BLOCK::set_io_pin_in(int pin) {
    io_in.pin = pin;
}