#include "main.h"
#include "lib/Robot.h"

void autonomous() {
    left_side();
    // right_side();
}

void skills() {
    Robot::flywheel.set_velocity(2200);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);

    Robot::drive.move(-30, 0);

    pros::delay(550);
}
void right_side() {
    Robot::INT = 127;
    Robot::flywheel.set_velocity(1825);
    Robot::power.set_value(7.2 , 0.01, 0, 3, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(0.0, 25), 3, 100000, 100);

    pros::delay(250);
    
    Robot::turn.set_value(2.5, 0.001, 0.0, 5, 0.0);
    Robot::drive.rotate_to(23.75, 0.5);

    pros::delay(4000);

    Robot::INT = -127;
    pros::delay(400);
    Robot::INT = 0;
    pros::delay(300);

    Robot::INT = -127;
    pros::delay(400);
    Robot::INT = 0;
    pros::delay(300);

    Robot::INT = -127;
    pros::delay(400);
    Robot::INT = 0;
    pros::delay(300);

    pros::delay(2000);

    Robot::turn.set_value(1.6, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-45, 1);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(29.2, -2), 5, 90, 1000, 2000);

    pros::delay(250);
    Robot::turn.set_value(1.7, 0.001, 0.0, 5, 0.0);
    Robot::drive.rotate_to(0, 0.5);

    pros::delay(250);

    Robot::power.set_value(6.5, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(28.4, -8), 3, 60, 1000, 800);

    pros::delay(250);

    Robot::drive.move(-40, 0);
    Robot::INT = -100;
    pros::delay(520);
    Robot::drive.move(40, 0);
    Robot::INT = 127;
    pros::delay(220);
    Robot::drive.move(0, 0);
}

void left_side() {
    Robot::AC.set_value(true);

    Robot::flywheel.set_velocity(2250);

    Robot::drive.move(-40, 0);
    Robot::INT = -100;

    pros::delay(250);
    Robot::INT = 127;


    Robot::power.set_value(12, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(0, 4), 1, 10000, 127, 1000); // 0, -5

    Robot::INT = 127;  

    pros::delay(500);

    Robot::turn.set_value(2.5, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-32, 1);
//
    Robot::power.set_value(7.2, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(-5.7, 10.3), 3, 10000); // 0, -5

    pros::delay(500);
    Robot::power.set_value(7.2, 0.01, 0, 2, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(1.5, 2.5), 3, 10000); // 0, -5

    pros::delay(250);

    Robot::turn.set_value(3, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-12.25, 0.5);

    pros::delay(1500);
    Robot::INT = -127;
    pros::delay(400);
    Robot::INT = 0;
    pros::delay(400);

    Robot::INT = -127;
    pros::delay(600);
    Robot::INT = 0;
    pros::delay(400);

    Robot::INT = -127;
    pros::delay(600);
    Robot::INT = 0;
    pros::delay(400);

//     Robot::turn.set_value(1.5, 0.001, 0.0, 6, 0.0);
//     Robot::drive.rotate_to(49.5, 0.5);

//      pros::delay(250);

//     //  Robot::INT = 0;

//      Robot::power.set_value(6.5, 0.01, 0, 2, 10);
//      Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
//      Robot::drive.move_to(Pose(24.04, 25.32), 3, 10000, 90, 1000); // 0, -5

//      Robot::INT = 127;

// //
//      Robot::flywheel.set_velocity(1900);

//     //  Robot::power.set_value(6.5, 0.01, 0, 2, 10);
//     //  Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
//     //  Robot::drive.move_to(Pose(38.2, 34.0), 3, 10000, 50); // 0, -5


//     Robot::power.set_value(6.5, 0.01, 0, 2, 10);
//     Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
//     Robot::drive.move_to(Pose(46.2, 40.8), 3, 10000, 30); // 0, -5

//      pros::delay(2250);

//      Robot::turn.set_value(1.3, 0.001, 0.0, 6, 0.0);
//      Robot::drive.rotate_to(-35.5, 0.5);

//     pros::delay(500);

//     Robot::INT = -127;
//     pros::delay(600);
//     Robot::INT = 0;
//     pros::delay(300);

//     Robot::INT = -127;
//     pros::delay(600);
//     Robot::INT = 0;
//     pros::delay(300);

//     Robot::INT = -127;
//     pros::delay(600);
//     Robot::INT = 0;
//     pros::delay(300);
}

void awp() {}


