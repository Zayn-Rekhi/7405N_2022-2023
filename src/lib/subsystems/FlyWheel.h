#pragma once;

#include "../drive/Drive.h"
#include <cmath>
#include "Odometry.h"

class FlyWheel{
    private:
        double flywheel_angle_;
        Pose goal_coords_; 

    public:
        FlyWheel(double flywheel_angle, Pose goal_coords);
    
        void shoot_disc();
};