#include "screens.h"

LV_IMG_DECLARE(umbrella_logo);

static void anim_x_cb(void * var, int32_t v);
static void anim_width_cb(void * var, int32_t v);
static void anim_opa_cb(void * var, int32_t v);

lv_obj_t * welcome_screen_create(void){
    lv_obj_t * main = lv_obj_create(NULL);
    lv_scr_load(main);
    lv_obj_set_scrollbar_mode(main,LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(main,lv_color_hex(COLOR_PALETTE_ONE),0);
    lv_obj_t * logo_image = lv_img_create(main);
    lv_img_set_src(logo_image, &umbrella_logo);
    lv_obj_center(logo_image);


    // animation

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, logo_image);
    lv_anim_set_values(&a, 0, 255);
    lv_anim_set_delay(&a,1500);
    lv_anim_set_time(&a, 1500); 
    lv_anim_set_exec_cb(&a, anim_opa_cb);
    lv_anim_set_path_cb(&a, lv_anim_path_linear);
    lv_anim_start(&a);

    return main;
}


static void anim_x_cb(void * var, int32_t v)
{
    lv_obj_set_x(var, v);
}

static void anim_width_cb(void * var, int32_t v)
{
    lv_obj_set_width(var, v);
}

static void anim_opa_cb(void * var, int32_t v)
{
    lv_obj_set_style_opa(var, v,0);
}