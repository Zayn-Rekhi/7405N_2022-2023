#include "main.h"
#include "lib/Robot.h"

void initialize() {
//


    Robot::EXP1.set_value(true);

    Robot::FLYPIST.set_value(true);


    pros::delay(250);
//    Display display;
//    display.addScreen("selection", new SelectionScreen());
//    SelectionScreen* screen = static_cast<SelectionScreen*>(display.getScreen("selection"));
//    Robot::teamSelection = TeamSelection::UNKNOWN;
//    display.show("selection", true, 100);
//    screen->getSelection();
    pros::lcd::initialize();
    pros::delay(250);

    pros::delay(1000);
    Robot::IMU.reset();
    pros::delay(1000);

    Robot::LE.set_data_rate(5);
    Robot::RE.set_data_rate(5);
    Robot::BE.set_data_rate(5);

    Robot::LE.reset_position();
    Robot::RE.reset_position();
    Robot::BE.reset_position();

    Robot::LE.reverse();
    Robot::BE.reverse();


    pros::delay(250);
}