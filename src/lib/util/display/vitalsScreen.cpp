#include "vitalsScreen.h"
#include "../Logging.h"
#include "main.h"

lv_style_t VitalsScreen::tIndic;  // indicates current tab
lv_style_t VitalsScreen::tBtn;    // buttons
lv_style_t VitalsScreen::msgInfo;
lv_style_t VitalsScreen::msgWarn;
lv_style_t VitalsScreen::msgError;
lv_style_t VitalsScreen::componentStyle;
lv_style_t VitalsScreen::ringStyle;
extern lv_font_t lv_font_dejavu_40;
extern lv_style_t bRel;
extern lv_style_t bPr;
extern lv_style_t bTGL_Rel;
extern lv_style_t bTGL_Pr;

// crappy fix
static bool cleared = false;

/**
 * @brief Button callback to clear console page
 *
 * @param btn
 * @return lv_res_t
 */
static lv_res_t clearBtnClicKAction(lv_obj_t* btn) {
    lv_obj_t* parent = lv_obj_get_parent(btn);

    lv_obj_set_parent(btn, lv_scr_act());
    lv_obj_clean(parent);
    lv_obj_set_parent(btn, parent);

    cleared = true;
    return LV_RES_OK;
}

VitalsScreen::VitalsScreen() {
    tabview = lv_tabview_create(screen, NULL);
    generalPage = lv_tabview_add_tab(tabview, "General");
    sensorsPage = lv_tabview_add_tab(tabview, "Sensors");
    consolePage = lv_tabview_add_tab(tabview, "Console");
    importantPage = lv_tabview_add_tab(tabview, "Important");

    LV_IMG_DECLARE(funny);
    importantIMG = lv_img_create(importantPage, NULL);
    lv_img_set_src(importantIMG, &funny);

    lv_tabview_set_anim_time(tabview, 75);  // unsure what unit it is in - looks nice though

    // tabview styling
    lv_style_copy(&tIndic, &lv_style_plain_color);
    lv_style_copy(&tBtn, lv_tabview_get_style(tabview, LV_TABVIEW_STYLE_BTN_REL));

    tIndic.body.padding.inner = 5;
    tBtn.body.padding.ver = 5;

    lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_INDIC, &tIndic);
    lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BTN_REL, &tBtn);

    // message styling
    lv_style_copy(&msgInfo, &lv_style_plain);
    msgInfo.text.font = &lv_font_dejavu_20;  // if this is too small do 20
    msgInfo.text.color = LV_COLOR_WHITE;

    lv_style_copy(&msgWarn, &msgInfo);
    msgWarn.text.color = LV_COLOR_ORANGE;

    lv_style_copy(&msgError, &msgWarn);
    msgError.text.color = LV_COLOR_RED;

    // sensor component styling

    lv_style_copy(&componentStyle, &lv_style_pretty_color);
    componentStyle.body.empty = true;
    componentStyle.body.border.color = LV_COLOR_WHITE;
    componentStyle.body.border.width = 2;
    componentStyle.body.radius = 3;
    componentStyle.body.padding.inner = 2;

    // ring count styling
    lv_style_copy(&ringStyle, &lv_style_plain);
    ringStyle.text.color = LV_COLOR_GREEN;
    ringStyle.text.font = &lv_font_dejavu_40;

    // general page
    ringCount = lv_label_create(generalPage, NULL);
    lv_label_set_text(ringCount, "Indexer:\n0");
    lv_label_set_align(ringCount, LV_LABEL_ALIGN_CENTER);
    // change color of ringStyle to change color of the text
    lv_obj_set_style(ringCount, &ringStyle);

    motor1General = lv_label_create(generalPage, ringCount);
    lv_label_set_text(motor1General, "Motor 1\n");
    motor2General = lv_label_create(generalPage, ringCount);
    lv_label_set_text(motor2General, "Motor 2\n");
    motor3General = lv_label_create(generalPage, ringCount);
    lv_label_set_text(motor3General, "Motor 3\n");
    motor4General = lv_label_create(generalPage, ringCount);
    lv_label_set_text(motor4General, "Motor 4\n");

    lv_obj_align(ringCount, generalPage, LV_ALIGN_CENTER, 0, 0);  // cant get it to move on y axis so wherever it goes
    lv_obj_align(motor1General, generalPage, LV_ALIGN_IN_TOP_LEFT, 13, 10);
    lv_obj_align(motor2General, generalPage, LV_ALIGN_IN_TOP_RIGHT, -13, 10);
    lv_obj_align(motor3General, generalPage, LV_ALIGN_IN_BOTTOM_LEFT, 13, 0);
    lv_obj_align(motor4General, generalPage, LV_ALIGN_IN_BOTTOM_RIGHT, -13, 0);

    // sensor page
    motor1Info = createComponent("Motor 1");
    lv_obj_align(motor1Info.container, sensorsPage, LV_ALIGN_IN_TOP_LEFT, 10, 0);
    motor2Info = createComponent("Motor 2");
    lv_obj_align(motor2Info.container, motor1Info.container, LV_ALIGN_IN_TOP_LEFT, lv_obj_get_width(motor1Info.container) + 25,
                 0);
    motor3Info = createComponent("Motor 3");
    lv_obj_align(motor3Info.container, motor1Info.container, LV_ALIGN_IN_TOP_LEFT, 0,
                 lv_obj_get_height(motor1Info.container) + 8);
    motor4Info = createComponent("Motor 4");
    lv_obj_align(motor4Info.container, motor3Info.container, LV_ALIGN_IN_TOP_LEFT, lv_obj_get_width(motor3Info.container) + 25,
                 0);

    // console page
    clearBtn = lv_btn_create(consolePage, NULL);
    lv_btn_set_action(clearBtn, LV_BTN_ACTION_CLICK, clearBtnClicKAction);
    lv_btn_set_style(clearBtn, LV_BTN_STYLE_REL, &bRel);
    lv_btn_set_style(clearBtn, LV_BTN_STYLE_REL, &bPr);
    lv_btn_set_style(clearBtn, LV_BTN_STYLE_REL, &bTGL_Rel);
    lv_btn_set_style(clearBtn, LV_BTN_STYLE_REL, &bTGL_Pr);
    lv_btn_set_fit(clearBtn, false, false);
    lv_obj_set_height(clearBtn, 25);
    lv_obj_set_width(clearBtn, 50);

    clearBtnTxt = lv_label_create(clearBtn, NULL);
    lv_label_set_text(clearBtnTxt, "Clear");
    lv_obj_set_style(clearBtnTxt, &msgInfo);

    lv_obj_align(clearBtn, consolePage, LV_ALIGN_IN_TOP_RIGHT, -10, 0);
}

