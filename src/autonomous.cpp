#include "main.h"
#include "lib/Robot.h"

void autonomous() {
    Robot::threading.start("odometry", Robot::odom_thread);
    Robot::threading.start("flywheel", Robot::flywheel_thread);
    Robot::threading.start("display", Robot::display_thread);
    Robot::threading.start("controller", Robot::controller_thread);

//    left_side();
//    right_side();
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

    pros::delay(250);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(30.0, 0), 3, 60, 80);

    pros::delay(250);


    Robot::turn.set_value(7, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(4, 1);

    pros::delay(250);

    Robot::INT = -60;


    pros::delay(2000);

//    Robot::turn.set_value(1.4, 0.001, 0.0, 6, 0.0);
//    Robot::drive.rotate_to(-52, 1);
//
//    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
//    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
//    Robot::drive.move_to(Pose(-10.3, 29.2), 3, 60, 80);



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

void left_side() {
    Robot::INT = 127;

    Robot::flywheel.set_velocity(2200);

    Robot::INT = 127;
    Robot::drive.move(-30, 0);

    pros::delay(550);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(0, 4), 1, 10000); // 0, -5

    pros::delay(250);

    Robot::turn.set_value(1.5, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-45, 1);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(-5.7, 10.3), 3, 10000); // 0, -5

    pros::delay(500);
    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(1.5, 2.5), 3, 10000); // 0, -5

    pros::delay(250);

    Robot::turn.set_value(1.5, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-7.5, 0.5);

    pros::delay(250);

    Robot::INT = -127;
    pros::delay(250);
    Robot::INT = -60;

    pros::delay(3000);

    Robot::INT = 0;
//25.9 23.2 30.3, 27.5
    Robot::turn.set_value(1.3, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(51.5, 1);

    pros::delay(250);

    Robot::INT = 0;

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(30.3, 27.5), 3, 10000, 50); // 0, -5

    Robot::INT = 127;

    pros::delay(250);

    Robot::flywheel.set_velocity(2000);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(39.2, 34.0), 3, 10000, 30); // 0, -5

    pros::delay(500);

    Robot::turn.set_value(1.3, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-31, 0.5);

    pros::delay(250);

    Robot::INT = -127;
//
//    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
//    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
//    Robot::drive.move_to(Pose(17.61, 17.33), 3, 10000, 100); // 0, -5
// 39.2 34.0
//    Robot::INT = 127;
//    pros::delay(250);
//
//
//    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
//    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
//    Robot::drive.move_to(Pose(48.87, 49.6), 8, 10000, 30); // 0, -5
//48.87 49.6
}

void awp() {}


