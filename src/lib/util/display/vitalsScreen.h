#pragma once
#include "display.h"
#include "../Logging.h"
#include <vector>

struct InfoComponent {
    lv_obj_t* container;
    lv_obj_t* name;
    lv_obj_t* info;
    char text[30];

    InfoComponent() : container(nullptr), name(nullptr), info(nullptr), text{'T', 'e', 'm', 'p', ':', '0', '\n', 'R', 'P', 'M', ':', '0', '\n', 'T', 'o', 'r', 'q', 'u', 'e', ':', '0'} {}
};

class VitalsScreen : public Screen {
   private:
    static lv_style_t tIndic;  // indicates current tab
    static lv_style_t tBtn;    // tabview buttons
    static lv_style_t msgInfo;
    static lv_style_t msgWarn;
    static lv_style_t msgError;
    static lv_style_t componentStyle;  // for SensorComponenet
    static lv_style_t ringStyle;

    lv_obj_t* tabview;
    lv_obj_t* generalPage;
    lv_obj_t* sensorsPage;
    lv_obj_t* consolePage;
    lv_obj_t* importantPage;
    lv_obj_t* importantIMG;

    lv_obj_t* ringCount;
    /**
     * @brief Labels for the general page on motor temps.
     *
     */
    lv_obj_t* motor1General;
    lv_obj_t* motor2General;
    lv_obj_t* motor3General;
    lv_obj_t* motor4General;

    lv_obj_t* clearBtn;
    lv_obj_t* clearBtnTxt;

    InfoComponent motor1Info;
    InfoComponent motor2Info;
    InfoComponent motor3Info;
    InfoComponent motor4Info;

    InfoComponent createComponent(const char* name);
    lv_obj_t* createMsg(LogMessage msg);

   public:
    VitalsScreen();

    virtual void update();
};