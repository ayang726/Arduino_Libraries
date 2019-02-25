#include "AI_BLOCK.h"


AI_BLOCK::~AI_BLOCK()
{
}

AI_BLOCK::AI_BLOCK(ADS1115_COMM* card, int device, int channel) {
    set_io_pin_in(card, device, channel);
}

// scan implementation
float AI_BLOCK::scan() {
    float result = 0;
    // scan interfaces with IO Modules
    // Different IO inputs and communication protocols
    // produces different scan function
    // this should be standardized once IO cards are finalized.
    // right now assuming direct interfacing with arduino
    result = io_in.card->readAnalogValueFrom(io_in.device, io_in.channel);
    return result;
}
// setup implementation
void AI_BLOCK::setup() {
// set pin mode
// part of IO interfacing. must have a input

    // pinMode(io_in.pin, INPUT);
}

// loop implementation
void AI_BLOCK::loop () {
//  scan field value
    field_val = scan();
//  calculate pv
    pv = simulate_enable ? simulate_val : field_val;
//  calculate out
    out = SCS_Helper::mapFloat(pv, xd_scale.lowRange, xd_scale.highRange, out_scale.lowRange, out_scale.highRange);
}

void AI_BLOCK::setSimulateMode(bool enable) {
    simulate_enable = enable;
}

void AI_BLOCK::setSimulateValue(float val) {
    simulate_val = val;
}
float AI_BLOCK::getPv() {
    return pv;
}
float AI_BLOCK::getOut() {
    return out;
}
float AI_BLOCK::getFieldVal() {
    return field_val;
}

void AI_BLOCK::setXdScale(SCALE scale) {
    xd_scale = scale;
}
void AI_BLOCK::setXdScale(float low, float high) {
    xd_scale.highRange = high;
    xd_scale.lowRange = low;
}

void AI_BLOCK::setOutScale(SCALE scale) {
    out_scale = scale;
}
void AI_BLOCK::setOutScale(float low, float high) {
    out_scale.lowRange = low;
    out_scale.highRange = high;
}

//interfacing with IO
void AI_BLOCK::set_io_pin_in(ADS1115_COMM* card, int device, int channel) {
    io_in.card = card;
    io_in.device = device;
    io_in.channel = channel;
}