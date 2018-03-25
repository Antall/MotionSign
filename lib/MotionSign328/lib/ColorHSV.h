#ifndef COLOR_HSV
#define COLOR_HSV

struct ColorHSV{
  uint16_t hue;
  uint8_t sat;
  uint8_t val;


  // default values are UNITIALIZED
  inline ColorHSV() __attribute__((always_inline))
  {
  }

  inline ColorHSV( uint16_t ih, uint8_t is, uint8_t iv) __attribute__((always_inline)) 
  {
    hue = ih; sat = is; val = iv;
  }

};

#endif
