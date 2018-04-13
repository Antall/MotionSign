#include "Display.h"

LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void Display::init(){
  lcd.begin(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Display::run(Data &data){

  if(!data.didUpdateScreen){return;}

  for(uint8_t i=0; i< SCREEN_HEIGHT; i++){
    for(uint8_t j=0; j< SCREEN_WIDTH; j++){
      lcd.setCursor(j, i);
      Serial.write(data.screen[i][j]);
      lcd.write(data.screen[i][j]);
    }
    Serial.print("\n");
  }

  data.didUpdateScreen = false;
  
  
}
