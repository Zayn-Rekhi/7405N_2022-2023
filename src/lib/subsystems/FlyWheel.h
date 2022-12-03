#pragma once

#include "../controllers/TBH.h"
#include <atomic>
#include <cmath>

class FlyWheel{
     private:
        std::atomic<int> settle_count = 0;
        std::atomic<int> mode = 0;

     public:
         std::atomic<double> target_speed;

        FlyWheel();
        static int instances;

        double get_velocity();
        void set_velocity(double speed);

        void set_mode(int mode_) { mode = mode_; };
        int get_mode() { return mode; };

        bool is_settled(double threshold);
        void update();
 };