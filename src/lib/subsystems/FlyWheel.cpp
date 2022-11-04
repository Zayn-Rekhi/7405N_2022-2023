#include "FlyWheel.h"
#include "../Robot.h"

FlyWheel::FlyWheel() {}

void FlyWheel::set_velocity(double speed_) {
    target_speed = speed_;
    printf("%.2f \n", target_speed);
}

double FlyWheel::get_velocity() {
    double vel1 = Robot::FLY1.get_actual_velocity() * 5 * 3;
    double vel2 = Robot::FLY2.get_actual_velocity() * 5 * 3;
    return (vel1 + vel2) / 2;
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

    Robot::FLY1.move_voltage(vel);
    Robot::FLY2.move_voltage(vel);
}