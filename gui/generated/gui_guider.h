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
	lv_obj_t *home_app2_drawing_board_icon;
	lv_obj_t *home_app2_drawing_board_icon_label;
	lv_obj_t *home_app2_electronic_organ_icon;
	lv_obj_t *home_app2_electronic_organ_icon_label;
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
	lv_obj_t *music_app_music_page;
	lv_obj_t *music_app_music_list;
	lv_obj_t *music_app_music_list_item0;
	lv_obj_t *music_app_music_list_item1;
	lv_obj_t *music_app_music_list_item2;
	lv_obj_t *music_app_music_recode;
	lv_obj_t *music_app_music_stylus;
	lv_obj_t *music_app_player_div;
	lv_obj_t *music_app_imgbtn_4;
	lv_obj_t *music_app_imgbtn_4_label;
	lv_obj_t *music_app_imgbtn_3;
	lv_obj_t *music_app_imgbtn_3_label;
	lv_obj_t *music_app_imgbtn_2;
	lv_obj_t *music_app_imgbtn_2_label;
	lv_obj_t *smart_home_app;
	bool smart_home_app_del;
	lv_obj_t *smart_home_app_IoT_page;
	lv_obj_t *smart_home_app_IoT_8key;
	lv_obj_t *smart_home_app_IoT_8key_label;
	lv_obj_t *smart_home_app_IoT_MPU6050;
	lv_obj_t *smart_home_app_IoT_MPU6050_label;
	lv_obj_t *smart_home_app_IoT_ADC;
	lv_obj_t *smart_home_app_IoT_ADC_label;
	lv_obj_t *smart_home_app_IoT_lm75;
	lv_obj_t *smart_home_app_IoT_lm75_label;
	lv_obj_t *smart_home_app_IoT_led_green;
	lv_obj_t *smart_home_app_IoT_led_green_label;
	lv_obj_t *smart_home_app_IoT_color_led;
	lv_obj_t *smart_home_app_IoT_color_led_label;
	lv_obj_t *smart_home_app_color_led_page;
	lv_obj_t *smart_home_app_color_led_cpicker;
	lv_obj_t *smart_home_app_color_led_name;
	lv_obj_t *smart_home_app_color_led_sw_div;
	lv_obj_t *smart_home_app_color_led_sw;
	lv_obj_t *smart_home_app_color_led_sw_text;
	lv_obj_t *smart_home_app_color_led_light_div;
	lv_obj_t *smart_home_app_color_led_light_text;
	lv_obj_t *smart_home_app_color_led_light_div_slider;
	lv_obj_t *smart_home_app_btn_return1;
	lv_obj_t *smart_home_app_btn_return1_label;
	lv_obj_t *smart_home_app_led_green_page;
	lv_obj_t *smart_home_app_led_green_sw_div;
	lv_obj_t *smart_home_app_led_green_sw;
	lv_obj_t *smart_home_app_led_green_sw_text;
	lv_obj_t *smart_home_app_led_green_name;
	lv_obj_t *smart_home_app_btn_return2;
	lv_obj_t *smart_home_app_btn_return2_label;
	lv_obj_t *smart_home_app_lm75_page;
	lv_obj_t *smart_home_app_temperature_div;
	lv_obj_t *smart_home_app_temperature_textt;
	lv_obj_t *smart_home_app_temperature_num;
	lv_obj_t *smart_home_app_lm75_name;
	lv_obj_t *smart_home_app_btn_return3;
	lv_obj_t *smart_home_app_btn_return3_label;
	lv_obj_t *smart_home_app_ADC_page;
	lv_obj_t *smart_home_app_ADC_name;
	lv_obj_t *smart_home_app_ADC_div;
	lv_obj_t *smart_home_app_ADC_text;
	lv_obj_t *smart_home_app_ADC_num;
	lv_obj_t *smart_home_app_btn_reutrn4;
	lv_obj_t *smart_home_app_btn_reutrn4_label;
	lv_obj_t *smart_home_app_MPU6050_page;
	lv_obj_t *smart_home_app_MPU6050_name;
	lv_obj_t *smart_home_app_attitude_div;
	lv_obj_t *smart_home_app_attitude_text;
	lv_obj_t *smart_home_app_attitude_text_x;
	lv_obj_t *smart_home_app_attitude_text_y;
	lv_obj_t *smart_home_app_attitude_text_z;
	lv_obj_t *smart_home_app_attitude_num_x;
	lv_obj_t *smart_home_app_attitude_num_y;
	lv_obj_t *smart_home_app_attitude_num_z;
	lv_obj_t *smart_home_app_accelerated_speed_div;
	lv_obj_t *smart_home_app_accelerated_speed_text;
	lv_obj_t *smart_home_app_accelerated_speed_text_x;
	lv_obj_t *smart_home_app_accelerated_speed_text_y;
	lv_obj_t *smart_home_app_accelerated_speed_text_z;
	lv_obj_t *smart_home_app_accelerated_speed_num_x;
	lv_obj_t *smart_home_app_accelerated_speed_num_y;
	lv_obj_t *smart_home_app_accelerated_speed_num_z;
	lv_obj_t *smart_home_app_mpu6050_temp;
	lv_obj_t *smart_home_app_mpu6050_teemp_text;
	lv_obj_t *smart_home_app_mpu6050_teemp_num;
	lv_obj_t *smart_home_app_btn_return5;
	lv_obj_t *smart_home_app_btn_return5_label;
	lv_obj_t *smart_home_app_key_page;
	lv_obj_t *smart_home_app_key_name;
	lv_obj_t *smart_home_app_btn_7;
	lv_obj_t *smart_home_app_btn_7_label;
	lv_obj_t *smart_home_app_btn_5;
	lv_obj_t *smart_home_app_btn_5_label;
	lv_obj_t *smart_home_app_btn_8;
	lv_obj_t *smart_home_app_btn_8_label;
	lv_obj_t *smart_home_app_btn_6;
	lv_obj_t *smart_home_app_btn_6_label;
	lv_obj_t *smart_home_app_btn_1;
	lv_obj_t *smart_home_app_btn_1_label;
	lv_obj_t *smart_home_app_btn_4;
	lv_obj_t *smart_home_app_btn_4_label;
	lv_obj_t *smart_home_app_btn_2;
	lv_obj_t *smart_home_app_btn_2_label;
	lv_obj_t *smart_home_app_btn_3;
	lv_obj_t *smart_home_app_btn_3_label;
	lv_obj_t *smart_home_app_btn_return6;
	lv_obj_t *smart_home_app_btn_return6_label;
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
	lv_obj_t *deepseek_app_input_div;
	lv_obj_t *deepseek_app_send_btn;
	lv_obj_t *deepseek_app_send_btn_label;
	lv_obj_t *deepseek_app_input_box;
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
	lv_obj_t *setting_app_sync_net_time_text;
	lv_obj_t *setting_app_sync_net_time_sw;
	lv_obj_t *electronic_organ_app;
	bool electronic_organ_app_del;
	lv_obj_t *electronic_organ_app_e_organ_btnm;
	lv_obj_t *drawing_board_app;
	bool drawing_board_app_del;
	lv_obj_t *drawing_board_app_tools_panel;
	lv_obj_t *drawing_board_app_colorwheel;
	lv_obj_t *drawing_board_app_width_slider;
	lv_obj_t *drawing_board_app_btn_clear;
	lv_obj_t *drawing_board_app_btn_clear_label;
	lv_obj_t *drawing_board_app_btn_nav_back;
	lv_obj_t *drawing_board_app_btn_nav_back_label;
	lv_obj_t *drawing_board_app_canvas_container;
	lv_obj_t *drawing_board_app_dialog_box;
	lv_obj_t *game_minecraft;
	bool game_minecraft_del;
	lv_obj_t *game_minecraft_back_btn;
	lv_obj_t *game_minecraft_back_btn_label;
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
void setup_scr_drawing_board_app(lv_ui *ui);
void setup_scr_game_minecraft(lv_ui *ui);
void setup_scr_game3(lv_ui *ui);
void setup_scr_game4(lv_ui *ui);
void setup_scr_game5(lv_ui *ui);
LV_IMG_DECLARE(_wifi_alpha_16x16);
LV_IMG_DECLARE(_voice_on_alpha_16x16);
LV_IMG_DECLARE(_voice_off_alpha_16x16);
LV_IMG_DECLARE(_setting_app_alpha_80x80);
LV_IMG_DECLARE(_calculator_app_alpha_80x80);
LV_IMG_DECLARE(_smart_home_app_alpha_80x80);
LV_IMG_DECLARE(_music_app_alpha_80x80);
LV_IMG_DECLARE(_weather_app_alpha_80x80);
LV_IMG_DECLARE(_drawing_app_alpha_80x80);
LV_IMG_DECLARE(_electronic_organ_app_alpha_80x80);
LV_IMG_DECLARE(_music_record_alpha_160x160);
LV_IMG_DECLARE(_music_stylus_alpha_26x126);
LV_IMG_DECLARE(_music_player_alpha_16x16);
LV_IMG_DECLARE(_music_pause_alpha_16x16);
LV_IMG_DECLARE(_music_prev_song_alpha_16x16);
LV_IMG_DECLARE(_music_next_song_alpha_16x16);
LV_IMG_DECLARE(_color_led_alpha_80x80);
LV_IMG_DECLARE(_color_led_alpha_80x80);
LV_IMG_DECLARE(_color_led_alpha_80x80);
LV_IMG_DECLARE(_color_led_alpha_80x80);
LV_IMG_DECLARE(_color_led_alpha_80x80);
LV_IMG_DECLARE(_color_led_alpha_80x80);

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
