#include "FlyWheel.h"
#include "../Robot.h"

FlyWheel::FlyWheel() {
    target_speed = 0;
}

void FlyWheel::set_velocity(double speed_) {
    target_speed.store(speed_);
}

double FlyWheel::get_velocity() {
    double velocity = Robot::FLY.get_actual_velocity() * 5 * 3;
    printf("%.2f \n", velocity - target_speed);
    double average = 0;

    bufferVel.push_back(velocity);
    if(bufferVel.size() == bufferVelSize) {
        bufferVel.pop_front();
        double sum = 0;
        for(int i = 0; i < bufferVel.size(); i++) sum += bufferVel[i];
        average = sum / bufferVelSize;
    }

    return average;
}

void FlyWheel::update() {
    double error = target_speed.load() - get_velocity();
    double vel = Robot::fly_controller.get_value(error);

    Robot::FLY.move_voltage(vel);
}