#pragma once

#include "../controllers/TBH.h"
#include <cmath>

class FlyWheel{
     private:
        double target_speed = 0;
        double prev_vel = 0;
        int settle_count = 0;
        int mode = 0;

     public:
        FlyWheel();

        double get_velocity();
        void set_velocity(double speed);

        void set_mode(int mode_) { mode = mode_; };
        int get_mode() { return mode; };

        bool is_settled();
        void update();
 };