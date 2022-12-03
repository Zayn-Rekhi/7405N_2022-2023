#include "FlyWheel.h"
#include "../Robot.h"
int FlyWheel::instances = 0;
FlyWheel::FlyWheel() {
    target_speed = 0;
    instances += 1;
    printf("FLYWHEEL CONSTRUCTED %d", instances);
}

void FlyWheel::set_velocity(double speed_) {
    target_speed.store(speed_);
}

double FlyWheel::get_velocity() {
    return Robot::FLY.get_actual_velocity() * 5 * 3;
}

// bool FlyWheel::is_settled(double threshold) {
//     bool settled = std::abs(target_speed - get_velocity()) < threshold;
//     if (settled && target_speed != 0) settle_count++;
//     if (settle_count >= 5) {
//         settle_count = 0;
//         return true;
//     }
//     return false;
// }

void FlyWheel::update() {
    double error = target_speed.load() - get_velocity();
    double vel = Robot::fly_controller.get_value(error);

    // printf("Target: %f Current: %f Error: %f Settled: %d Output: %f \n", target_speed, get_velocity(), error, vel);

    Robot::FLY.move_voltage(vel);
}