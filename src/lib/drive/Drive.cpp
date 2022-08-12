#include "Drive.h"
#include "../Robot.h"

Drive::Drive() {}

bool Drive::isMoving(double stop_threshold) {
	Pose error = Robot::odometry.getPose() - prev;
	if (motion.size() == 10) 
		motion.pop_front();
    motion.push_back(std::abs(error.x) + std::abs(error.y));
    
	double sum = 0;
	for (int i = 0; i < motion.size(); i++) sum += motion[i];
	double motion_average = sum / 10;

	if (motion_average < stop_threshold) return true;
	return false;

}

void Drive::brake(pros::motor_brake_mode_e_t brake) {
    Robot::FL.set_brake_mode(brake);
    Robot::FR.set_brake_mode(brake);
    Robot::BL.set_brake_mode(brake);
    Robot::BR.set_brake_mode(brake);
}

void Drive::move(double power, double strafe, double turn, bool driver) {
    double scalar = 1;

    double powers[] {
        power + strafe + turn,
        power - strafe - turn,
		power - strafe + turn, 
		power + strafe - turn
    };

    if(!driver) {
		int max = *std::max_element(powers, powers + 4);
		int min = abs(*std::min_element(powers, powers + 4));

		double true_max = double(std::max(max, min));
		scalar = (true_max > 127) ? 127 / true_max : 1;
    } 

    Robot::FL = powers[0] * scalar;
    Robot::FR = powers[1] * scalar;
    Robot::BL = powers[2] * scalar;
    Robot::BR = powers[3] * scalar; 
}

void Drive::move_to(Pose target, std::array<double, 3> speeds, bool pp) {
	Pose error = target - Robot::odometry.getPose();	
	int time = pros::millis();

    while (std::abs(error.y) > 0.1 || std::abs(error.x) > 0.1 || std::abs(error.phi) > 1) {   
		Pose cur = Robot::odometry.getPose();
        
		double power = Robot::power.get_value(error.y * std::cos(cur.phi) + error.x * std::sin(cur.phi)) * speeds[0];
        double strafe = Robot::strafe.get_value(error.x * std::cos(cur.phi) - error.y * std::sin(cur.phi)) * speeds[1];
        double turn = Robot::turn.get_value(error.phi) * speeds[2];


        move(power, strafe, turn, false);
        error = target - cur;
		pros::delay(5);

    }

	move(0, 0, 0, false);
	brake(pros::E_MOTOR_BRAKE_HOLD);

	motion = std::deque<double>();	
	Robot::power.reset();    
	Robot::strafe.reset();
	Robot::turn.reset();	
}

void Drive::rotate_to(double angle) {
	Pose cur = Robot::odometry.getPose();
	cur.phi = angle;
	move_to(cur);
}

void Drive::rotate_to(Pose target) {
	double angle = Robot::odometry.getPose().angleTo(target);
	Pose cur = Robot::odometry.getPose();
	cur.phi = angle;
	move_to(cur);
}
