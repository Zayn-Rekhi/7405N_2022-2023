#include "Robot.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "subsystems/FlyWheel.h"

// ---------------- lil qiao ---------------- //


/* ========================================================================== */
/*                             Robot 🧠🤔                                     */
/* ========================================================================== */
// bruh
std::atomic<bool> Robot::auton_done = false;
// Controller
pros::Controller Robot::master(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor Robot::FL(10, true);  // Forward Left Drive Wheel
pros::Motor Robot::CL(16, true); //
pros::Motor Robot::BL(17, true); //  // Back Left Drive Wheel
pros::Motor Robot::FR(7, false);   // Forward Right Drive Wheel
pros::Motor Robot::CR(5, false); //
pros::Motor Robot::BR(20, false); // // Back Right Drive Wheel

// Intake
pros::Motor Robot::INT(12, true); //

// Flywheel
pros::Motor Robot::FLY(6, false);

// Sensors
pros::IMU Robot::IMU(9);

// Expansion Pistons
pros::ADIDigitalOut Robot::EXP({{19, 'A'}});
pros::ADIDigitalOut Robot::AC({{19, 'C'}});



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
TBH Robot::fly_controller(2);

/* ========================================================================== */
/*                               Utility 🔨⛏ 🛠                               */
/* ========================================================================== */
Threading Robot::threading(100);
TeamSelection Robot::teamSelection = TeamSelection::UNKNOWN;

/* ========================================================================== */
/*                               Threads 🧵🪡                                 */
/* ========================================================================== */
void Robot::driver_thread(void *ptr) {
    while(true){
        if(!auton_done){
            pros::delay(5);
        } else {
            FLY.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

            int flyspeed_mode = 0;
            bool flyspeed_change = false;
            double flyspeed = 0;

            bool activate_triple_shot = false;
            int triple_shot_time = 0;
            int numShots = 0;
            int shot_time_start = 0;

            bool activate_single_shot = false;
            int single_shot_time = 0;

            bool activate_angle_change = false;

            INT.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

            while(true) {
                //Drive
                int power = master.get_analog(ANALOG_LEFT_Y);
                int turn = master.get_analog(ANALOG_RIGHT_X);

//        if(std::abs(power) < 20) power = 0;
//        if(std::abs(turn) < 20) turn = 0;

                drive.move(power, util::dampen(turn));

                //Intake
                bool intake = master.get_digital(DIGITAL_R2);
                bool outtake = master.get_digital(DIGITAL_R1);

                bool triple_shot = master.get_digital_new_press(DIGITAL_A);
                bool single_shot = master.get_digital_new_press(DIGITAL_X);


                if(triple_shot && !activate_triple_shot) {
                    activate_triple_shot = true;
                } else if(triple_shot && activate_triple_shot) {
                    activate_triple_shot = false;
                }

                if(single_shot && !activate_single_shot) {
                    activate_single_shot = true;
                } else if(single_shot && activate_single_shot) {
                    activate_single_shot = false;
                }

                if (intake || outtake) {
                    activate_triple_shot = false;
                    activate_single_shot = false;
                    numShots = 0;
                    triple_shot_time = 0;
                    single_shot_time = 0;
                }

                if(activate_triple_shot) {
                    bool shoot = false;
                    if (fabs(flywheel.get_velocity()) > fabs((0.85 * flyspeed))) {
                        INT = -127;
                        shoot = true;
                        if (pros::millis() - shot_time_start > 500) {
                            ++numShots;
                            shot_time_start = pros::millis();
                        }
                    }

                    if (triple_shot_time > 2500) {
                        INT = 0;
                        activate_triple_shot = false;
                        numShots = 0;
                        triple_shot_time = 0;
                    } else if (!shoot) {
                        INT = 0;
                    }

                    triple_shot_time += 5;
                } else if (activate_single_shot) {
                    if(single_shot_time <= 5) {
                        INT = -127;
                    } else if(single_shot_time > 300) {
                        INT = 0;
                        single_shot_time = 0;
                        activate_single_shot = false;
                    }

                    single_shot_time += 5;
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


                pros::lcd::print(7, "%.2f fwsmode %d", pros::millis(), flyspeed_mode);

                flywheel.set_mode(flyspeed_mode);

                // Expansion
                bool expand = master.get_digital_new_press(DIGITAL_DOWN);

                if(expand) {
                    EXP.set_value(true);
                }

                //Angle Change
                bool angle_change = master.get_digital_new_press(DIGITAL_B);

                if(angle_change && !activate_angle_change) {
                    AC.set_value(false);
                    activate_angle_change = true;
                } else if(angle_change && activate_angle_change) {
                    AC.set_value(true);
                    activate_angle_change = false;
                }

                switch(flyspeed_mode) {
                    case 0:
                        flyspeed = 0; //try setting the velocity just once
                        break;
                    case 1:
                        flyspeed = 1375;
                        break;
                    case 2:
                        flyspeed = 2500;
                        break;
                }

                if(activate_angle_change && flyspeed_mode) {
                    flyspeed = 1375;
                }

                flywheel.set_velocity(flyspeed);
                pros::delay(5);
            }}
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
        pros::lcd::print(3, "FT: %.1f LT: %.1f RT: %.1f IT: %.1f ", FLY.get_temperature(), l_temp, r_temp, INT.get_temperature());
        pros::lcd::print(4, "X=%.2f, Y=%.2f, A=%.2f", cur.x, cur.y, cur.theta);
        pros::lcd::print(5, "%.2f %.2f %.2f %.2f", FL.get_position(), FR.get_position(), CL.get_position(), CR.get_position());

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