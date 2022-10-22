#include "main.h"
#include "lib/Robot.h"

void initialize() {
    pros::delay(250);
    pros::lcd::initialize();
    pros::delay(250);

    pros::delay(1000);
    Robot::IMU.reset();
    pros::delay(1000);

    Robot::LE.set_data_rate(5);
    Robot::RE.set_data_rate(5);
    Robot::BE.set_data_rate(5);

    Robot::LE.reset_position();
    Robot::RE.reset_position();
    Robot::BE.reset_position();

    Robot::LE.reverse();
    Robot::BE.reverse();

    Robot::FLYPIST.set_value(false);
    Robot::EXP1.set_value(false);

    pros::delay(250);
}