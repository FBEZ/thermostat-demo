#include "widgets.h"
#include <stdio.h>
extern thermostat_settings_t settings;
LV_FONT_DECLARE(roboto_regular_100);
LV_FONT_DECLARE(roboto_regular_50);

static lv_style_t style_arc;

static void set_temperature_value_changed_cb(lv_event_t * e);
static int16_t percentage_from_temperature(int16_t);
static int16_t temperature_from_percentage(int16_t);

lv_obj_t * create_temperature_arc(lv_obj_t * parent){
    
    lv_obj_t * arc = lv_arc_create(parent);
    lv_obj_set_size(arc, ARC_SIZE_PX, ARC_SIZE_PX);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    //lv_arc_set_range(arc,TEMPERATURE_ARC_MIN_DECI_CELSIUS,TEMPERATURE_ARC_MAX_DECI_CELSIUS);
    lv_arc_set_value(arc, percentage_from_temperature(settings.set_temperature_celsius));
    printf("First temperature set: %d\n", percentage_from_temperature(settings.set_temperature_celsius));
    lv_obj_center(arc);
  
    lv_obj_set_style_arc_color(arc,lv_color_hex(COLOR_PALETTE_ONE),LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(arc,lv_color_hex(COLOR_PALETTE_THREE),LV_PART_KNOB);
    lv_obj_set_style_bg_color(arc,lv_color_hex(COLOR_PALETTE_FIVE),LV_PART_MAIN);

    lv_obj_t * label_temperature = lv_label_create(arc);
    //lv_label_set_text_fmt(label_temperature, "%d", (settings.set_temperature_deci_celsius-MINIMUM_TEMPERATURE)/(MAXIMUM_TEMPERATURE-MINIMUM_TEMPERATURE)*100);
    lv_obj_set_style_text_font(label_temperature,&roboto_regular_100,0);
    lv_obj_center(label_temperature);


    lv_obj_t * label_celsius = lv_label_create(arc);
    lv_label_set_text(label_celsius,"°C");
    lv_obj_align(label_celsius,LV_ALIGN_BOTTOM_MID,0,0);
    lv_obj_set_style_text_font(label_celsius,&roboto_regular_50,0);

    lv_obj_add_event_cb(arc, set_temperature_value_changed_cb, LV_EVENT_VALUE_CHANGED, label_temperature);
    lv_event_send(arc, LV_EVENT_VALUE_CHANGED, label_temperature);

    return arc;
}

static int16_t temperature_from_percentage(int16_t percentage){
    return (MINIMUM_TEMPERATURE + percentage*(MAXIMUM_TEMPERATURE-MINIMUM_TEMPERATURE)/100);
}
static int16_t percentage_from_temperature(int16_t temperature){
    return (temperature-MINIMUM_TEMPERATURE)*100/(MAXIMUM_TEMPERATURE-MINIMUM_TEMPERATURE);
}


static void set_temperature_value_changed_cb(lv_event_t * e){
    lv_obj_t * arc = lv_event_get_target(e);
    lv_obj_t * label = lv_event_get_user_data(e);

    uint16_t scale_factor = lv_arc_get_value(arc); // from 0 to 100
    lv_color_t point_color = lv_color_make((uint16_t)(GET_RED(KNOB_GRADIENT_START)  *(100-scale_factor)+GET_RED(KNOB_GRADIENT_END)  *scale_factor)/100, 
                                           (uint16_t)(GET_GREEN(KNOB_GRADIENT_START)*(100-scale_factor)+GET_GREEN(KNOB_GRADIENT_END)*scale_factor)/100, 
                                           (uint16_t)(GET_BLUE(KNOB_GRADIENT_START) *(100-scale_factor)+GET_BLUE(KNOB_GRADIENT_END) *scale_factor)/100);
  

    lv_label_set_text_fmt(label, "%d", temperature_from_percentage(scale_factor));
    settings.set_temperature_celsius = temperature_from_percentage(scale_factor);
    printf("Scale factor: %d\tSet temp: %d\n", scale_factor, settings.set_temperature_celsius);

    lv_obj_set_style_text_color(label, point_color,0);
    lv_obj_set_style_bg_color(arc,point_color,LV_PART_INDICATOR);
}