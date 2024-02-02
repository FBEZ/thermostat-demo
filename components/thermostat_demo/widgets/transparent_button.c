#include "widgets.h"

lv_obj_t * create_transparent_button(lv_obj_t * parent){
    lv_obj_t * ret = lv_obj_create(parent);
    lv_obj_remove_style_all(ret);
    lv_obj_set_style_opa(ret,LV_OPA_0, 0);
    return ret;
}