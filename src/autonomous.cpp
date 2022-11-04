#include "main.h"
#include "lib/Robot.h"

void autonomous() {
    Robot::threading.start("odometry", Robot::odom_thread);
    Robot::threading.start("flywheel", Robot::flywheel_thread);
    Robot::threading.start("display", Robot::display_thread);
    Robot::threading.start("controller", Robot::controller_thread);



    skills();
//    right_side();
//    left_side();
//    awp();

}

void skills() {
    Robot::flywheel.set_velocity(2500);
    Robot::drive.move(30, 0);
    pros::delay(200);
    Robot::INT1 = 120;
    Robot::INT2 = 120;
    pros::delay(200);
    Robot::INT1 = 0;
    Robot::INT2 = 0;

    Robot::drive.move(0, 0);

    Robot::power.set_value(8, 0.001, 0, 0, 0.0);
    Robot::drive.move_to(Pose(0, -3), 0.4, 5); // 0, -5

    Robot::turn.set_value(1.5, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(117, 1);

    Robot::INT1 = 120;
    Robot::INT2 = 120;

    pros::delay(250);

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(1, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(25.2, -22.2), 2, 20, 90); // 0, -5

    Robot::turn.set_value(2.3, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(90, 1);

    Robot::drive.move(30, 0);


    pros::delay(750);
    Robot::INT1 = 0;
    Robot::INT2 = 0;

    Robot::drive.move(0, 0);
    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(20.5, -22.2), 3, 10000, 70); // 0, -5

    pros::delay(250);

    Robot::turn.set_value(1.6, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(180, 1);

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(18.9, -40.3), 5, 10000, 70); // 0, -5

    pros::delay(250);

    Robot::turn.set_value(6, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(173.5, 0.5);

    pros::delay(1000);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);

    pros::delay(700);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);

    pros::delay(700);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);

    pros::delay(500);

    Robot::turn.set_value(1.9, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(227, 0.5);

    pros::delay(250);

    Robot::INT1 = 120;
    Robot::INT2 = 120;

    Robot::flywheel.set_velocity(2600);

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(-35.9, -84.9), 5, 10000, 70); // 0, -5
    //-35.85 -84.9

    pros::delay(250);


    Robot::turn.set_value(1.3, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(125, 0.5);

    pros::delay(1000);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);

    pros::delay(700);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);

    pros::delay(700);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);

    pros::delay(500);

    Robot::turn.set_value(1.5, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(222, 0.5);

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(-57.1, -108.7), 5, 10000, 40); // 0, -5

    pros::delay(1000);

    Robot::turn.set_value(1.3, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(99.4, 0.5);
//
//    pros::delay(500);
//    Robot::FLYPIST.set_value(true);
//    pros::delay(250);
//    Robot::FLYPIST.set_value(false);
//
//    pros::delay(700);
//    Robot::FLYPIST.set_value(true);
//    pros::delay(250);
//    Robot::FLYPIST.set_value(false);
//    pros::delay(300);
//
//    pros::delay(700);
//    Robot::FLYPIST.set_value(true);
//    pros::delay(250);
//    Robot::FLYPIST.set_value(false);
//    pros::delay(300);
//
//    pros::delay(500);

    //-54.57 -102.7

}

void right_side() {
    Robot::flywheel.set_velocity(2350);

    Robot::INT1 = 120;
    Robot::INT2 = 120;

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0.5, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(0, 22.3), 5, 20); // 0, -5

    pros::delay(250);

    Robot::turn.set_value(5, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(15, 1);

    pros::delay(500);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);

    pros::delay(700);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);

    pros::delay(700);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);

    pros::delay(500);

    Robot::turn.set_value(1.8, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-42, 1);

    Robot::flywheel.set_velocity(2200);

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0.5, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(-27.9, 43.2), 5, 60, 80); // 0, -5

    pros::delay(750);

    Robot::turn.set_value(1.4, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(37, 1);

    pros::delay(500);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);

    pros::delay(700);
    Robot::FLYPIST.set_value(true);
    pros::delay(150);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);

    pros::delay(300);

    Robot::INT1 = 0;
    Robot::INT2 = 0;

    Robot::turn.set_value(1.6, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(131, 1);

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(1, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(30.72, -7.38), 5, 20, 105); // 0, -5

    Robot::drive.move(30, 0);


    pros::delay(400);
    Robot::INT1 = -120;
    Robot::INT2 = -120;
    pros::delay(600);
    Robot::INT1 = 0;
    Robot::INT2 = 0;

    Robot::drive.move(0, 0);

//
//    Robot::turn.set_value(1.7, 0.001, 0.0, 6, 0.0);
//    Robot::drive.rotate_to(180, 1);
//

//


}

