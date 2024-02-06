#include "screens.h"
#include "widgets.h"

extern lv_group_t * g;

lv_obj_t * rotary_screen_create(screens_callbacks_t screens_callbacks){
    lv_obj_t * main = lv_obj_create(NULL);
    lv_obj_t * arc = create_temperature_arc(main);
    lv_group_add_obj(g,arc);
    return main;

}