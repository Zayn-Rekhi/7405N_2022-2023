#include "main.h"
#include "lib/Robot.h"

void autonomous() {
    Robot::threading.start("odometry", Robot::odom_thread);
    Robot::threading.start("flywheel", Robot::flywheel_thread);
    Robot::threading.start("display", Robot::display_thread);
    Robot::threading.start("controller", Robot::controller_thread);

    right_side();
}

void skills() {}

void right_side() {
    Robot::INT = 127;

    Robot::flywheel.set_velocity(2600);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(0, 18.3), 1, 10000); // 0, -5

    pros::delay(250);

    Robot::turn.set_value(1.4, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-57, 1);

    pros::delay(250);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(30.0, -1.9), 3, 60, 80);

    pros::delay(250);

    Robot::turn.set_value(1.4, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(0, 1);

    pros::delay(250);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(30.0, -8), 3, 60, 80);

    pros::delay(100);

    Robot::INT = 127;
    Robot::drive.move(-30, 0);

    pros::delay(1000);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(30.0, 0), 3, 60, 80);

    pros::delay(250);


    Robot::turn.set_value(7, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(4, 1);
    Robot::INT = -60;


    pros::delay(2000);

    Robot::turn.set_value(1.4, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-52, 1);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(-10.3, 29.2), 3, 60, 80);



////
//    pros::delay(750);
//
//    Robot::turn.set_value(1.4, 0.001, 0.0, 6, 0.0);
//    Robot::drive.rotate_to(37, 1);
//
//    pros::delay(750);
//
//
//    Robot::turn.set_value(1.4, 0.001, 0.0, 6, 0.0);
//    Robot::drive.rotate_to(127, 0.5);
//
//    pros::delay(750);
//
//
//    Robot::power.set_value(5.5, 0.001, 0, 5, 10);
//    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
//    Robot::drive.move_to(Pose(28.00, -1.75), 5, 10000); // 0, -5
//
//    pros::delay(750);
//
//
//    Robot::turn.set_value(1.2, 0.001, 0.0, 6, 0.0);
//    Robot::drive.rotate_to(-10, 1);
}

void left_side() {}

void awp() {}


