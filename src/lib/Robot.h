#pragma once

#include "main.h"
#include "drive/Drive.h"

// Util Imports
#include "util/Threading.h"
#include "util/Util.h"
// Other
#include <map>
#include <functional>
#include <string>

class Robot {
    public:
        static pros::Controller master;

        // Motors
        static pros::Motor FL;
        static pros::Motor BL;
        static pros::Motor FR;
        static pros::Motor BR;

        // Intake
        static pros::Motor INT1;
        static pros::Motor INT2;

        // Flywheel
        static pros::Motor FLY1;
        static pros::Motor FLY2;


        // Sensors
        static pros::Rotation LE;
        static pros::Rotation RE;
        static pros::Rotation BE;
        static pros::Imu IMU;

        // Drive
        static Drive drive;
        static Odometry odometry;
        static PID power;
        static PID strafe;
        static PID turn;

        static Threading threading;
        
        static void driver(void *ptr);
        static void display(void *ptr);
        static void odom(void *ptr);
};

