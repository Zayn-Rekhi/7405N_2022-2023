//
// Created by zayn on 8/4/21.
//

#pragma once

#ifndef INC_7405K_2021_2022_ODOMETRY_H
#define INC_7405K_2021_2022_ODOMETRY_H

#include "main.h"
#include <vector>
#include <string>

/**
 * This is to make processing each point easier for the robot. Each point has an X coordinate, Y coordinate, and a
 * Heading.
 * @param x X Coordinate
 * @param y Y Coordinate
 * @param heading Angle/Rotation
 */
struct Point {
    double y_;
    double x_;
    double heading_;

    Point() : x_(0), y_(0), heading_(0) {}
    Point(double x, double y) : x_(x), y_(y), heading_(0) {}
    Point(double x, double y, double heading) : x_(x), y_(y), heading_(heading) {}
    
    bool operator==(const Point& p2) {
        return this->x_ == p2.x_ && this->y_ == p2.y_;
    }

    bool operator!=(const Point& p2) {
        return this->x_ != p2.x_ || this->y_ != p2.y_;
    }
};

class Odometry {
   private:

    Point cur_point;       // Current Point
    /* Robot specific params */

    /**
     * @brief Offset between Left Encoder or Right Encoder and the middle of the robot.
     */
    double horizontal_offset_;
    double vertical_offset_;
    double wheel_circumference_;  // Circumference of wheel

    /**
     * @brief Ability to use the IMU for calculating Heading or Encoders
     */
    bool IMU_turning_;

    /* Previous values of the Left Encoder, Right Encoder, and Back Encoder */
    double prev_LE, prev_RE;

    /* Velocities */
    double prev_time;
    double prev_LW, prev_RW;
    double vel_LW, vel_RW;

   public:
    Odometry(double horizontal_offset, double vertical_offset, double wheel_diameter, bool IMU_turning = false);

    void update();

    void set_x(double x);
    void set_y(double y);
    void set_heading(double heading);

    double get_x();
    double get_y();
    double get_heading(std::string unit = "deg");

    Point getPoint() { return cur_point; }
};

#endif  // INC_7405K_2021_2022_ODOMETRY_H
