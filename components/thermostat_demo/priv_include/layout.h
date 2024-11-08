#ifndef LAYOUT_H
#define LAYOUT_H


/*COLOR PALETTE*/

// Five color palette
#define COLOR_PALETTE_ONE    0x2B2D42 // grigio scuro
#define COLOR_PALETTE_TWO    0x8D99AE // grigio chiaro
#define COLOR_PALETTE_THREE  0xEDF2F4 // bianco 
#define COLOR_PALETTE_FOUR   0xEF233C // rosso chiaro
#define COLOR_PALETTE_FIVE   0xD80032 // rosso scuro

#define KNOB_GRADIENT_START COLOR_PALETTE_TWO
#define KNOB_GRADIENT_END COLOR_PALETTE_FIVE



// Color Macros
#define GET_RED(NUMBER)   (uint16_t)(((NUMBER)>>16) & 0xFF)
#define GET_BLUE(NUMBER)  (uint16_t)(((NUMBER)>>8)  & 0xFF)
#define GET_GREEN(NUMBER) (uint16_t)(((NUMBER))     & 0xFF)


/*DIMENSIONS*/

#define DISPLAY_RADIUS_PX       480
#define CENTRAL_PANEL_RADIUS_PX 400
#define DEFAULT_BUTTON_SIZE_PX  40

#define ARC_SIZE_PX 300

/*TIMINGS*/

#define INITIAL_ANIMATIONS_DURATION_MS 2000
#define INITIAL_ANIMATIONS_DELAYS_MS 1000

/*RANGES*/
#define TEMPERATURE_ARC_MIN_DECI_CELSIUS 100
#define TEMPERATURE_ARC_MAX_DECI_CELSIUS 400
#define MINIMUM_TEMPERATURE 10
#define MAXIMUM_TEMPERATURE 40



#endif