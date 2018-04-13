#ifndef DISPLAY_H
#define DISPLAY_H

#include "Data.h"
#include <LiquidCrystal.h>

#define LCD_RS 15
#define LCD_ENABLE 2
#define LCD_D4 16
#define LCD_D5 15
#define LCD_D6 12
#define LCD_D7 13

class Display {

  public:
    void init();
    void run(Data &data);

  private:
    LiquidCrystal lcd;
};

#endif
