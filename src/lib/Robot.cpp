#include "Robot.h"

/* ========================================================================== */
/*                             Robot 🧠🤔                                     */
/* ========================================================================== */

// Controller
pros::Controller Robot::master(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor Robot::FL(3, true);  // Forward Left Drive Wheel
pros::Motor Robot::BL(16, true);   // Back Left Drive Wheel
pros::Motor Robot::FR(18, false);   // Forward Right Drive Wheel
pros::Motor Robot::BR(10, false);  // Back Right Drive Wheel

// Intake
pros::Motor Robot::INT1(19, false);
pros::Motor Robot::INT2(1, true);

// Flywheel
pros::Motor Robot::FLY1(2, true);
pros::Motor Robot::FLY2(9, false);

// Sensors
pros::Rotation Robot::LE(21);
pros::Rotation Robot::RE(17);
pros::Rotation Robot::BE(20);
pros::IMU Robot::IMU(11);

// Flywheel Piston
pros::ADIDigitalOut Robot::FLYPIST(1);

// Expansion Pistons
pros::ADIDigitalOut Robot::EXP1(3);


/* ========================================================================== */
/*                               Drive 🚗 🏎️ 🚘                               */
/* ========================================================================== */
Drive Robot::drive;
Odometry Robot::odometry(7.38, 5.5, 2.75);

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

/* ========================================================================== */
/*                               Threads 🧵🪡                                 */
/* ========================================================================== */
void Robot::driver_thread(void *ptr) {
    Pose target = Pose(19, -111, 0);
    bool goal_centric = false;
    int flyspeed_mode = 0;
    bool flyspeed_change = false;

    int flyspeed = 0;

    FLY1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    FLY2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

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
            INT1 = 127;
            INT2 = 127;
        } else if (outtake) {
            INT1 = -127;
            INT2 = -127;
        } else {
            INT1 = 0;
            INT2 = 0;
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

        if(flyspeed_change && flywheel.is_settled()) {
            master.rumble(".");
            flyspeed_change = false;
        }
//
        switch(flyspeed_mode) {
            case 0:
                flywheel.set_velocity(0); //try setting the velocity just once
                break;
            case 1:
                flywheel.set_velocity(2500);
                break;
            case 2:
                flywheel.set_velocity(3000);
                break;
        }

        flywheel.set_mode(flyspeed_mode);

        // Ejector
        bool eject = master.get_digital_new_press(DIGITAL_X);
        bool triple_eject = master.get_digital_new_press(DIGITAL_A);

        if(triple_eject) {
            for(int i = 0; i < 6; i++) {
                if (i % 2 == 0) {
                    pros::delay(150);
                    FLYPIST.set_value(true);
                } else {
                    pros::delay(150);
                    FLYPIST.set_value(false);
                }
            }
        }

        if (eject && !activate_ejector) {
            FLYPIST.set_value(true);
            activate_ejector = true;
        } else if (activate_ejector) {
            pros::delay(150);
            FLYPIST.set_value(false);
            activate_ejector = false;
        }

        // Expansion
        bool expand = master.get_digital_new_press(DIGITAL_DOWN);
        if(expand) {
            EXP1.set_value(true);
            pros::delay(200);
        }

        pros::delay(5);
    }
}



void Robot::display_thread(void *ptr) {
    while (true) {
        Pose cur = Robot::odometry.getPose();

        double RE_val = RE.get_position();
        double BE_val = BE.get_position();
        double LE_val = LE.get_position();

        pros::lcd::print(1, "FL: %.2f FR: %.2f", FL.get_actual_velocity(), FR.get_actual_velocity());
        pros::lcd::print(2, "BL: %.2f BR: %.2f", BL.get_actual_velocity(), BR.get_actual_velocity());
        pros::lcd::print(3, "Temp1: %.2f Temp2: %.2f", FLY1.get_temperature(), FLY2.get_temperature());
        pros::lcd::print(4, "%.2f %.2f", BE_val, IMU.get_rotation());
        pros::lcd::print(5, "X: %.2f Y: %.2f Angle: %.2f", cur.x, cur.y, cur.theta);
        pros::lcd::print(6, "%.2f %.2f", FLY1.get_actual_velocity() * 5 * 3, FLY2.get_actual_velocity() * 5 * 3);

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
//        flywheel.update();
        pros::delay(5);
    }
}