void left_side() {
    Robot::flywheel.set_velocity(2300);
    Robot::drive.move(30, 0);
    pros::delay(200);
    Robot::INT1 = 120;
    Robot::INT2 = 120;
    pros::delay(200);
    Robot::INT1 = 0;
    Robot::INT2 = 0;

    Robot::drive.move(0, 0);

    Robot::power.set_value(8, 0.001, 0, 0, 0.0);
    Robot::drive.move_to(Pose(0, -5), 0.4, 5); // 0, -5

    Robot::turn.set_value(1.35, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(163.6, 1);

    pros::delay(1300);
    Robot::FLYPIST.set_value(true);
    pros::delay(150);
    Robot::FLYPIST.set_value(false);

    pros::delay(1200);
    Robot::FLYPIST.set_value(true);
    pros::delay(150);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);

    Robot::turn.set_value(1.8, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(90, 1);

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0.5, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(-11.3, -12.2), 5, 20, 80); // 0, -5

    Robot::turn.set_value(1.9, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(135, 1);

    pros::delay(250);

    Robot::INT1 = 127;
    Robot::INT2 = 127;

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0.0, 0.0, 0.0, 0.0, 0.0);
    Robot::drive.move_to(Pose(-1.6, -28.4), 5, 100000, 40); // 0, -5

    pros::delay(1000);

    Robot::flywheel.set_velocity(2300);


    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0.0, 0.0, 0.0, 0.0, 0.0);
    Robot::drive.move_to(Pose(-4.8, -23.7), 5, 100000, 40); // 0, -5

    Robot::turn.set_value(2.3, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(160.5, 0.5);

    pros::delay(1000);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);

    pros::delay(1000);
    Robot::FLYPIST.set_value(true);
    pros::delay(150);
    Robot::FLYPIST.set_value(false);

    pros::delay(1000);
    Robot::FLYPIST.set_value(true);
    pros::delay(150);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);
}


void awp() {
    Robot::flywheel.set_velocity(2500);
    Robot::drive.move(30, 0);
    pros::delay(200);
    Robot::INT1 = 120;
    Robot::INT2 = 120;
    pros::delay(250);
    Robot::INT1 = 0;
    Robot::INT2 = 0;

    Robot::drive.move(0, 0);

    Robot::power.set_value(8, 0.001, 0, 0, 0.0);
    Robot::drive.move_to(Pose(0, -5), 0.4, 5); // 0, -5

    Robot::turn.set_value(1.4, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-125, 1);


    pros::delay(500);

    Robot::INT1 = 127;
    Robot::INT2 = 127;

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0.5, 0, 0.0, 0, 0.0);
    Robot::drive.move_to(Pose(-16.8, -24.2), 5, 20); // 0, -5

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::drive.move_to(Pose(-45.2, -42.8), 2, 20, 40); // 0, -5

    pros::delay(500);
    Robot::turn.set_value(1.5, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-229, 1);

    pros::delay(500);
    Robot::FLYPIST.set_value(true);
    pros::delay(250);
    Robot::FLYPIST.set_value(false);

    pros::delay(500);
    Robot::FLYPIST.set_value(true);
    pros::delay(150);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);

    pros::delay(500);
    Robot::FLYPIST.set_value(true);
    pros::delay(150);
    Robot::FLYPIST.set_value(false);
    pros::delay(300);



    pros::delay(500);

    Robot::turn.set_value(1.7, 0.001, 0.0, 6, 0.0);
    Robot::drive.rotate_to(-141, 1);

    Robot::INT1 = 0;
    Robot::INT2 = 0;

    pros::delay(750);

    Robot::power.set_value(6.9, 0.00001, 0, 5, 10);
    Robot::turn.set_value(0, 0, 0.0, 0.0, 0.0);
    Robot::drive.move_to(Pose(-92.3, -106.3), 5, 40, 90); // 0, -5

    Robot::drive.move(30, 0);


    pros::delay(400);
    Robot::INT1 = -120;
    Robot::INT2 = -120;
    pros::delay(550);
    Robot::INT1 = 0;
    Robot::INT2 = 0;

    Robot::drive.move(0, 0);

}


