#include "Drive.h"


void Drive::move(double power, double strafe, double turn) {
    double powers[] {
		power + strafe + turn,
		power - strafe - turn,
		power - strafe + turn, 
		power + strafe - turn
	};

	int max = *std::max_element(powers, powers + 4);
	int min = abs(*std::min_element(powers, powers + 4));

	double true_max = double(std::max(max, min));
	double scalar = (true_max > 127) ? 127 / true_max : 1;
	
	Robot::FL = (power + strafe + turn) * scalar;
	Robot::FR = (power - strafe - turn) * scalar;
	Robot::BL = (power - strafe + turn) * scalar;
	Robot::BR = (power + strafe - turn) * scalar;
}

void Drive::move_to(Pose target, std::array<double, 3> speeds, bool pp) {}

void Drive::rotate_to(double angle) {}
void Drive::rotate_to_pose(Pose target) {}