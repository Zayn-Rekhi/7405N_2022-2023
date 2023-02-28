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
    printf("Error: %.2f Vel: %.2f \n", error, vel);

//    if (std::abs(error) < 300) {
//        vel = 0.001 * vel;
//    }
    Robot::FLY.move_voltage(vel);
}

bool FlyWheel::reached_target(double threshold) {
    int reached_target_count = 0;
    for (int i = 0; i < bufferVelSize; i++) {
        if(std::abs(target_speed.load() - get_velocity()) < threshold) {
            reached_target_count++;
        }
    }

    if(reached_target_count / bufferVelSize == 1) {
        return true;
    }

    return false;
}