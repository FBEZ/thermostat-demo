
#include "lvgl.h"
#include <stdio.h>
#include "esp_system.h"
#ifdef ESP_IDF_VERSION
#include "esp_log.h"
#endif


#include "layout.h"

static const char *TAG = "main_menu";

extern lv_group_t* g;

LV_IMG_DECLARE(umbrella_icon)
LV_FONT_DECLARE(roboto_medium_24)

static bool main_layer_enter_cb(void *layer);
static bool main_layer_exit_cb(void *layer);
static void main_layer_timer_cb(lv_timer_t *tmr);


typedef bool (*lv_layer_enter_cb)(void *);
typedef bool (*lv_layer_exit_cb)(void *);

typedef struct lv_layer {
    char *lv_obj_name;
    lv_obj_t *lv_obj_parent;
    lv_obj_t *lv_obj_layer;
    struct lv_layer *lv_show_layer;
    lv_layer_enter_cb enter_cb;
    lv_layer_exit_cb exit_cb;
    lv_timer_cb_t timer_cb;
    lv_timer_t *timer_handle;
} lv_layer_t;


lv_layer_t menu_layer = {
    .lv_obj_name    = "main_menu_Layer",
    .lv_obj_parent  = NULL,
    .lv_obj_layer   = NULL,
    .lv_show_layer  = NULL,
    .enter_cb       = main_layer_enter_cb,
    .exit_cb        = main_layer_exit_cb,
    .timer_cb       = main_layer_timer_cb,
};
typedef struct {
    const char *name_CN;
    const char *name_EN;
    const lv_img_dsc_t *icon;
    const lv_img_dsc_t *icon_ns;
    lv_color_t theme_color;
    void *layer;
} ui_menu_app_t;

static ui_menu_app_t menu[] = {
    {"Pulizia",    "Washing",     &umbrella_icon,      &umbrella_icon,       LV_COLOR_MAKE(36, 163, 235), NULL},
    {"Termosato",      "Thermostat",  &umbrella_icon,   &umbrella_icon,    LV_COLOR_MAKE(249, 139, 122), NULL},
    {"Luce",    "Light",       &umbrella_icon,        &umbrella_icon,         LV_COLOR_MAKE(255, 229, 147), NULL},
};

#define APP_NUM 3//(sizeof(menu) / sizeof(ui_menu_app_t))
static lv_obj_t *icons[APP_NUM];
static uint8_t app_index = 0;
static lv_obj_t *page;
static lv_obj_t *label_name;
static lv_obj_t *tips_btn, *tips_label;

static uint8_t tips_delay;
static uint8_t factory_Enter;

//static time_out_count time_100ms, time_500ms;

static uint32_t ui_get_num_offset(uint32_t num, int32_t max, int32_t offset)
{
    if (num >= max) {
        ESP_LOGI(TAG, "[ERROR] num should less than max");
        return num;
    }

    uint32_t i;
    if (offset >= 0) {
        i = (num + offset) % max;
    } else {
        offset = max + (offset % max);
        i = (num + offset) % max;
    }

    return i;
}

static uint32_t get_app_index(int8_t offset)
{
    return ui_get_num_offset(app_index, APP_NUM, offset);
}

void set_tips_info()
{
    tips_delay = 4;
    lv_obj_clear_flag(tips_btn, LV_OBJ_FLAG_HIDDEN);
}

static void arc_path_by_theta(int16_t theta, int16_t *x, int16_t *y)
{
    const int ox = 0, oy = 0;
    *x = ox + ((lv_trigo_sin(theta) * 45) >> LV_TRIGO_SHIFT);
    *y = oy + ((lv_trigo_sin(theta + 90) * 45) >> LV_TRIGO_SHIFT);
}

static void obj_set_to_hightlight(lv_obj_t *obj, bool enable)
{
    if (enable) {
        lv_obj_set_style_shadow_width(obj, 15, 0);
        lv_obj_set_style_shadow_spread(obj, 3, 0);
    } else {
        lv_obj_set_style_shadow_width(obj, 0, 0);
        lv_obj_set_style_shadow_spread(obj, 0, 0);
    }
}


