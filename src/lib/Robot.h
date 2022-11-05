#pragma once

#include "main.h"

// Drive Imports
#include "drive/Drive.h"

// Subsystem Imports
#include "subsystems/Flywheel.h"

// Util Imports
#include "util/Threading.h"
#include "util/Util.h"
#include "util/selectionScreen.h"
#include "util/Display.h"
#include "util/selectionScreen.h"

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

        // Flywheel Piston
        static pros::ADIDigitalOut FLYPIST;

        // Flywheel Piston
        static pros::ADIDigitalOut EXP1;

        // Drive
        static Drive drive;
        static Odometry odometry;
        static PID power;
        static PID turn;

        // Subsystems
        static FlyWheel flywheel;
        static TBH fly_controller;

        // Utility
        static Threading threading;
        static TeamSelection teamSelection;


        static void driver_thread(void *ptr);
        static void display_thread(void *ptr);
        static void controller_thread(void *ptr);
        static void odom_thread(void *ptr);
        static void flywheel_thread(void *ptr);
};

