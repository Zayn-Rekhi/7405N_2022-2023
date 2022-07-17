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

Odometry Robot::odometry(0.0, 0.0, 0.0);

/* ========================================================================== */
/*                               Drive 🚗 🏎️ 🚘                               */
/* ========================================================================== */

void Robot::driver(void *ptr) {
   while(true) {
        pros::delay(5);
   }
}


/* ========================================================================== */
/*                              Subsystems 🦾🦿                               */
/* ========================================================================== */


/* ========================================================================== */
/*                               Utility 🔨 ⛏ 🛠                             */
/* ========================================================================== */
void Robot::display(void *ptr) {
    pros::delay(1000);

    while (true) {
        pros::delay(5);
    }
}