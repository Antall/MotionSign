#ifndef DISPLAY_H
#define DISPLAY_H

#include "Data.h"
#include <LiquidCrystal.h>

#define LCD_RS 15
#define LCD_ENABLE 2
#define LCD_D4 13
#define LCD_D5 12
#define LCD_D6 14
#define LCD_D7 16

class Display {

  public:
    void init();
    void run(Data &data);
};

#endif
