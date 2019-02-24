#include "SCS_Helper.h"

float SCS_Helper::mapFloat(float val, float fromLow, float fromHigh, float toLow, float toHigh) {
    return (val - fromLow) / (fromHigh - fromLow) * (toHigh - toLow) + toLow;
}