lv_obj_t * pie_menu_create(void)
{
    lv_obj_t * page = lv_obj_create(NULL);
    lv_obj_set_size(page, DISPLAY_RADIUS_PX, DISPLAY_RADIUS_PX);

    lv_obj_set_style_border_width(page, 5, 0);
    lv_obj_set_style_border_color(page, menu[get_app_index(0)].theme_color, 0);
    lv_obj_set_style_radius(page, LV_RADIUS_CIRCLE, 0);
    lv_obj_clear_flag(page, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_center(page);
    lv_obj_refr_size(page);

    for (int i = APP_NUM - 1; i >= 0; i--) {
        int16_t x, y;
        arc_path_by_theta(180 + i * 120, &x, &y);
        icons[i] = lv_img_create(page);
        if (i == app_index) {
            lv_img_set_src(icons[i], menu[i].icon);
        } else {
            lv_img_set_src(icons[i], menu[i].icon_ns);
        }
        lv_obj_align(icons[i], LV_ALIGN_CENTER, x, y);
        lv_obj_set_style_border_color(icons[i], menu[i].theme_color, 0);
        lv_obj_set_style_shadow_color(icons[i], menu[i].theme_color, 0);
        lv_obj_set_style_border_width(icons[i], 0, 0);
        lv_obj_set_style_radius(icons[i], LV_RADIUS_CIRCLE, 0);
        obj_set_to_hightlight(icons[i], i == app_index);
    }

    if (0 != app_index) {
        lv_obj_swap(icons[0], icons[app_index]);
    }

    label_name = lv_label_create(page);

    lv_obj_set_style_text_font(label_name, &roboto_medium_24, 0);
    lv_label_set_text(label_name, menu[app_index].name_EN);

    lv_obj_set_width(label_name, 150);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label_name, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label_name, LV_ALIGN_BOTTOM_MID, 0, -6);


    tips_btn = lv_obj_create(page);
    lv_obj_set_style_border_width(tips_btn, 0, 0);
    lv_obj_set_style_pad_all(tips_btn, 0, 0);
    lv_obj_set_size(tips_btn, 200, 40);
    lv_obj_align(tips_btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(tips_btn, lv_color_hex(0x111111), LV_PART_MAIN);

    tips_label = lv_label_create(tips_btn);
    lv_obj_set_style_text_color(tips_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_center(tips_label);
    lv_obj_set_style_text_font(tips_label, &roboto_medium_24, 0);
    lv_label_set_text(tips_label, "factory default");

    lv_obj_add_flag(tips_btn, LV_OBJ_FLAG_HIDDEN);

    // lv_obj_add_event_cb(page, menu_event_cb, LV_EVENT_FOCUSED, NULL);
    // lv_obj_add_event_cb(page, menu_event_cb, LV_EVENT_KEY, NULL);
    // lv_obj_add_event_cb(page, menu_event_cb, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(page, menu_event_cb, LV_EVENT_LONG_PRESSED, NULL);
    //ui_add_obj_to_encoder_group(page);
    return page;
}

// static bool main_layer_enter_cb(void *layer)
// {
//     bool ret = false;

//     LV_LOG_USER("");
//     factory_Enter = 0;
//     lv_layer_t *create_layer = layer;

//     if (NULL == create_layer->lv_obj_layer) {
//         ret = true;
//         create_layer->lv_obj_layer = lv_obj_create(lv_scr_act());
//         lv_obj_set_size(create_layer->lv_obj_layer, LV_HOR_RES, LV_VER_RES);
//         lv_obj_set_style_border_width(create_layer->lv_obj_layer, 0, 0);
//         lv_obj_set_style_pad_all(create_layer->lv_obj_layer, 0, 0);

//         ui_menu_init(create_layer->lv_obj_layer);
//     }
//     set_time_out(&time_100ms, 200);
//     set_time_out(&time_500ms, 500);
//     feed_clock_time();

//     return ret;
// }


// static bool main_layer_exit_cb(void *layer)
// {
//     LV_LOG_USER("");
//     return true;
// }

// static void main_layer_timer_cb(lv_timer_t *tmr)
// {
//     if (is_time_out(&time_500ms)) {
//         if (tips_delay) {
//             tips_delay--;
//             if (0 == tips_delay) {
//                 lv_obj_add_flag(tips_btn, LV_OBJ_FLAG_HIDDEN);
//                 esp_restart();
//             }
//         }
//     }

//     return;
// }