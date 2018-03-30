#ifndef INTERNET_H
#define INTERNET_H

#include "Data.h"
#include <ESP8266WiFi.h>

class Internet {
  public:
    void init();
    void run(Data &data);

  private:
    void getReserved(Data &data, WiFiClient &client);
    void postOccupied(Data &data, WiFiClient &client);
    unsigned long lastRun;
};
#endif
