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

void right_side() {}

void left_side() {}

void awp() {}


