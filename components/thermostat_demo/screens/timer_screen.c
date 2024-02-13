#include "screens.h"
#include "widgets.h"
#include <stdio.h>

extern thermostat_settings_t settings;
extern lv_group_t * g;
static screens_callbacks_t cbs;
static void go_back_cb(lv_event_t *);

LV_FONT_DECLARE(roboto_regular_100);
LV_FONT_DECLARE(roboto_regular_50);

lv_obj_t * timer_screen_create(screens_callbacks_t screens_callbacks){
    cbs = screens_callbacks;
    
    lv_obj_t * main = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(main, lv_color_hex(COLOR_PALETTE_ONE),LV_PART_MAIN);

    lv_obj_t * central_panel = lv_obj_create(main);
    lv_obj_center(central_panel);
    lv_obj_set_scrollbar_mode(central_panel,LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_size(central_panel, CENTRAL_PANEL_RADIUS_PX,CENTRAL_PANEL_RADIUS_PX);
    lv_obj_set_style_radius(central_panel,LV_RADIUS_CIRCLE,0);
    lv_obj_set_style_bg_color(central_panel, lv_color_hex(COLOR_PALETTE_TWO),LV_PART_MAIN);
    lv_obj_set_style_border_side(central_panel,0,0);

    lv_obj_t * time_label = lv_label_create(central_panel); 
    lv_obj_align(time_label,LV_ALIGN_TOP_MID,0,80);
    lv_label_set_text(time_label,"12:05");
    lv_obj_set_style_text_font(time_label,&roboto_regular_100,0);
    lv_obj_set_style_text_color(time_label,lv_color_hex(COLOR_PALETTE_FOUR),0);

    lv_obj_t * temperature_label = lv_label_create(central_panel);
    lv_obj_align(temperature_label,LV_ALIGN_BOTTOM_MID,0,-60);
    lv_label_set_text_fmt(temperature_label,"%d °C",settings.measured_temperature_celsius);
    lv_obj_set_style_text_font(temperature_label,&roboto_regular_50,0);
    lv_obj_set_style_text_color(temperature_label,lv_color_hex(COLOR_PALETTE_THREE),0);

    lv_obj_t * back_button = create_transparent_button(main);
    lv_obj_add_event_cb(back_button,go_back_cb,LV_EVENT_ALL,NULL);
    lv_group_add_obj(g,back_button);
    

    return main;
}


static void go_back_cb(lv_event_t * e){
    printf("Timer: event: %d\n", e->code);
    if(e->code==LV_EVENT_LONG_PRESSED||e->code==LV_EVENT_LONG_PRESSED_REPEAT){
        cbs.menu_screen_cb(NULL);
    }
}