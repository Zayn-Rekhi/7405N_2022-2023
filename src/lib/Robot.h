#pragma once

#include "main.h"
#include "drive/Drive.h"
#include "subsystems/Subsystems.h"

// Util Imports
#include "util/Threading.h"

// Other
#include <map>
#include <functional>
#include <string>

class Robot {
    public:
        static pros::Controller Master;

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
        static Odometry odometry;
        static PID power;
        static PID strafe;
        static PID turn;

        static void driver(void *ptr);
        static void display(void *ptr);
};

