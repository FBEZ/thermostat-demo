#include "widgets.h"

lv_obj_t * create_temperature_arc(lv_obj_t * parent){
    lv_obj_t * arc = lv_arc_create(parent);
    lv_obj_set_size(arc, 300, 300);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_value(arc, 40);
    lv_obj_center(arc);
    return arc;
}