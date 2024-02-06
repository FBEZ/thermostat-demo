#ifndef SCREENS_H
#define SCREENS_H

#include "lvgl.h"
#include "layout.h"
#include "priv_types.h"

lv_obj_t * welcome_screen_create(screens_callbacks_t);
lv_obj_t * menu_screen_create(screens_callbacks_t);
lv_obj_t * rotary_screen_create(screens_callbacks_t);
lv_obj_t * pie_menu_create(screens_callbacks_t);

#endif