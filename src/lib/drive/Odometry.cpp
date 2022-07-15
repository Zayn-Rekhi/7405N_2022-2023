//
// Created by zayn on 8/4/21.
//

#include "Odometry.h"

#define TO_RAD(n) n * M_PI / 180;
#define TO_DEG(n) n * 180 / M_PI;

Odometry::Odometry(double horizontal_offset, double vertical_offset, double wheel_diameter_, bool IMU_turning) : horizontal_offset_(horizontal_offset),
                                                                                                                vertical_offset_(vertical_offset),
                                                                                                                wheel_circumference_(wheel_diameter_ * M_PI),
                                                                                                                IMU_turning_(IMU_turning),
                                                                                                                cur_point(Point(0, 0, 0)) {
                                                                                                                    Robot::LE.reset_position();
                                                                                                                    Robot::RE.reset_position();
                                                                                                                    Robot::LE.reset();
                                                                                                                    Robot::RE.reset();
                                                                                                                    Robot::LE.reverse();
                                                                                                                }



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
    double cur_phi = TO_RAD(Robot::IMU.get_rotation());
    double dphi = cur_phi - cur_point.heading_;

    double cur_turn_offset_x = 360 * (horizontal_offset_ * dphi) / wheel_circumference_;
    double cur_turn_offset_y = 360 * (vertical_offset_ * dphi) / wheel_circumference_;

    double turn_offset_x = (float) turn_offset_x + cur_turn_offset_x;
    double turn_offset_y = (float) turn_offset_y + cur_turn_offset_y;

    double cur_y = ((Robot::LE.get_value() - turn_offset_y) + (Robot::RE.get_value() + turn_offset_y)) / 2;
    double cur_x = Robot::BE.get_value() - turn_offset_x;

    double dy = cur_y - cur_point.y_;
    double dx = cur_x - cur_point.x_;

    double global_dy = dy * std::cos(cur_phi) + dx * std::sin(cur_phi);
    double global_dx = dx * std::cos(cur_phi) - dy * std::sin(cur_phi);
    
    cur_point.y_ = (float) cur_point.y_ + global_dy;
    cur_point.x_ = (float) cur_point.x_ + global_dx;
}


/**
 * @param x X coordinate to be set
 */
void Odometry::set_x(double x) {
    cur_point.x_ = x;
}

/**
 * @param y Y coordinate to be set
 */
void Odometry::set_y(double y) {
    cur_point.y_ = y;
}

/**
 * @param heading heading to be set
 */
void Odometry::set_heading(double heading) {
    if (!IMU_turning_)
        cur_point.heading_ = heading;
}

/**
* @return X value of current coordinate
*/
double Odometry::get_x() {
    return cur_point.x_;
}

double Odometry::get_y() {
    return cur_point.y_;
}

/**
 * @param type The type of unit the angle should be converted to
 * @return The current angle that the robot is facing
 */
double Odometry::get_heading(std::string unit) {
    if (unit.compare("deg") == 0) {
        return TO_DEG(cur_point.heading_);
    } else {
        return cur_point.heading_;
    }
}
