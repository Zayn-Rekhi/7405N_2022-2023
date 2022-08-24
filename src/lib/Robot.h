#pragma once

#include "main.h"
#include "drive/Drive.h"
#include "subsystems/Subsystems.h"

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

        // Subsystems
        static FlyWheel flywheel;

        static Threading threading;
        
        static void driver(void *ptr);
        static void display(void *ptr);
        static void odom(void *ptr);
};

