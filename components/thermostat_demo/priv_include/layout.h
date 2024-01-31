#ifndef LAYOUT_H
#define LAYOUT_H


/*COLOR PALETTE*/

// Five color palette
#define COLOR_PALETTE_ONE    0x2B2D42
#define COLOR_PALETTE_TWO    0x8D99AE
#define COLOR_PALETTE_THREE  0xEDF2F4
#define COLOR_PALETTE_FOUR   0xEF233C
#define COLOR_PALETTE_FIVE   0xD80032

// Color Macros
#define GET_RED(NUMBER)   (uint16_t)(((NUMBER)>>16) & 0xFF)
#define GET_BLUE(NUMBER)  (uint16_t)(((NUMBER)>>8)  & 0xFF)
#define GET_GREEN(NUMBER) (uint16_t)(((NUMBER))     & 0xFF)


/*DIMENSIONS*/

#define DISPLAY_RADIUS_PX       480
#define CENTRAL_PANEL_RADIUS_PX 400
#define DEFAULT_BUTTON_SIZE_PX  40



#endif