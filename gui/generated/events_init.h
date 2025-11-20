/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

void events_init(lv_ui *ui);

void events_init_home_app1(lv_ui *ui);
void events_init_home_app2(lv_ui *ui);
void events_init_weather_app(lv_ui *ui);
void events_init_music_app(lv_ui *ui);
void events_init_smart_home_app(lv_ui *ui);
void events_init_clock_app(lv_ui *ui);
void events_init_calculator_app(lv_ui *ui);
void events_init_setting_app(lv_ui *ui);
void events_init_electronic_organ_app(lv_ui *ui);
void events_init_drawing_board_app(lv_ui *ui);
void events_init_minecraft_app(lv_ui *ui);
void events_init_link_game_app(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
