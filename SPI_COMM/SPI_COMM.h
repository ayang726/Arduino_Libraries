#ifndef SPI_COMM_h
#define SPI_COMM_h

#include <Arduino.h>

class SPIClass
{
private:
public:
    int CSPIN;
    SPIClass(/* args */);
    ~SPIClass();
    void masterInit();
    void masterInit(int);
    void slaveInit();
    uint8_t transfer(uint8_t);
    void transfer(void*, size_t);
    void attachInterrupt();
    void detachInterrupt();
};


#endif