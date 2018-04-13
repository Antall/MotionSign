
#include "Display.h"

void Display::init(){
  lcd = LiquidCrystal(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
}

void Display::run(Data &data){

  for(uint8_t i=0; i< SCREEN_HEIGHT; i++){
    for(uint8_t j=0; j< SCREEN_WIDTH; j++){
      lcd.setCursor(j, i);
      lcd.write(data.screen[i][j]);
    }
  }
  
}
