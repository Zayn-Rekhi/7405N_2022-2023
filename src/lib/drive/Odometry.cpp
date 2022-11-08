#include "Odometry.h"
#include "../Robot.h"

Odometry::Odometry(double horizontal_offset, double wheel_diameter_) : horizontal_offset_(horizontal_offset),
                                                                       wheel_circumference_(wheel_diameter_ * M_PI),
                                                                       cur_point(Pose()) {}



/**
 * Steps to updating Odometry:
 *   1. Get current encoder values
 *   2. Convert current encoder values to inches
 *   3. Update previous encoder values
 *   4. Calculate the difference in angle and the current angle
 *   5. Calculate the change in position (X and Y Coordinates)
 *   6. Rotate change in position by the change in angle
 *   7. Update X and Y coordinates
 */
void Odometry::update() {
    double curHeading = util::to_rad(Robot::IMU.get_rotation());
    double curLE = Robot::CL.get_position() / 100;
    double curRE = Robot::CR.get_position() / 100;

    double dLE = ((curLE - prev_encs[0]) / 360.0f) * wheel_circumference_;
    double dRE = ((curRE - prev_encs[1]) / 360.0f) * wheel_circumference_;

    prev_encs[0] = curLE;
    prev_encs[1] = curRE;

    double vertical_motion = (dRE + dLE) / 2;
    double posX = vertical_motion * std::cos(curHeading);
    double posY = vertical_motion * std::sin(curHeading);

    /* Updates current X and Y coordinates */
    cur_point.x += posX;
    cur_point.y += posY;
}
