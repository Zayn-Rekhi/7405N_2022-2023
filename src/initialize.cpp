#include "main.h"
#include "lib/Robot.h"
#define IMUDELAYTIME 5000


void initialize() {
    Robot::EXP.set_value(true);

    pros::lcd::initialize();
    pros::delay(100);

    Robot::IMU.reset();
    int time = 0;
    while(Robot::IMU.is_calibrating()) {
        time += 5;
        if(time > IMUDELAYTIME)
            break;
        pros::delay(5);
    }
}

void competition_initialize() {}

void disabled() {}