#include "FlyWheel.h"
#include "../Robot.h"

FlyWheel::FlyWheel() {}

void FlyWheel::set_velocity(double speed) {
    target_speed = speed;
}

double FlyWheel::get_velocity() {
    double vel1 = Robot::FLY1.get_actual_velocity() * 5 * 3;
    double vel2 = Robot::FLY2.get_actual_velocity() * 5 * 3;
    return (vel1 + vel2) / 2;
}

bool FlyWheel::is_settled() {
    bool settled = std::abs(target_speed - get_velocity()) < 40;
    if (settled) settle_count++;
    if (settle_count >= 5) {
        settle_count = 0;
        return true;
    }
    return false;
}

void FlyWheel::update() {
    double error = target_speed - get_velocity();
    double vel = Robot::fly_controller.get_value(error);

//    printf("Target: %f Current: %f Error: %f \n", target_speed, get_velocity(), error);

//    printf("%f %f \n", vel - prev_vel, error);

//    if(std::abs(vel - prev_vel) > 0.00005) {
//        int sign = vel - prev_vel < 0 ? -1 : 1;
//        vel += sign * 0.0000000005;
//    }

    Robot::FLY1.move_voltage(vel);
    Robot::FLY2.move_voltage(vel) ;
    prev_vel = vel;
}