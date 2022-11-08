#include "Robot.h"

/* ========================================================================== */
/*                             Robot 🧠🤔                                     */
/* ========================================================================== */

// Controller
pros::Controller Robot::master(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor Robot::FL(21, true);  // Forward Left Drive Wheel
pros::Motor Robot::CL(7, false);
pros::Motor Robot::BL(16, false);   // Back Left Drive Wheel
pros::Motor Robot::FR(13, false);   // Forward Right Drive Wheel
pros::Motor Robot::CR(3, true);
pros::Motor Robot::BR(5, true);  // Back Right Drive Wheel

// Intake
pros::Motor Robot::INT(19, false);

// Flywheel
pros::Motor Robot::FLY(2, true);

// Sensors
pros::IMU Robot::IMU(11);

// Expansion Pistons
pros::ADIDigitalOut Robot::EXP(3);


/* ========================================================================== */
/*                               Drive 🚗 🏎️ 🚘                               */
/* ========================================================================== */
Drive Robot::drive;
Odometry Robot::odometry(5.5, 2.75);

PID Robot::power(6.9, 0.00001, 0, 5, 0);
PID Robot::turn(0, 0, 0, 0, 0);
//PID Robot::turn(1.4, 0.005, 0.0, 6);

/* ========================================================================== */
/*                              Subsystems 🦾🦿                               */
/* ========================================================================== */
FlyWheel Robot::flywheel;
TBH Robot::fly_controller(1);

/* ========================================================================== */
/*                               Utility 🔨 ⛏ 🛠                             */
/* ========================================================================== */
Threading Robot::threading(100);
TeamSelection Robot::teamSelection = TeamSelection::UNKNOWN;

/* ========================================================================== */
/*                               Threads 🧵🪡                                 */
/* ========================================================================== */
void Robot::driver_thread(void *ptr) {
    Pose target = Pose(19, -111, 0);
    bool goal_centric = false;
    int flyspeed_mode = 0;
    bool flyspeed_change = false;

    int flyspeed = 0;

    FLY.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    bool activate_ejector = false;

    Robot::turn.set_value(5, 0, 0, 0, 0);

    while(true) {
        //Drive
        int power = master.get_analog(ANALOG_LEFT_Y);
        int turn = master.get_analog(ANALOG_RIGHT_X);

        if(std::abs(power) < 20) power = 0;
        if(std::abs(turn) < 20) turn = 0;

//        bool up_button = master.get_digital_new_press(DIGITAL_UP);
//        if(up_button && !goal_centric) {
//            goal_centric = true;
//        } else if (up_button && goal_centric) {
//            goal_centric = false;
//        }
//
//        if(goal_centric) {
//            double angle = Robot::odometry.getPose().angleTo(target);
//            double headingDegrees = Robot::odometry.getPose().theta;
//            double curPosHeading = std::fmod(headingDegrees, 180.0) - 180.0 * std::round(headingDegrees / (360.0));
//            double headingErr = angle - curPosHeading;
//            if (std::fabs(headingErr) > 180.0) {
//                headingErr = headingErr > 0.0 ? headingErr - 360.0 : headingErr + 360.0;
//            }
//            turn = Robot::turn.get_value(headingErr);
//        }

        drive.move(power, turn);


        //Intake
        bool intake = master.get_digital(DIGITAL_R2);
        bool outtake = master.get_digital(DIGITAL_R1);

        if(intake) {
            INT = 127;
        } else if (outtake) {
            INT = -127;
        } else {
            INT = 0;
        }



        // Shoot
//        bool shoot_inc = master.get_digital_new_press(DIGITAL_L1);
//        bool shoot_dec = master.get_digital_new_press(DIGITAL_L2);
//
//        if (shoot_inc) flyspeed += 50;
//        if (shoot_dec) flyspeed -= 50;
//
//        if (flyspeed > 3200) flyspeed = 3200;
//        if (flyspeed < 0) flyspeed = 0;
//
//        flywheel.set_velocity(flyspeed);
//        printf("%.2f \n", flyspeed);

        //2500 2450

        bool shoot_inc = master.get_digital_new_press(DIGITAL_L1);
        bool shoot_dec = master.get_digital_new_press(DIGITAL_L2);

        if(shoot_inc && flyspeed_mode < 2) {
            flyspeed_mode++;
            fly_controller.reset();
            flyspeed_change = true;
        }

        if (shoot_dec && flyspeed_mode > 0) {
            flyspeed_mode--;
            fly_controller.reset();
            flyspeed_change = true;
        }

        if(flyspeed_change) {
            master.rumble("___");
            flyspeed_change = false;
        }

        switch(flyspeed_mode) {
            case 0:
                flywheel.set_velocity(0); //try setting the velocity just once
                break;
            case 1:
                flywheel.set_velocity(2100);
                break;
            case 2:
                flywheel.set_velocity(2300);
                break;
        }

        flywheel.set_mode(flyspeed_mode);

        // Ejector

        bool roller = master.get_digital_new_press(DIGITAL_B);
        if(roller) {
            INT = 127;
            INT = 127;

            drive.move(30, 0);
            pros::delay(250);

            INT = 127;
            INT = 127;
        }

        pros::delay(5);
    }
}



void Robot::display_thread(void *ptr) {
    while (true) {
        Pose cur = Robot::odometry.getPose();

        pros::lcd::print(1, "Left: %.2f %.2f %.2f", FL.get_actual_velocity(), CL.get_actual_velocity(), BL.get_actual_velocity());
        pros::lcd::print(1, "Right: %.2f %.2f %.2f", FR.get_actual_velocity(), CR.get_actual_velocity(), BR.get_actual_velocity());
        pros::lcd::print(3, "Temp: %.2f", FLY.get_temperature());
        pros::lcd::print(4, "X: %.2f Y: %.2f Angle: %.2f", cur.x, cur.y, cur.theta);

        pros::delay(5);
    }
}

void Robot::controller_thread(void *ptr) {
    while (true) {
        if(flywheel.get_mode() == 0) {
            master.print(1, 0, "");
        } else if(flywheel.get_mode() == 1) {
            master.print(1, 0, "####");
        } else if(flywheel.get_mode() == 2) {
            master.print(1, 0, "########");
        } else if(flywheel.get_mode() == 3) {
            master.print(1, 0, "#############");
        }

        pros::delay(50);
    }
}

void Robot::odom_thread(void *ptr) {
    while(true) {
        odometry.update();
        pros::delay(5);
    }
}

void Robot::flywheel_thread(void *ptr) {
    while(true) {
        flywheel.update();
        pros::delay(5);
    }
}