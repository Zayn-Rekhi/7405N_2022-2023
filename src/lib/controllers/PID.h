//
// Created by zayn on 7/12/21.
//

#ifndef INC_7405K_2021_2022_PID_H
#define INC_7405K_2021_2022_PID_H
#include "vector"
#include "utility"
#include <ctime>

class PID {
   private:
    double kp;
    double ki;
    double kd;
    double integral_bound;

    double error_sum;
    double prev_error;
    int prev_time;

   public:
    PID(double p, double i, double d, double i_bound);
    double get_value(double error);
    void set_value(double p, double i, double d, double i_bound);
    void reset();
};

#endif  //INC_7405K_2021_2022_PID_H
