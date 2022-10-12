#include "Odometry.h"
#include "../Robot.h"

Odometry::Odometry(double horizontal_offset, double vertical_offset, double wheel_diameter_) : horizontal_offset_(horizontal_offset),
                                                                                               vertical_offset_(vertical_offset),
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
    double cur_heading = util::to_rad(Robot::IMU.get_rotation());

    double cur_LE = (Robot::LE.get_position() / 100.0f);
    double cur_RE = (Robot::RE.get_position() / 100.0f);
    double cur_BE = (Robot::BE.get_position() / 100.0f);

    double dLE = (cur_LE - prev_encs[0]) / 360.0f * wheel_circumference_;
    double dRE = (cur_RE - prev_encs[1]) / 360.0f * wheel_circumference_;
    double dBE = (cur_BE - prev_encs[2]) / 360.0f * wheel_circumference_;

    double d_theta = cur_heading - util::to_rad(cur_point.theta);
    double dMidPos = (dLE + dRE) / 2.0;
    double dPerpPos = dBE + vertical_offset_ * d_theta;

    double global_x = (dMidPos * std::sin(cur_heading) + dPerpPos * std::cos(cur_heading));
    double global_y = (dMidPos * std::cos(cur_heading) - dPerpPos * std::sin(cur_heading));

    cur_point.theta = util::to_deg(cur_heading);
    cur_point.x += global_x;
    cur_point.y += global_y;

    prev_encs = {cur_LE, cur_RE, cur_BE};
}
