#include "main.h"
#include "lib/Robot.h"

void autonomous() {
    Robot::threading.start("display", Robot::display);
    Robot::threading.start("odometry", Robot::odom);

    Robot::drive.rotate_to(Pose(10, 0, 0));
}