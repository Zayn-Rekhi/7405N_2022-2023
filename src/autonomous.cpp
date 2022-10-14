#include "main.h"
#include "lib/Robot.h"

void autonomous() {
    Robot::threading.start("odometry", Robot::odom_thread);
    Robot::threading.start("flywheel", Robot::flywheel_thread);
    Robot::threading.start("display", Robot::display_thread);
    Robot::threading.start("controller", Robot::controller_thread);

    match1();
}

void match1() {
    Robot::drive.move(30, 0);
    pros::delay(200);
    Robot::INT1 = 120;
    Robot::INT2 = 120;
    pros::delay(180);
    Robot::INT1 = 0;
    Robot::INT2 = 0;

    Robot::drive.move(0, 0);

    Robot::power.set_value(8, 0.001, 0, 0);
    Robot::drive.move_to(Pose(0, -5), 0.4, 5); // 0, -5

    Robot::turn.set_value(1.4, 0.005, 0.0, 6);
    Robot::drive.rotate_to(160, 1);
}