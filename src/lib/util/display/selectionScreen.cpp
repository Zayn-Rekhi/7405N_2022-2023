#include "selectionScreen.h"
#include "lib/Robot.h"

// yay globals
lv_style_t bRel;
lv_style_t bPr;
lv_style_t bTGL_Rel;
lv_style_t bTGL_Pr;

static lv_res_t selectBtnAction(lv_obj_t* btn) {
    uint32_t num = lv_obj_get_free_num(btn);

    // figure out which corresponds to which
    Robot::teamSelection = (TeamSelection)num;

    return LV_RES_OK;
}

SelectionScreen::SelectionScreen() {
    lv_style_copy(&bRel, &lv_style_btn_rel);
    lv_style_copy(&bPr, &lv_style_btn_pr);
    lv_style_copy(&bTGL_Rel, &lv_style_btn_tgl_rel);
    lv_style_copy(&bTGL_Pr, &lv_style_btn_tgl_pr);

    bRel.body.opa = LV_OPA_TRANSP;
    bRel.body.radius = 0;
    bPr.body.opa = LV_OPA_TRANSP;
    bPr.body.radius = 0;
    bTGL_Rel.body.opa = LV_OPA_TRANSP;
    bTGL_Rel.body.radius = 0;
    bTGL_Pr.body.radius = 0;
    bTGL_Pr.body.opa = LV_OPA_TRANSP;
    
    left = lv_btn_create(screen, NULL);
    lv_btn_set_style(left, LV_BTN_STYLE_REL, &bTGL_Pr);
    lv_obj_set_size(left, 130, 100);
    lv_obj_set_pos(left, percentX(5), percentY(4));

    right = lv_btn_create(screen, left);
    lv_obj_set_pos(right, percentX(44), percentY(4));

    right_high = lv_btn_create(screen, left);
    lv_obj_set_pos(right_high, percentX(83), percentY(4));

    right_double = lv_btn_create(screen, left);
    lv_obj_set_pos(right_double, percentX(44), percentY(63));

    lv_obj_set_free_num(left, (uint32_t)TeamSelection::LEFT);
    lv_obj_set_free_num(right, (uint32_t)TeamSelection::RIGHT);
    lv_obj_set_free_num(right_high, (uint32_t)TeamSelection::RIGHT_HIGH);
    lv_obj_set_free_num(right_double, (uint32_t)TeamSelection::RIGHT_DOUBLE);

    lv_btn_set_action(left, LV_BTN_ACTION_CLICK, selectBtnAction);
    lv_btn_set_action(right, LV_BTN_ACTION_CLICK, selectBtnAction);
    lv_btn_set_action(right_high, LV_BTN_ACTION_CLICK, selectBtnAction);
    lv_btn_set_action(right_double, LV_BTN_ACTION_CLICK, selectBtnAction);

    left_label = lv_label_create(left, NULL);
    lv_label_set_text(left_label, "Left Side");

    right_label = lv_label_create(right, NULL);
    lv_label_set_text(right_label, "Right Side");

    right_high_label = lv_label_create(right_high, NULL);
    lv_label_set_text(right_high_label, "Right High");

    right_double_label = lv_label_create(right_double, NULL);
    lv_label_set_text(right_double_label, "Right Double");
}

void SelectionScreen::getSelection() {
    while (Robot::teamSelection == TeamSelection::UNKNOWN) {
        pros::delay(100);
    }
}