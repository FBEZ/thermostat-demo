#ifndef PRIV_TYPES_H
#define PRIV_TYPES_H

typedef struct _welcome_screen_callbacks{
    lv_anim_ready_cb_t menu_screen_cb;
    lv_anim_ready_cb_t temperature_screen_cb;
    lv_anim_ready_cb_t air_quality_screen_cb;
    lv_anim_ready_cb_t timer_screen_cb;
}screens_callbacks_t;


typedef struct _settings{
    int16_t set_temperature_deci_celsius;
    int16_t measured_temperature_deci_celsius;
}thermostat_settings_t;

#endif