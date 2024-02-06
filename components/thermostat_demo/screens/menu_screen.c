#include "screens.h"
#include "widgets.h"
#include <stdio.h>

extern lv_group_t * g; 
extern lv_indev_t * knob_indev;

LV_IMG_DECLARE(main_menu_thermometer);
LV_IMG_DECLARE(main_menu_air_quality);
LV_IMG_DECLARE(main_menu_timer);

void button_thermometer_cb(lv_event_t * e);
void button_air_quality_cb(lv_event_t * e);
void button_timer_cb(lv_event_t * e);

static screens_callbacks_t cbs;

lv_obj_t * menu_screen_create(screens_callbacks_t screens_callback){
    cbs = screens_callback;
    //lv_group_set_default(g);

    lv_obj_t * main = lv_obj_create(NULL);
    
    lv_obj_t * central_panel = lv_obj_create(main);
    //lv_obj_set_style_bg_color(central_panel, lv_color_hex(0x00CAFE),0);
    lv_obj_set_style_radius(central_panel,LV_RADIUS_CIRCLE,0);
    lv_obj_set_style_size(central_panel,CENTRAL_PANEL_RADIUS_PX,0);
    lv_obj_set_scrollbar_mode(central_panel,LV_SCROLLBAR_MODE_OFF);
    lv_obj_t * background_image = lv_img_create(central_panel);
    lv_img_set_src(background_image, &main_menu_thermometer);
    lv_obj_center(central_panel);
    lv_obj_center(background_image);

    // Transparent buttons
    lv_obj_t * button_thermometer = create_transparent_button(central_panel);
    lv_obj_add_event_cb(button_thermometer,button_thermometer_cb,LV_EVENT_ALL, (void*)background_image );
    lv_group_add_obj(g,button_thermometer);
    lv_obj_t * button_air_quality = create_transparent_button(central_panel);
    lv_obj_add_event_cb(button_air_quality,button_air_quality_cb,LV_EVENT_ALL, (void*)background_image);
    lv_group_add_obj(g,button_air_quality);
    lv_obj_t * button_timer = create_transparent_button(central_panel);
    lv_obj_add_event_cb(button_timer,button_timer_cb,LV_EVENT_ALL, (void*)background_image);
    lv_group_add_obj(g,button_timer);


    return main;
}

void button_thermometer_cb(lv_event_t * e){
    if(e->code==LV_EVENT_FOCUSED){
        lv_img_set_src((lv_obj_t *)e->user_data, &main_menu_thermometer);
    }
    if(e->code==LV_EVENT_PRESSED){
        cbs.temperature_screen_cb(NULL);
    }
}
void button_air_quality_cb(lv_event_t * e){
    if(e->code==LV_EVENT_FOCUSED){
        lv_img_set_src((lv_obj_t *)e->user_data, &main_menu_air_quality);
    }
    if(e->code==LV_EVENT_PRESSED){
        cbs.air_quality_screen_cb(NULL);
    }
}
void button_timer_cb(lv_event_t * e){
    if(e->code==LV_EVENT_FOCUSED){
        lv_img_set_src((lv_obj_t *)e->user_data, &main_menu_timer);
    }
    if(e->code==LV_EVENT_PRESSED){
        cbs.timer_screen_cb(NULL);
    }
}


