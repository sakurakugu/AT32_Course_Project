/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *home_app1;
	bool home_app1_del;
	lv_obj_t *home_app1_status_bar;
	lv_obj_t *home_app1_wifi;
	lv_obj_t *home_app1_voice_on;
	lv_obj_t *home_app1_voice_off;
	lv_obj_t *home_app1_time;
	lv_obj_t *home_app1_date;
	lv_obj_t *home_app1_home_page;
	lv_obj_t *home_app1_setting_app_icon;
	lv_obj_t *home_app1_setting_app_icon_label;
	lv_obj_t *home_app1_deepseek_app_icon;
	lv_obj_t *home_app1_deepseek_app_icon_label;
	lv_obj_t *home_app1_calculator_app_icon;
	lv_obj_t *home_app1_calculator_app_icon_label;
	lv_obj_t *home_app1_smart_home_app_icon;
	lv_obj_t *home_app1_smart_home_app_icon_label;
	lv_obj_t *home_app1_music_app_icon;
	lv_obj_t *home_app1_music_app_icon_label;
	lv_obj_t *home_app1_weather_app_icon;
	lv_obj_t *home_app1_weather_app_icon_label;
	lv_obj_t *home_app2;
	bool home_app2_del;
	lv_obj_t *home_app2_home_page;
	lv_obj_t *home_app2_imgbtn_6;
	lv_obj_t *home_app2_imgbtn_6_label;
	lv_obj_t *home_app2_imgbtn_5;
	lv_obj_t *home_app2_imgbtn_5_label;
	lv_obj_t *home_app2_imgbtn_4;
	lv_obj_t *home_app2_imgbtn_4_label;
	lv_obj_t *home_app2_imgbtn_3;
	lv_obj_t *home_app2_imgbtn_3_label;
	lv_obj_t *home_app2_imgbtn_2;
	lv_obj_t *home_app2_imgbtn_2_label;
	lv_obj_t *home_app2_imgbtn_1;
	lv_obj_t *home_app2_imgbtn_1_label;
	lv_obj_t *status_app;
	bool status_app_del;
	lv_obj_t *weather_app;
	bool weather_app_del;
	lv_obj_t *weather_app_weather_page;
	lv_obj_t *weather_app_updatetime;
	lv_obj_t *weather_app_city;
	lv_obj_t *weather_app_temperature;
	lv_obj_t *weather_app_unit;
	lv_obj_t *weather_app_weather;
	lv_obj_t *weather_app_weather_3days_div;
	lv_obj_t *weather_app_text_day3;
	lv_obj_t *weather_app_num_day3;
	lv_obj_t *weather_app_text_night2;
	lv_obj_t *weather_app_text_night3;
	lv_obj_t *weather_app_num_day1;
	lv_obj_t *weather_app_num_day2;
	lv_obj_t *weather_app_num_night3;
	lv_obj_t *weather_app_text_day2;
	lv_obj_t *weather_app_num_night2;
	lv_obj_t *weather_app_text_day1;
	lv_obj_t *weather_app_weather_names;
	lv_obj_t *weather_app_text_night1;
	lv_obj_t *weather_app_weather_times;
	lv_obj_t *weather_app_num_night1;
	lv_obj_t *weather_app_update_weather_btn;
	lv_obj_t *weather_app_update_weather_btn_label;
	lv_obj_t *music_app;
	bool music_app_del;
	lv_obj_t *music_app_music_list;
	lv_obj_t *music_app_music_play;
	lv_obj_t *music_app_img_1;
	lv_obj_t *music_app_list_1;
	lv_obj_t *music_app_list_1_item0;
	lv_obj_t *music_app_list_1_item1;
	lv_obj_t *music_app_list_1_item2;
	lv_obj_t *smart_home_app;
	bool smart_home_app_del;
	lv_obj_t *smart_home_app_cont_1;
	lv_obj_t *smart_home_app_imgbtn_6;
	lv_obj_t *smart_home_app_imgbtn_6_label;
	lv_obj_t *smart_home_app_imgbtn_5;
	lv_obj_t *smart_home_app_imgbtn_5_label;
	lv_obj_t *smart_home_app_imgbtn_4;
	lv_obj_t *smart_home_app_imgbtn_4_label;
	lv_obj_t *smart_home_app_imgbtn_3;
	lv_obj_t *smart_home_app_imgbtn_3_label;
	lv_obj_t *smart_home_app_imgbtn_2;
	lv_obj_t *smart_home_app_imgbtn_2_label;
	lv_obj_t *smart_home_app_imgbtn_1;
	lv_obj_t *smart_home_app_imgbtn_1_label;
	lv_obj_t *calculator_app;
	bool calculator_app_del;
	lv_obj_t *calculator_app_caalculator_page;
	lv_obj_t *calculator_app_btn_equal;
	lv_obj_t *calculator_app_btn_equal_label;
	lv_obj_t *calculator_app_btn_add;
	lv_obj_t *calculator_app_btn_add_label;
	lv_obj_t *calculator_app_btn_subtract;
	lv_obj_t *calculator_app_btn_subtract_label;
	lv_obj_t *calculator_app_btn_backspace;
	lv_obj_t *calculator_app_btn_backspace_label;
	lv_obj_t *calculator_app_btn_num_3;
	lv_obj_t *calculator_app_btn_num_3_label;
	lv_obj_t *calculator_app_btn_num_6;
	lv_obj_t *calculator_app_btn_num_6_label;
	lv_obj_t *calculator_app_btn_num_9;
	lv_obj_t *calculator_app_btn_num_9_label;
	lv_obj_t *calculator_app_btn_multiply;
	lv_obj_t *calculator_app_btn_multiply_label;
	lv_obj_t *calculator_app_btn_num_2;
	lv_obj_t *calculator_app_btn_num_2_label;
	lv_obj_t *calculator_app_btn_num_5;
	lv_obj_t *calculator_app_btn_num_5_label;
	lv_obj_t *calculator_app_btn_num_8;
	lv_obj_t *calculator_app_btn_num_8_label;
	lv_obj_t *calculator_app_btn_divide;
	lv_obj_t *calculator_app_btn_divide_label;
	lv_obj_t *calculator_app_btn_num_1;
	lv_obj_t *calculator_app_btn_num_1_label;
	lv_obj_t *calculator_app_btn_num_4;
	lv_obj_t *calculator_app_btn_num_4_label;
	lv_obj_t *calculator_app_btn_num_7;
	lv_obj_t *calculator_app_btn_num_7_label;
	lv_obj_t *calculator_app_btn_clear;
	lv_obj_t *calculator_app_btn_clear_label;
	lv_obj_t *calculator_app_btn_num_0;
	lv_obj_t *calculator_app_btn_num_0_label;
	lv_obj_t *calculator_app_btn_modulus;
	lv_obj_t *calculator_app_btn_modulus_label;
	lv_obj_t *calculator_app_btn_right_parenthesis;
	lv_obj_t *calculator_app_btn_right_parenthesis_label;
	lv_obj_t *calculator_app_btn_left_parenthesis;
	lv_obj_t *calculator_app_btn_left_parenthesis_label;
	lv_obj_t *calculator_app_label_1;
	lv_obj_t *deepseek_app;
	bool deepseek_app_del;
	lv_obj_t *deepseek_app_ta_1;
	lv_obj_t *deepseek_app_spangroup_1;
	lv_span_t *deepseek_app_spangroup_1_span;
	lv_obj_t *deepseek_app_spangroup_2;
	lv_span_t *deepseek_app_spangroup_2_span;
	lv_obj_t *setting_app;
	bool setting_app_del;
	lv_obj_t *setting_app_setting_page;
	lv_obj_t *setting_app_setting_page_sidebar_page;
	lv_obj_t *setting_app_setting_page_subpage_1;
	lv_obj_t *setting_app_setting_page_cont_1;
	lv_obj_t *setting_app_setting_page_label_1;
	lv_obj_t *setting_app_setting_page_subpage_2;
	lv_obj_t *setting_app_setting_page_cont_2;
	lv_obj_t *setting_app_setting_page_label_2;
	lv_obj_t *setting_app_setting_page_subpage_3;
	lv_obj_t *setting_app_setting_page_cont_3;
	lv_obj_t *setting_app_setting_page_label_3;
	lv_obj_t *setting_app_setting_page_subpage_4;
	lv_obj_t *setting_app_setting_page_cont_4;
	lv_obj_t *setting_app_setting_page_label_4;
	lv_obj_t *setting_app_placeholder_1;
	lv_obj_t *setting_app_wifi_name_text;
	lv_obj_t *setting_app_wifi_name_input;
	lv_obj_t *setting_app_wifi_password_text;
	lv_obj_t *setting_app_wifi_password_input;
	lv_obj_t *setting_app_placeholder_2;
	lv_obj_t *setting_app_wifi_link_btn;
	lv_obj_t *setting_app_wifi_link_btn_label;
	lv_obj_t *setting_app_light_text;
	lv_obj_t *setting_app_light_slider;
	lv_obj_t *setting_app_sound_text;
	lv_obj_t *setting_app_sound_slider;
	lv_obj_t *setting_app_sync_net_time_text;
	lv_obj_t *setting_app_sync_net_time_sw;
	lv_obj_t *electronic_organ_app;
	bool electronic_organ_app_del;
	lv_obj_t *game1;
	bool game1_del;
	lv_obj_t *game2;
	bool game2_del;
	lv_obj_t *game3;
	bool game3_del;
	lv_obj_t *game4;
	bool game4_del;
	lv_obj_t *game5;
	bool game5_del;
	lv_obj_t *g_kb_top_layer;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_home_app1(lv_ui *ui);
