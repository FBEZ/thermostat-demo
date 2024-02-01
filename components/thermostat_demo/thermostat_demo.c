#include <stdio.h>
#include "thermostat_demo.h"
#include "screens.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

lv_group_t *  g;
extern lv_indev_t * knob_indev;
bool welcome_screen_loaded = false;

void loading_welcome_screen(lv_anim_t * a);

void thermostat_demo(void)
{
    g= lv_group_create();
    lv_indev_set_group(knob_indev, g);

    //lv_obj_t * welcome_scr = welcome_screen();
    lv_obj_t * welcome_scr = welcome_screen_create(loading_welcome_screen);
    lv_scr_load(welcome_scr);

}


void loading_welcome_screen(lv_anim_t * a) {
        printf("called\n");
        lv_obj_t * rotary_scr = rotary_screen_create();
        lv_scr_load(rotary_scr);
}
  