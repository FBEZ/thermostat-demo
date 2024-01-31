#include <stdio.h>
#include "thermostat_demo.h"
#include "screens.h"
#include "lvgl.h"

lv_group_t *  g;
extern lv_indev_t * knob_indev;

void thermostat_demo(void)
{
    g= lv_group_create();
    lv_indev_set_group(knob_indev, g);


    //lv_obj_t * welcome_scr = welcome_screen();
    lv_obj_t * welcome_scr = welcome_screen_create();
    //lv_obj_t * rotary_scr = rotary_screen();
    lv_scr_load(welcome_scr);

}
  