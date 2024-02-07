#ifndef WIDGETS_H
#define WIDGETS_H

#include "lvgl.h"
#include "layout.h"
#include "priv_types.h" // for the thermostat settings

lv_obj_t * create_simple_button(lv_obj_t * parent, char * label_text);
lv_obj_t * create_transparent_button(lv_obj_t * parent);
lv_obj_t * create_temperature_arc(lv_obj_t * parent);

#endif