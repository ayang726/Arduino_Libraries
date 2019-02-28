#ifndef SPI_COMM_h
#define SPI_COMM_h

#include <Arduino.h>

class SPI_COMM
{
private:
public:
    int CSPIN;
    SPI_COMM(/* args */);
    ~SPI_COMM();
    void masterInit();
    void masterInit(int);
    void slaveInit();
    uint8_t transfer(uint8_t);
    void transfer(void*, size_t);
};


#endif