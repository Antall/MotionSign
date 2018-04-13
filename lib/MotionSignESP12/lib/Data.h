#ifndef DATA_H
#define DATA_H

#include "Arduino.h"

#define DEBUG_PRINT

#define SCREEN_WIDTH 20
#define SCREEN_HEIGHT 4

class Data{

  public:
    Data();
    bool isOccupied;
    bool isReserved;
    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    void wipeScreen();
    void storeChar(char incomingByte);
    bool didUpdateScreen;

  private:
    uint8_t cursorX;
    uint8_t cursorY;
    void shiftUp();
    void checkCursor();


};

#endif
