#include "TrapezoidalProfile.h"


TrapezoidalProfile::TrapezoidalProfile(double max_vel, double acc, double dec, double target) : max_vel(max_vel), 
                                                                                    acc(acc), 
                                                                                    dec(dec), 
                                                                                    target(target), 
                                                                                    time_acc(max_vel / acc), 
                                                                                    time_dec(max_vel / dec) {
    double dist_acc = 0.5 * this->time_acc * this->max_vel;
    double dist_dec = 0.5 * this->time_dec * this->max_vel;
    double dist_slew = this->target - (dist_acc + dist_dec);

    this->time_slew = dist_slew / this->max_vel;
    this->time_total = this->time_acc + this->time_slew + this->time_dec;
}

double TrapezoidalProfile::get_acc(double time) {
    if(time <= this->time_acc) {
        return time * this->acc;
    } else if (time <= this->time_acc + this-> time_slew) {
        return this->max_vel;
    } else if (time <= this->time_total) {
        return (this->time_total - time) * this->dec;
    } else {
        return 0;
    }
}

double TrapezoidalProfile::get_time_total() {
    return time_total * 1000;
}