#ifndef WIDGETS_H
#define WIDGETS_H

#include "lvgl.h"
#include "layout.h"

lv_obj_t * create_simple_button(lv_obj_t * parent, char * label_text);
lv_obj_t * create_transparent_button(lv_obj_t * parent);

#endif