InfoComponent VitalsScreen::createComponent(const char* name) {
    InfoComponent component;

    component.container = lv_cont_create(sensorsPage, NULL);
    lv_cont_set_fit(component.container, false, false);  // could cause issues when aligning
    lv_cont_set_layout(component.container, LV_LAYOUT_CENTER);
    lv_obj_set_style(component.container, &componentStyle);
    lv_obj_set_width(component.container, 200);
    lv_obj_set_height(component.container, 100);

    component.name = lv_label_create(component.container, NULL);
    lv_label_set_text(component.name, name);

    component.info = lv_label_create(component.container, NULL);
    lv_label_set_align(component.info, LV_LABEL_ALIGN_CENTER);
    // lv_label_set_array_text(component.info, component.text, sizeof(component.text));
    lv_obj_set_style(component.info, &msgInfo);

    return component;
}

lv_obj_t* VitalsScreen::createMsg(LogMessage msg) {
    static lv_obj_t* prev = nullptr;  // used for aligning messages
    lv_obj_t* message = lv_label_create(consolePage, NULL);

    lv_label_set_long_mode(message, LV_LABEL_LONG_BREAK);
    lv_obj_set_width(message, lv_page_get_scrl_width(consolePage));
    lv_label_set_text(message, msg.msg.c_str());

    switch (msg.type) {
        case LogType::INFO:
            lv_obj_set_style(message, &msgInfo);
            break;
        case LogType::WARN:
            lv_obj_set_style(message, &msgWarn);
            break;
        case LogType::ERROR:
            lv_obj_set_style(message, &msgError);
            break;
        default:
            lv_obj_set_style(message, &msgInfo);
            break;
    }

    // also checks whether or not there is at least one message on page
    if (prev != nullptr && !cleared) {
        lv_obj_align(message, prev, LV_ALIGN_IN_TOP_LEFT, 0, lv_obj_get_height(prev));
    }
    cleared = false;
    prev = message;

    return message;
}

void VitalsScreen::update() {
    // gets information to update the screen with
    Logger& instance = Logger::instance();
    if (!instance.displayMutex.take(5))
        return;

    while (!instance.displayQueue.empty()) {
        createMsg(instance.displayQueue.front());
        instance.displayQueue.pop();
    }

    instance.displayMutex.give();

    double FL_TEMP = pros::c::motor_get_temperature(3);
    double FR_TEMP = pros::c::motor_get_temperature(5);
    double BL_TEMP = pros::c::motor_get_temperature(4);
    double BR_TEMP = pros::c::motor_get_temperature(2);

    double FL_TORQUE = pros::c::motor_get_torque(3);
    double FR_TORQUE = pros::c::motor_get_torque(5);
    double BL_TORQUE = pros::c::motor_get_torque(4);
    double BR_TORQUE = pros::c::motor_get_torque(2);

    double FL_RPM = pros::c::motor_get_actual_velocity(3);
    double FR_RPM = pros::c::motor_get_actual_velocity(5);
    double BL_RPM = pros::c::motor_get_actual_velocity(4);
    double BR_RPM = pros::c::motor_get_actual_velocity(2);

    // TODO:
    // test in person whether or not we have to do lv_label_set_array_text
    // cause idk how lvgl works under the hood
    snprintf(motor1Info.text, sizeof(motor1Info.text), "Temp:%f\nRPM:%f\nTrq:%f\0", FL_TEMP, FL_RPM, FL_TORQUE);
    snprintf(motor2Info.text, sizeof(motor2Info.text), "Temp:%f\nRPM:%f\nTrq:%f\0", FR_TEMP, FR_RPM, FR_TORQUE);
    snprintf(motor3Info.text, sizeof(motor3Info.text), "Temp:%f\nRPM:%f\nTrq:%f\0", BL_TEMP, BL_RPM, BL_TORQUE);
    snprintf(motor4Info.text, sizeof(motor4Info.text), "Temp:%f\nRPM:%f\nTrq:%f\0", BR_TEMP, BR_RPM, BR_TORQUE);

    lv_label_set_array_text(motor1Info.info, motor1Info.text, sizeof(motor1Info.text));
    lv_label_set_array_text(motor2Info.info, motor2Info.text, sizeof(motor2Info.text));
    lv_label_set_array_text(motor3Info.info, motor3Info.text, sizeof(motor3Info.text));
    lv_label_set_array_text(motor4Info.info, motor4Info.text, sizeof(motor4Info.text));
}