void setup_scr_home_app2(lv_ui *ui);
void setup_scr_status_app(lv_ui *ui);
void setup_scr_weather_app(lv_ui *ui);
void setup_scr_music_app(lv_ui *ui);
void setup_scr_smart_home_app(lv_ui *ui);
void setup_scr_calculator_app(lv_ui *ui);
void setup_scr_deepseek_app(lv_ui *ui);
void setup_scr_setting_app(lv_ui *ui);
void setup_scr_electronic_organ_app(lv_ui *ui);
void setup_scr_game1(lv_ui *ui);
void setup_scr_game2(lv_ui *ui);
void setup_scr_game3(lv_ui *ui);
void setup_scr_game4(lv_ui *ui);
void setup_scr_game5(lv_ui *ui);
LV_IMG_DECLARE(_wifi_alpha_16x16);
LV_IMG_DECLARE(_voice_on_alpha_16x16);
LV_IMG_DECLARE(_voice_off_alpha_16x16);
LV_IMG_DECLARE(_setting_app_alpha_80x80);
LV_IMG_DECLARE(_deepseek_alpha_80x80);
LV_IMG_DECLARE(_calculator_app_alpha_80x80);
LV_IMG_DECLARE(_smart_home_app_alpha_80x80);
LV_IMG_DECLARE(_music_app_alpha_80x80);
LV_IMG_DECLARE(_weather_app_alpha_80x80);
LV_IMG_DECLARE(_setting_app_alpha_80x80);
LV_IMG_DECLARE(_deepseek_alpha_80x80);
LV_IMG_DECLARE(_calculator_app_alpha_80x80);
LV_IMG_DECLARE(_smart_home_app_alpha_80x80);
LV_IMG_DECLARE(_music_app_alpha_80x80);
LV_IMG_DECLARE(_weather_app_alpha_80x80);

LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_14)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_montserratMedium_64)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_12)
LV_FONT_DECLARE(lv_font_montserratMedium_18)


#ifdef __cplusplus
}
#endif
#endif
