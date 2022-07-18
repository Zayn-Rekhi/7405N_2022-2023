#pragma once

#include "main.h"
#include "../util/Pose.h"

#include <vector>
#include <string>

class Odometry {
    private:
        Pose cur_point;     

        double horizontal_offset_;
        double vertical_offset_;
        double wheel_circumference_;  

    public:
        Odometry(double horizontal_offset, double vertical_offset, double wheel_diameter);
        void update(void *ptr);

        Pose getPose() { return cur_point; }
        void setPose(Pose point) { cur_point = point; }
};
