#include "main.h"
#include "lib/Robot.h"

void initialize() {
    Robot::EXP.set_value(true);

    pros::lcd::initialize();
    pros::delay(100);

    Robot::IMU.reset();
    while(Robot::IMU.is_calibrating()) { pros::delay(5); }

    Robot::CL.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    Robot::CR.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
}