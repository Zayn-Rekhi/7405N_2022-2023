#pragma once;

#include "../drive/Drive.h"
#include <cmath>
#include "Odometry.h"

class FlyWheel{
    private:
        double flywheel_angle_;
        Pose goal_coords_; 
        double flywheel_height_;

    public:
        FlyWheel(double flywheel_angle, Pose goal_coords, double flywheel_height);
    
        void shoot_disc();

        double get_velocity();
};