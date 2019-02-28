/*
 * SPI Communication Master/Slave
 * 
 */


#include "SPI_COMM.h"

int CSPIN = 9;
const int SSPIN = 10;
// const int DD_MOSI = DDB3;
// const int DD_MISO = DDB4;
// const int DD_SCK = DDB5;
const int PIN_MOSI = 11;
const int PIN_MISO = 12;
const int PIN_SCK = 13;


SPI_COMM::SPI_COMM(/* args */)
{
}

SPI_COMM::~SPI_COMM()
{
}

void SPI_COMM::masterInit()  {
//  DDRB = (1<<DD_MOSI)|(1<<DD_SCK);
// Setting SPI enable, Mode as Master, Speed as Clock_fre/16
    pinMode(SSPIN,OUTPUT);
    digitalWrite(SSPIN, HIGH);
    pinMode(CSPIN,OUTPUT);
    digitalWrite(CSPIN, HIGH);
    pinMode(PIN_MOSI, OUTPUT);
    pinMode(PIN_SCK, OUTPUT);
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_COMM::masterInit(int csPin) {
    CSPIN = csPin;
    masterInit();
}

void SPI_COMM::slaveInit() {
//  DDRB = (1<<DD_MISO);
// Setting SPI enable
    pinMode(SSPIN, INPUT);
    pinMode(PIN_MISO, OUTPUT);
    SPCR = (1<<SPE);
}

// Write to the SPI bus (MOSI pin) and also receive (MISO pin)
uint8_t SPI_COMM::transfer(uint8_t data) {
    SPDR = data;
    /*
        * The following NOP introduces a small delay that can prevent the wait
        * loop form iterating when running at the maximum speed. This gives
        * about 10% more speed, even if it seems counter-intuitive. At lower
        * speeds it is unnoticed.
        */
    // asm volatile("nop");
    while (!(SPSR & _BV(SPIF)));
    return SPDR;
}

void SPI_COMM::transfer(void *buf, size_t count) {
    if (count == 0) return;
    uint8_t *p = (uint8_t *)buf;
    SPDR = *p;
    while (--count > 0) {
        uint8_t out = *(p + 1);
        while (!(SPSR & _BV(SPIF))) ;
        uint8_t in = SPDR;
        SPDR = out;
        *p++ = in;
    }
    while (!(SPSR & _BV(SPIF))) ;
    *p = SPDR;
}