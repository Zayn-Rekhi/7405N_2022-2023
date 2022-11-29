#include "Robot.h"

// ---------------- lil qiao ---------------- //


/* ========================================================================== */
/*                             Robot 🧠🤔                                     */
/* ========================================================================== */

// Controller
pros::Controller Robot::master(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor Robot::FL(10, true);  // Forward Left Drive Wheel
pros::Motor Robot::CL(16, true);
pros::Motor Robot::BL(17, true);   // Back Left Drive Wheel
pros::Motor Robot::FR(3, false);   // Forward Right Drive Wheel
pros::Motor Robot::CR(5, false);
pros::Motor Robot::BR(15, false);  // Back Right Drive Wheel

// Intake
pros::Motor Robot::INT(12, true);

// Flywheel
pros::Motor Robot::FLY(6, false);

// Sensors
pros::IMU Robot::IMU(2);

// Expansion Pistons
pros::ADIDigitalOut Robot::EXP(3);


/* ========================================================================== */
/*                               Drive 🚗 🏎️ 🚘                               */
/* ========================================================================== */
Drive Robot::drive;
Odometry Robot::odometry(5.5, 2.75);

PID Robot::power(6.9, 0.00001, 0, 5, 0);
PID Robot::turn(0, 0, 0, 0, 0);

/* ========================================================================== */
/*                              Subsystems 🦾🦿                               */
/* ========================================================================== */
FlyWheel Robot::flywheel;
TBH Robot::fly_controller(1);

/* ========================================================================== */
/*                               Utility 🔨⛏ 🛠                               */
/* ========================================================================== */
Threading Robot::threading(100);
TeamSelection Robot::teamSelection = TeamSelection::UNKNOWN;

/* ========================================================================== */
/*                               Threads 🧵🪡                                 */
/* ========================================================================== */
void Robot::driver_thread(void *ptr) {
    FLY.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    int flyspeed_mode = 0;
    bool flyspeed_change = false;

    bool activate_triple_shot = false;
    int triple_shot_time = 0;

    while(true) {
        //Drive
        int power = master.get_analog(ANALOG_LEFT_Y);
        int turn = master.get_analog(ANALOG_RIGHT_X);

        if(std::abs(power) < 20) power = 0;
        if(std::abs(turn) < 20) turn = 0;

        drive.move(util::dampen(power), util::dampen(turn));

        //Intake
        bool intake = master.get_digital(DIGITAL_R2);
        bool outtake = master.get_digital(DIGITAL_R1);

        bool triple_shot = master.get_digital_new_press(DIGITAL_X);

        if(triple_shot && !activate_triple_shot) {
            activate_triple_shot = true;
        } else if(triple_shot && activate_triple_shot) {
            activate_triple_shot = false;
        }

        if(activate_triple_shot) {
            if(triple_shot_time <= 5) {
                INT = -127;
            } else if(triple_shot_time > 1000) {
                INT = 0;
                triple_shot_time = 0;
                activate_triple_shot = false;
            }

            triple_shot_time += 5;
        } else {
            if(intake) {
                INT = 127;
            } else if (outtake) {
                INT = -127;
            } else {
                INT = 0;
            }
        }


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
                flywheel.set_velocity(1600);
                break;
            case 2:
                flywheel.set_velocity(2500);
                break;
        }

        flywheel.set_mode(flyspeed_mode);

        // Ejector



        pros::delay(5);
    }
}

void Robot::display_thread(void *ptr) {
    while (true) {
        Pose cur = Robot::odometry.getPose();

        double RE_val = CL.get_position();
        double BE_val = CR.get_position();

        double l_temp = (FL.get_temperature() + CL.get_temperature() + BL.get_temperature()) / 3;
        double r_temp = (FR.get_temperature() + CR.get_temperature() + BR.get_temperature()) / 3;

        pros::lcd::print(1, "Left: %.2f %.2f %.2f", FL.get_actual_velocity(), CL.get_actual_velocity(), BL.get_actual_velocity());
        pros::lcd::print(2, "Right: %.2f %.2f %.2f", FR.get_actual_velocity(), CR.get_actual_velocity(), BR.get_actual_velocity());
        pros::lcd::print(3, "FT: %.1f LT: %.1f RT: %.1f ", FLY.get_temperature(), l_temp, r_temp);
        pros::lcd::print(4, "FT: %.1f LT: %.1f RT: %.1f ", FLY.get_temperature(), l_temp, r_temp);
        pros::lcd::print(5, "X=%.2f, Y=%.2f, A=%.2f", cur.x, cur.y, cur.theta);
        pros::lcd::print(6, "%.2f %.2f %.2f %.2f", FL.get_position(), FR.get_position(), CL.get_position(), CR.get_position());


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
    CL.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
    CR.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
    FL.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
    FR.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);

    CL.tare_position();
    CR.tare_position();
    FL.tare_position();
    FR.tare_position();

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