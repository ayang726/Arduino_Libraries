/*
 * SPI Communication Master/Slave
 * 
 */


#include "SPI_COMM.h"

int PIN_CS = 9;
int PIN_SS = 10;
int PIN_MOSI = 11;
int PIN_MISO = 12;
int PIN_SCK = 13;


SPIClass::SPIClass(/* args */)
{
}

SPIClass::~SPIClass()
{
}

void SPIClass::masterInit()  {
//  DDRB = (1<<DD_MOSI)|(1<<DD_SCK);
// Setting SPI enable, Mode as Master, Speed as Clock_fre/16
    pinMode(PIN_SS,OUTPUT);
    digitalWrite(PIN_SS, HIGH);
    pinMode(PIN_CS,OUTPUT);
    digitalWrite(PIN_CS, HIGH);
    pinMode(PIN_MOSI, OUTPUT);
    pinMode(PIN_SCK, OUTPUT);
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPIClass::masterInit(int csPin) {
    PIN_CS = csPin;
    masterInit();
}

void SPIClass::slaveInit() {
//  DDRB = (1<<DD_MISO);
// Setting SPI enable
    pinMode(PIN_SS, INPUT);
    pinMode(PIN_MISO, OUTPUT);
    SPCR = (1<<SPE);
}

// Write to the SPI bus (MOSI pin) and also receive (MISO pin)
uint8_t SPIClass::transfer(uint8_t data) {
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

void SPIClass::transfer(void *buf, size_t count) {
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

void SPIClass::attachInterrupt() { SPCR |= _BV(SPIE); }
void SPIClass::detachInterrupt() { SPCR &= ~_BV(SPIE); }