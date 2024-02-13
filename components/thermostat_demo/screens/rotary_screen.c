#include "screens.h"
#include "widgets.h"
#include <stdio.h>

extern lv_group_t * g;

static screens_callbacks_t cbs;
static void go_back_cb(lv_event_t *);

lv_obj_t * rotary_screen_create(screens_callbacks_t screens_callbacks){
    cbs = screens_callbacks;
    
    lv_obj_t * main = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(main, lv_color_hex(COLOR_PALETTE_THREE),LV_PART_MAIN);

    lv_obj_t * arc = create_temperature_arc(main);
    lv_event_send(arc,LV_KEY_ENTER,NULL); //put already in navigation mode
    lv_obj_add_event_cb(arc,go_back_cb,LV_EVENT_ALL,NULL);
    lv_group_add_obj(g,arc);

    return main;
}

static void go_back_cb(lv_event_t * e){
    printf("Code event:%d\n",e->code);
    //printf("Longpress!\n");
    if(e->code==LV_EVENT_LONG_PRESSED||e->code==LV_EVENT_LONG_PRESSED_REPEAT){
        //printf("Longpress\n");
        lv_group_remove_all_objs(g);
        cbs.menu_screen_cb(NULL);
    }
}