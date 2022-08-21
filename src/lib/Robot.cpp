#include "Robot.h"

/* ========================================================================== */
/*                             Robot 🧠🤔                                     */
/* ========================================================================== */

// Controller
pros::Controller Robot::master(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor Robot::FL(13, true);  // Forward Left Drive Wheel
pros::Motor Robot::BL(19, true);   // Back Left Drive Wheel
pros::Motor Robot::FR(5, false);   // Forward Right Drive Wheel
pros::Motor Robot::BR(4, false);  // Back Right Drive Wheel

// Sensors
pros::Rotation Robot::LE(12);
pros::Rotation Robot::RE(14);
pros::Rotation Robot::BE(2);
pros::IMU Robot::IMU(6);


/* ========================================================================== */
/*                               Drive 🚗 🏎️ 🚘                               */
/* ========================================================================== */
Drive Robot::drive;
Odometry Robot::odometry(7.38, 5.5, 2.75);

PID Robot::power(2.1, 0.1, 4.5, 5);
PID Robot::strafe(6.1, 0.0, 0.0, 0.0);
PID Robot::turn(10, 0.0, 0.0, 0.0);


void Robot::driver(void *ptr) {
    Pose target = Pose(6, 57, 0);
    bool goal_centric = false;

    while(true) {
        int power = master.get_analog(ANALOG_LEFT_Y);
        int strafe = master.get_analog(ANALOG_LEFT_X);
        int turn = master.get_analog(ANALOG_RIGHT_X); 

        if(std::abs(power) < 20) power = 0;
        if(std::abs(strafe) < 20) strafe = 0;
        if(std::abs(turn) < 20) turn = 0;

        bool up_button = master.get_digital_new_press(DIGITAL_UP);
        if(up_button && !goal_centric) {
            goal_centric = true;
        } else if (up_button && goal_centric) {
            goal_centric = false;
        }

        if(goal_centric) {
            double angle = Robot::odometry.getPose().angleTo(target);
            double headingDegrees = Robot::odometry.getPose().phi;
            double curPosHeading = std::fmod(headingDegrees, 180.0) - 180.0 * std::round(headingDegrees / (360.0));
            double headingErr = angle - curPosHeading;
            if (std::fabs(headingErr) > 180.0) {
                headingErr = headingErr > 0.0 ? headingErr - 360.0 : headingErr + 360.0;
            }
            turn = Robot::turn.get_value(headingErr);
        }

        drive.move(power, strafe, turn, true); 
        pros::delay(5);
    }
}


/* ========================================================================== */
/*                              Subsystems 🦾🦿                               */
/* ========================================================================== */
Threading Robot::threading(100);

/* ========================================================================== */
/*                               Utility 🔨 ⛏ 🛠                             */
/* ========================================================================== */
void Robot::display(void *ptr) {
    while (true) {
        Pose cur = Robot::odometry.getPose();

        double RE_val = RE.get_position();
        double BE_val = BE.get_position();
        double LE_val = LE.get_position();

        pros::lcd::print(1, "FL: %.2f FR: %.2f", FL.get_actual_velocity(), FR.get_actual_velocity());
        pros::lcd::print(2, "BL: %.2f BR: %.2f", BL.get_actual_velocity(), BR.get_actual_velocity());
        pros::lcd::print(3, "%.2f %.2f", RE_val, LE_val);
        pros::lcd::print(4, "%.2f %.2f", BE_val, IMU.get_rotation());
        pros::lcd::print(5, "%.2f %.2f %.2f", cur.x, cur.y, cur.phi);

        pros::delay(5);
    }
}

void Robot::odom(void *ptr) {
    while(true) {
        odometry.update();
        pros::delay(5);
    }
}