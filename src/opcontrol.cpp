#include "main.h"
#include "lib/Robot.h"

void opcontrol() {
    Robot::threading.start("driver", Robot::driver_thread);
    Robot::threading.start("odometry", Robot::odom_thread);
    Robot::threading.start("flywheel", Robot::flywheel_thread);
    Robot::threading.start("display", Robot::display_thread);
    Robot::threading.start("controller", Robot::controller_thread);
}
