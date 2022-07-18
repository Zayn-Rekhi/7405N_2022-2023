#include "Odometry.h"
#include "../Robot.h"

#define TO_RAD(n) n * M_PI / 180
#define TO_DEG(n) n * 180 / M_PI

Odometry::Odometry(double horizontal_offset, double vertical_offset, double wheel_diameter_) : horizontal_offset_(horizontal_offset),
                                                                                               vertical_offset_(vertical_offset),
                                                                                               wheel_circumference_(wheel_diameter_ * M_PI),
                                                                                               cur_point(Pose(0, 0, 0)) {}



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
void Odometry::update(void *ptr) {
    while(true) {
        double cur_phi = TO_RAD(Robot::IMU.get_rotation());
        double dphi = cur_phi - cur_point.phi;

        double cur_turn_offset_x = 360 * (horizontal_offset_ * dphi) / wheel_circumference_;
        double cur_turn_offset_y = 360 * (vertical_offset_ * dphi) / wheel_circumference_;

        double turn_offset_x = (float) turn_offset_x + cur_turn_offset_x;
        double turn_offset_y = (float) turn_offset_y + cur_turn_offset_y;

        double cur_y = ((Robot::LE.get_position() - turn_offset_y) + (Robot::RE.get_position() + turn_offset_y)) / 2;
        double cur_x = Robot::BE.get_position() - turn_offset_x;

        double dy = cur_y - cur_point.y;
        double dx = cur_x - cur_point.x;

        double global_dy = dy * std::cos(cur_phi) + dx * std::sin(cur_phi);
        double global_dx = dx * std::cos(cur_phi) - dy * std::sin(cur_phi);
        
        cur_point.x = (float) cur_point.x + global_dx;
        cur_point.y = (float) cur_point.y + global_dy;
        cur_point.phi = TO_DEG(cur_phi);
    }

}
