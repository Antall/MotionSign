#include "Data.h"

Data::Data(){

  isOccupied = false;
  isReserved = false;
  didUpdateScreen = false;
  this->wipeScreen();
}

void Data::wipeScreen(){
  cursorX = 0;
  cursorY = 0;
  for(uint8_t i=0; i<SCREEN_HEIGHT; i++){
    for(uint8_t j=0; j<SCREEN_WIDTH; j++){
      screen[i][j] = ' ';
    }
  }
}

void Data::storeChar(char incomingByte){
  didUpdateScreen = true;

  if(incomingByte == 13 || incomingByte == '\n'){
    cursorY++;
    cursorX = 0;
    return;
  }

  this->checkCursor();
  screen[cursorY][cursorX] = incomingByte;
  cursorX++;
}

void Data::checkCursor(){
  if(cursorX >= SCREEN_WIDTH){
    cursorX = 0;
    cursorY++;
  }

  if(cursorY >= SCREEN_HEIGHT){
    this->shiftUp();
    cursorY = SCREEN_HEIGHT-1;
  }
}

void Data::shiftUp(){
  for(uint8_t i=0; i < (SCREEN_HEIGHT - 1); i++){
    for(uint8_t j=0; j < SCREEN_WIDTH; j++){
      screen[i][j] = screen[i+1][j];
    }
  }
  for(uint8_t j=0; j < SCREEN_WIDTH; j++){
    screen[SCREEN_HEIGHT - 1][j] = ' ';
  }
}
