#ifndef SCREENS_H
#define SCREENS_H

#include "lvgl.h"
#include "layout.h"

lv_obj_t * welcome_screen_create(lv_anim_ready_cb_t);
lv_obj_t * menu_screen_create(void);
lv_obj_t * rotary_screen_create(void);
lv_obj_t * pie_menu_create(void);

#endif