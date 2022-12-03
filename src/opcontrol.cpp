#include "lib/subsystems/FlyWheel.h"
#include "main.h"
#include "lib/Robot.h"

void opcontrol() {
    pros::lcd::print(0, "OPCONTROL FLY SPEED: %.2f", Robot::flywheel.target_speed.load());
    Robot::auton_done.store(true);
    // Robot::threading.start("driver", Robot::driver_thread);
    // printf("jawn\n");
    // while(true){
    //     printf("FW Instances %d\n", FlyWheel::instances);
    //     pros::delay(20);
    // }
}
