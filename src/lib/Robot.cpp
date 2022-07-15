//
// Created by zayn on 8/4/21.
//

#include "Robot.h"

/* ========================================================================== */
/*                             Robot 🧠🤔                                     */
/* ========================================================================== */

// Controller
pros::Controller Robot::Master(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor Robot::FL(0, false);  // Forward Left Drive Wheel
pros::Motor Robot::BL(0, true);   // Back Left Drive Wheel

pros::Motor Robot::FR(0, true);   // Forward Right Drive Wheel
pros::Motor Robot::BR(0, false);  // Back Right Drive Wheel

//port treated as lift rotation - Victor
pros::Rotation Robot::LE(8);
pros::Rotation Robot::RE(15);
pros::IMU Robot::IMU(9);

Odometry Robot::odometry(0.0, 0.0, 0.0, true);

/* ========================================================================== */
/*                               Drive 🚗 🏎️ 🚘                               */
/* ========================================================================== */

void Robot::driver(void *ptr) {
   while(true) {

   }
}


/* ========================================================================== */
/*                              Subsystems 🦾🦿                               */
/* ========================================================================== */


/* ========================================================================== */
/*                               Utility 🔨 ⛏ 🛠                             */
/* ========================================================================== */
Threading Robot::threading(100);
void Robot::display(void *ptr) {
    pros::delay(1000);

    while (true) {

        pros::lcd::print(1, "X: %.2f Y: %.2f H: %.2f", odometry.get_x(), odometry.get_y(), odometry.get_heading());

        pros::delay(5);
    }
}

void Robot::startOdometry(void *ptr) {
    while (true) {
        odometry.update();
        pros::delay(5);
    }
}

void Robot::startThreading() {
    threading.start("Odometry", Robot::startOdometry);
    threading.start("Display", Robot::display);
}
