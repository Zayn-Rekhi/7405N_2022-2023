#pragma once

#include "Odometry.h"
#include "../controllers/PID.h"
#include <array>
#include <cmath>
#include <deque>

class Drive {
    private:
        Pose prev;
        std::deque<double> motion;
        bool isMoving(double stop_threshold);

    public:
        Drive();

        void brake(pros::motor_brake_mode_e_t);

        void move(double power, double strafe, double turn, bool driver);
        void move_to(Pose target, std::array<double, 3> speeds = {1, 1, 1}, bool pp = false);
        
        void rotate_to(double angle);
        void rotate_to(Pose target);
};
