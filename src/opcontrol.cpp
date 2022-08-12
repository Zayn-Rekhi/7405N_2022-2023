#include "main.h"
#include "lib/Robot.h"

void opcontrol() {
    Robot::threading.start("driver", Robot::driver);
    Robot::threading.start("display", Robot::display);
    Robot::threading.start("odometry", Robot::odom);
}
