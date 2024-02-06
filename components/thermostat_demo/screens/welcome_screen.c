#include "screens.h"

LV_IMG_DECLARE(umbrella_logo);
LV_IMG_DECLARE(umbrella_logo_small);
LV_FONT_DECLARE(logo_font_40);


static void anim_opa_cb(void * var, int32_t v);


lv_obj_t * welcome_screen_create(screens_callbacks_t finished_cb){
    lv_obj_t * main = lv_obj_create(NULL);
    lv_scr_load(main);
    lv_obj_set_scrollbar_mode(main,LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(main,lv_color_hex(COLOR_PALETTE_ONE),0);

    lv_obj_t * logo_image = lv_img_create(main);
    lv_img_set_src(logo_image, &umbrella_logo);
    lv_obj_center(logo_image);


    lv_obj_t * small_logo_image = lv_img_create(main);
    lv_img_set_src(small_logo_image, &umbrella_logo_small);
    lv_obj_set_align(small_logo_image, LV_ALIGN_TOP_MID);
    lv_obj_set_pos(small_logo_image, 0, 50);

    lv_obj_t * logo_text = lv_label_create(main);
    lv_label_set_text(logo_text,"UMBRELLA\nCORPORATION");
    lv_obj_set_style_text_font(logo_text,&logo_font_40,0);
    lv_obj_set_style_text_color(logo_text, lv_color_hex(COLOR_PALETTE_THREE),0);
    lv_obj_set_style_text_align(logo_text,LV_TEXT_ALIGN_CENTER,0);
    lv_obj_set_align(logo_text, LV_ALIGN_LEFT_MID);
    lv_obj_set_pos(logo_text, 30, 70);



    lv_anim_timeline_t * anim_timeline = lv_anim_timeline_create();


    // animation appearing logo

    lv_anim_t a_big_logo_appear;
    lv_anim_init(&a_big_logo_appear);
    lv_anim_set_var(&a_big_logo_appear, logo_image);
    lv_anim_set_values(&a_big_logo_appear, 0, 255);
    //lv_anim_set_delay(&a_big_logo_appear,1500);
    lv_anim_set_time(&a_big_logo_appear, INITIAL_ANIMATIONS_DURATION_MS); 
    lv_anim_set_exec_cb(&a_big_logo_appear, anim_opa_cb);
    lv_anim_set_path_cb(&a_big_logo_appear, lv_anim_path_linear);
    //lv_anim_start(&a_big_logo_appear);

    lv_anim_t a_big_logo_disappear;
    lv_anim_init(&a_big_logo_disappear);
    lv_anim_set_var(&a_big_logo_disappear, logo_image);
    lv_anim_set_values(&a_big_logo_disappear, 255, 0);
    //lv_anim_set_delay(&a_big_logo_appear,1500);
    lv_anim_set_time(&a_big_logo_disappear, INITIAL_ANIMATIONS_DURATION_MS); 
    lv_anim_set_exec_cb(&a_big_logo_disappear, anim_opa_cb);
    lv_anim_set_path_cb(&a_big_logo_disappear, lv_anim_path_linear);
    //lv_anim_start(&a_big_logo_appear);


    lv_anim_t a_small_logo_appear;
    lv_anim_init(&a_small_logo_appear);
    lv_anim_set_var(&a_small_logo_appear, small_logo_image);
    lv_anim_set_values(&a_small_logo_appear, 0, 255);
    //lv_anim_set_delay(&a_small_logo,1500);
    lv_anim_set_time(&a_small_logo_appear, INITIAL_ANIMATIONS_DURATION_MS); 
    lv_anim_set_exec_cb(&a_small_logo_appear, anim_opa_cb);
    lv_anim_set_path_cb(&a_small_logo_appear, lv_anim_path_linear);
    //lv_anim_start(&a_small_logo);

    lv_anim_t a_logo_text_appear;
    lv_anim_init(&a_logo_text_appear);
    lv_anim_set_var(&a_logo_text_appear, logo_text);
    lv_anim_set_values(&a_logo_text_appear, 0, 255);
    //lv_anim_set_delay(&a_small_logo,1500);
    lv_anim_set_time(&a_logo_text_appear, INITIAL_ANIMATIONS_DURATION_MS); 
    lv_anim_set_exec_cb(&a_logo_text_appear, anim_opa_cb);
    lv_anim_set_path_cb(&a_logo_text_appear, lv_anim_path_linear);
    lv_anim_set_ready_cb(&a_logo_text_appear,finished_cb.menu_screen_cb );
    //lv_anim_start(&a_small_logo);


    lv_anim_timeline_add(anim_timeline, 0, &a_big_logo_appear);
    lv_anim_timeline_add(anim_timeline, INITIAL_ANIMATIONS_DURATION_MS, &a_big_logo_disappear);
    lv_anim_timeline_add(anim_timeline, INITIAL_ANIMATIONS_DURATION_MS+INITIAL_ANIMATIONS_DELAYS_MS, &a_small_logo_appear);
    lv_anim_timeline_add(anim_timeline, INITIAL_ANIMATIONS_DURATION_MS+INITIAL_ANIMATIONS_DELAYS_MS, &a_logo_text_appear);
    
    lv_anim_timeline_start(anim_timeline);

    return main;
}

static void anim_width_cb(void * var, int32_t v)
{
    lv_obj_set_width(var, v);
}

static void anim_opa_cb(void * var, int32_t v)
{
    lv_obj_set_style_opa(var, v,0);
}
