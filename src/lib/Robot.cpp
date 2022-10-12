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

PID Robot::power(2.1, 0.1, 4.5, 5);
PID Robot::turn(10, 0.0, 0.0, 0.0);

/* ========================================================================== */
/*                              Subsystems 🦾🦿                               */
/* ========================================================================== */
FlyWheel Robot::flywheel;
TBH Robot::fly_controller(0.0000005);

/* ========================================================================== */
/*                               Utility 🔨 ⛏ 🛠                             */
/* ========================================================================== */
Threading Robot::threading(100);

/* ========================================================================== */
/*                               Threads 🧵🪡                                 */
/* ========================================================================== */
void Robot::driver_thread(void *ptr) {
    Pose target = Pose(6, 57, 0);
    bool goal_centric = false;
    int flyspeed_mode = 0;
    bool flyspeed_change = false;

    FLY1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    FLY2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    bool activate_ejector = false;


    while(true) {
        //Drive
        int power = master.get_analog(ANALOG_LEFT_Y);
        int turn = master.get_analog(ANALOG_RIGHT_X);

        if(std::abs(power) < 20) power = 0;
        if(std::abs(turn) < 20) turn = 0;

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
        bool shoot_inc = master.get_digital_new_press(DIGITAL_L1);
        bool shoot_dec = master.get_digital_new_press(DIGITAL_L2);

        if(shoot_inc && flyspeed_mode < 3) {
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

        switch(flyspeed_mode) {
            case 0:
                flywheel.set_velocity(0); //try setting the velocity just once
                break;
            case 1:
                flywheel.set_velocity(1000);
                break;
            case 2:
                flywheel.set_velocity(2000);
                break;
            case 3:
                flywheel.set_velocity(3000);
                break;
        }

        flywheel.set_mode(flyspeed_mode);

        // Ejector
        bool eject = master.get_digital_new_press(DIGITAL_X);
        bool triple_eject = master.get_digital_new_press(DIGITAL_A);

        if(triple_eject) {
            for(int i = 0; i < 6; i++) {
                printf("%.2f \n", i);
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
        pros::lcd::print(3, "%.2f %.2f", RE_val, LE_val);
        pros::lcd::print(4, "%.2f %.2f", BE_val, IMU.get_rotation());
        pros::lcd::print(5, "%.2f %.2f %.2f", cur.x, cur.y, cur.theta);
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
        flywheel.update();
        pros::delay(5);
    }
}