//
// Created by zayn on 8/4/21.
//

#pragma once
#ifndef INC_7405K_2021_2022_ROBOT_H
#define INC_7405K_2021_2022_ROBOT_H


#include "main.h"

// Drive Imports
#include "drive/Odometry.h"

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
    static pros::Imu IMU;

    static Odometry odometry;
    static void startOdometry(void *ptr);

    static Threading threading;
    static void startThreading();

    static void driver(void *ptr);
    static void display(void *ptr);
};

#endif  // INC_7405K_2021_2022_ROBOT_H
