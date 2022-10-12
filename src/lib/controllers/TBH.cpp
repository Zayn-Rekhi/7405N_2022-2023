#include "TBH.h"

TBH::TBH(double _gain) {
    gain = _gain;
}

double TBH::get_value(double error) {
    output += gain * error;

    if(output > 1) output = 1;
    else if (output < -1) output = -1;

    if (std::signbit(error) != std::signbit(prev_error)) {
        output = 0.5 * (output + tbh);
        tbh = output;
    }

    prev_error = error;
    return output;
}

void TBH::reset() {
    tbh = 0;
    prev_error = 0;
}