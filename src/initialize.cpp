#include "main.h"
#include "lib/Robot.h"

void initialize() {
    Robot::EXP1.set_value(true);
    Robot::FLYPIST.set_value(true);

    pros::lcd::initialize();
    pros::delay(100);

    Robot::IMU.reset();
    while(Robot::IMU.is_calibrating()) { pros::delay(5); }

    Robot::LE.set_data_rate(5);
    Robot::RE.set_data_rate(5);
    Robot::BE.set_data_rate(5);

    Robot::LE.reset_position();
    Robot::RE.reset_position();
    Robot::BE.reset_position();

    Robot::LE.reverse();
    Robot::BE.reverse();
}