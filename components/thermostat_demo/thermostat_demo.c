#include <stdio.h>
#include "thermostat_demo.h"
#include "screens.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "priv_types.h"

lv_group_t *  g;
extern lv_indev_t * knob_indev;
bool welcome_screen_loaded = false;
thermostat_settings_t settings = {
    .set_temperature_deci_celsius = 22,
    .measured_temperature_deci_celsius = 22
};

void load_menu_screen_cb(lv_anim_t * a);
void load_temperature_screen_cb(lv_anim_t * a);
void load_air_quality_screen_cb(lv_anim_t * a);
void load_timer_screen_cb(lv_anim_t * a);

static screens_callbacks_t cbs = {
    .menu_screen_cb = load_menu_screen_cb,
    .temperature_screen_cb = load_temperature_screen_cb,
    .air_quality_screen_cb = load_air_quality_screen_cb,
    .timer_screen_cb = load_timer_screen_cb
};


void thermostat_demo(void)
{

    g= lv_group_create();
    lv_indev_set_group(knob_indev, g);
    lv_obj_t * welcome_scr = welcome_screen_create(cbs);
    lv_scr_load(welcome_scr);
}


void load_menu_screen_cb(lv_anim_t * a) {
        printf("called menu screen\n");
        lv_obj_t * menu_scr = menu_screen_create(cbs);
        lv_scr_load_anim(menu_scr,LV_SCR_LOAD_ANIM_NONE,0,0,true);
}

void load_temperature_screen_cb(lv_anim_t * a){
    lv_obj_t * temperature_scr = rotary_screen_create(cbs);
    lv_scr_load_anim(temperature_scr, LV_SCR_LOAD_ANIM_NONE, 0,0,true);
    printf("chiamata cb temperatura\n");
    
}

void load_air_quality_screen_cb(lv_anim_t * a){

}

void load_timer_screen_cb(lv_anim_t * a){

}