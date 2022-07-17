#pragma once

/**
 * This is to make processing each point easier for the robot. Each point has an X coordinate, Y coordinate, and a
 * Heading.
 * @param x X Coordinate
 * @param y Y Coordinate
 * @param heading Angle/Rotation
 */
struct Pose {
    double y_;
    double x_;
    double heading_;

    Pose() : x_(0), y_(0), heading_(0) {}
    Pose(double x, double y) : x_(x), y_(y), heading_(0) {}
    Pose(double x, double y, double heading) : x_(x), y_(y), heading_(heading) {}
    
    bool operator==(const Pose& p2) {
        return this->x_ == p2.x_ && this->y_ == p2.y_;
    }

    bool operator!=(const Pose& p2) {
        return this->x_ != p2.x_ || this->y_ != p2.y_;
    }
};