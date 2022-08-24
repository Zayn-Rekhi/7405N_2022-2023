#include "FlyWheel.h"
#include "../Robot.h"

FlyWheel::FlyWheel(double flywheel_angle, Pose goal_coords, double flywheel_height) : flywheel_angle_(flywheel_angle), goal_coords_(goal_coords), flywheel_height_(flywheel_height) {}

double FlyWheel::get_velocity() {
    double horizontal_dist = Robot::odometry.getPose().distanceTo(goal_coords_);
    double vertical_dist = 2.5-flywheel_height_;
    double numerator = pow(16.09, 0.5) * horizontal_dist;
    double denominator = util::to_deg(std::cos(flywheel_angle_))*pow(horizontal_dist*util::to_deg(std::sin(flywheel_angle_))/util::to_deg(std::cos(flywheel_angle_))-2.5,0.5);
    return numerator/denominator;
}

void FlyWheel::shoot_disc() {
    Robot::drive.rotate_to(goal_coords_);
    // Requirements to create flywheel launch code: Diameter of flywheel, how flywheel velocity relates to disc velocity
    //
    
}