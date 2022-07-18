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

// Sensors
pros::Rotation Robot::LE(0);
pros::Rotation Robot::RE(0);
pros::Rotation Robot::BE(0);
pros::IMU Robot::IMU(0);


/* ========================================================================== */
/*                               Drive 🚗 🏎️ 🚘                               */
/* ========================================================================== */
Odometry Robot::odometry(0.0, 0.0, 0.0);

PID Robot::power(0.0, 0.0, 0.0, 0.0);
PID Robot::strafe(0.0, 0.0, 0.0, 0.0);
PID Robot::turn(0.0, 0.0, 0.0, 0.0);


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