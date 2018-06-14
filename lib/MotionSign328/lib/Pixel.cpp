#include "Pixel.h"

Pixel::Pixel(){
  hsv.hue = 0;
  hsv.sat = 0xFF;
  hsv.val = 0xFF;
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)b << 16) | ((uint32_t)g <<  8) | r;
}


void Pixel::setFrom(Pixel* pixel){
  hsv = pixel->hsv;
}

void Pixel::set(uint16_t h, uint8_t s, uint8_t v){
  hsv.hue = h; hsv.sat = s; hsv.val = v;
}

uint32_t Pixel::color()
{
  return ColorFromHSV(hsv);
}

uint32_t ColorFromHSV(ColorHSV hsv){
    unsigned char region, fpart, p, q, t, r, g, b;

    uint16_t h = hsv.hue >> 8,
             s = hsv.sat,
             v = hsv.val;

    if(s == 0) {
        /* color is grayscale */
        r = g = b = hsv.val;
        return Color(r, g, b);
    }

    /* make hue 0-5 */
    region = h / 43;
    /* find remainder part, make it from 0-255 */
    fpart = (h - (region * 43)) * 6;

    /* calculate temp vars, doing integer multiplication */
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * fpart) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - fpart)) >> 8))) >> 8;

    /* assign temp vars based on color cone region */
    switch(region) {
        case 0:
            r = v; g = t; b = p; break;
        case 1:
            r = q; g = v; b = p; break;
        case 2:
            r = p; g = v; b = t; break;
        case 3:
            r = p; g = q; b = v; break;
        case 4:
            r = t; g = p; b = v; break;
        default:
            r = v; g = p; b = q; break;
    }

    return Color(r, g, b);
}
