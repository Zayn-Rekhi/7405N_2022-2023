#include "FlyWheel.h"
#include "../Robot.h"

FlyWheel::FlyWheel(double flywheel_angle, Pose goal_coords) : flywheel_angle_(flywheel_angle), goal_coords_(goal_coords) {}

void FlyWheel::shoot_disc() {
    Robot::drive.rotate_to(goal_coords_);
    
}