#include "FlyWheel.h"
#include "../Robot.h"

FlyWheel::FlyWheel() {}

void FlyWheel::set_velocity(double speed_) {
    target_speed = speed_;
    printf("%.2f \n", target_speed);
}

double FlyWheel::get_velocity() {
    return Robot::FLY.get_actual_velocity() * 5 * 3;
}

bool FlyWheel::is_settled(double threshold) {
    bool settled = std::abs(target_speed - get_velocity()) < threshold;
    if (settled && target_speed != 0) settle_count++;
    if (settle_count >= 5) {
        settle_count = 0;
        return true;
    }
    return false;
}

void FlyWheel::update() {
    double error = target_speed - get_velocity();
    double vel = Robot::fly_controller.get_value(error);

    printf("Target: %f Current: %f Error: %f Settled: %d Output: %f \n", target_speed, get_velocity(), error, vel);

    Robot::FLY.move_voltage(vel);
}