#pragma once

/**
 * This is to make processing each Pose easier for the robot. Each Pose has an X coordinate, Y coordinate, and a
 * Heading.
 * @param x X Coordinate
 * @param y Y Coordinate
 * @param heading Angle/Rotation
 */
struct Pose {
    double x;
    double y;
    double phi;

    Pose() {
        this->x = 0;
        this->y = 0;
        this->phi = 0;
    }

    Pose(double x, double y) {
        this->x = x;
        this->y = y;
        this->phi = 0;
    }

    Pose(double x, double y, double phi) {
        this->x = x;
        this->y = y;
        this->phi = phi;
    }

    Pose(const Pose& Pose) {
        this->x = Pose.x;
        this->y = Pose.y;
        this->phi = Pose.phi;
    }

    void operator=(const Pose& equal) {
        this->x = equal.x;
        this->y = equal.y;
        this->phi = equal.phi;
    }

    Pose operator+(const Pose& add) {
        return Pose(this->x + add.x, this->y + add.y);
    }

    Pose operator-(const Pose& sub) {
        return Pose(this->x - sub.x, this->y - sub.y, this->phi - sub.phi);
    }

    Pose operator*(double mult) {
        return Pose(this->x * mult, this->y * mult);
    }

    void operator+=(const Pose& add) {
        this->x = this->x + add.x;
        this->y = this->y + add.y;
    }

    void operator/=(double div) {
        this->x /= div;
        this->y /= div;
    }

    double distanceTo(const Pose& to) {
        return sqrt(pow((to.x - x), 2) + pow(to.y - y, 2));
    }
    
    //returns angle relative to y axis in degrees from -180 to 180
    double angleTo(const Pose& to) { 
        double tox = to.x - this->x;
        double toy = to.y - this->y;
        return ((atan2(tox, toy)) * (180.0 / M_PI));
    }

    double magnitude() {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    double dot(const Pose& p) {
        return (x * p.x) + (y * p.y);
    }
};