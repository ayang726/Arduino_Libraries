#ifndef DataHandler_h
#define DataHandler_h

#include <Arduino.h>

struct SocketData {
  private:
    String event;
    int data;
    String dataStr;
  public:
    SocketData(String, int);
    SocketData(int);
    String parsedString;
};



#endif