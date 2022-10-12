#include "main.h"
#include "lib/Robot.h"

void autonomous() {
    Robot::threading.start("display", Robot::display_thread);
    Robot::threading.start("odometry", Robot::odom_thread);

}