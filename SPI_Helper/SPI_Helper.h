#ifndef SPI_Helper_h
#define SPI_Helper_h

#include <Arduino.h>

uint8_t spiDataBuf[64];
uint8_t * spiBufferPtr = &spiDataBuf[0];

typedef union {
    float number;
    uint8_t bytes[4];
} floatUnion;


int counter = 0;
void spiResetBufferPtr() {
  spiBufferPtr = &spiDataBuf[0];
  counter = 0;
}
void spiClearBuffer() {
  for(size_t i = 0; i < 64; i++)
  {
    spiDataBuf[i] = 0x00000000;
  }
  spiResetBufferPtr();
}

void spiTransferData(SPIClass *spi, size_t count, size_t size) {
  spiResetBufferPtr();
  for(size_t i = 0; i < count; i++)
  {
    for(size_t j = 0; j < size; j++)
    {
        Serial.print("Transfering data #");
        Serial.println(counter++);
    //   Serial.print("buffered data before sending: ");
    //   Serial.println(*(spiBufferPtr));
      *spiBufferPtr = spi->transfer(*spiBufferPtr);
      spiBufferPtr++;
    //   Serial.print("buffered data after written into: ");
    //   Serial.println(*(spiBufferPtr-1));
    }
  }
}


void spiTransmit(SPIClass *spi, uint8_t *data, size_t count) {
  spiClearBuffer();
  spiResetBufferPtr();
  for(size_t i = 0; i < count; i++)
  {
    *spiBufferPtr++ = *(data+i);
  }
  spiTransferData(spi, count, sizeof(*data));
}

void spiTransmit(SPIClass *spi, uint16_t *data, size_t count) {
  spiClearBuffer();
  spiResetBufferPtr();
  for(size_t i = 0; i < count; i++)
  {
    uint16_t n = *(data+i);
    for(size_t j = 0; j < sizeof(n); j++)
    {
      *spiBufferPtr++ = n>>(j*8);
    }  
  }     
  spiTransferData(spi, count, sizeof(*data));
}

void spiTransmit(SPIClass *spi, uint32_t *data, size_t count) {
  spiClearBuffer();
  spiResetBufferPtr();
  for(size_t i = 0; i < count; i++)
  {
    uint32_t n = *(data+i);
    for(size_t j = 0; j < sizeof(n); j++)
    {
      *spiBufferPtr++ = n>>(j*8);
    }  
  }     
  spiTransferData(spi, count, sizeof(*data));
}

void spiTransmit(SPIClass *spi, float *data, size_t count) {
  spiClearBuffer();
  spiResetBufferPtr();
  for(size_t i = 0; i < count; i++)
  {
    floatUnion n;
    n.number = *(data+i);
    for(size_t j = 0; j < sizeof(n); j++)
    {
        *spiBufferPtr++ = n.bytes[j];
        // Serial.print("buffer data: ");
        // Serial.println(*(spiBufferPtr-1));
    }  
  }     
  spiTransferData(spi, count, sizeof(*data));
}


void spiReceive(SPIClass *spi, uint8_t * dataTablePtr, size_t count) {
  spiClearBuffer();
  spiTransferData(spi, count, sizeof(uint8_t));
  spiResetBufferPtr();
  for(size_t i = 0; i < count; i++)
  {
    *dataTablePtr++ = *spiBufferPtr++;
  }
}

void spiReceive(SPIClass *spi, uint16_t * dataTablePtr, size_t count) {
  int size = sizeof(uint16_t);
  spiClearBuffer();
  spiTransferData(spi, count, size);
  spiResetBufferPtr();
  for(size_t i = 0; i < count; i++)
  {
    uint16_t n = *spiBufferPtr++ | *spiBufferPtr++ << 8; 
    // Serial.print("data n is: ");
    // Serial.println(n);
    *dataTablePtr++ = n;
  }
}

void spiReceive(SPIClass *spi, uint32_t * dataTablePtr, size_t count) {
  int size = sizeof(uint32_t);
  spiClearBuffer();
  spiTransferData(spi, count, size);
  spiResetBufferPtr();
  for(size_t i = 0; i < count; i++)
  {
    uint32_t n = *spiBufferPtr++ | *spiBufferPtr++ << 8 | *spiBufferPtr++ << 16 | *spiBufferPtr++ << 24;
    *dataTablePtr++ = n;
  }
}

void spiReceive(SPIClass *spi, float * dataTablePtr, size_t count) {
  int size = sizeof(float);
  spiClearBuffer();
  spiTransferData(spi, count, size);
  spiResetBufferPtr();
  for(size_t i = 0; i < count; i++)
  {
    floatUnion n;
    for(size_t j = 0; j < size; j++)
    {
        // Serial.print("buffer data: ");
        // Serial.println(*spiBufferPtr);
        n.bytes[4-j] = *spiBufferPtr++;
        // Serial.println(n.bytes[j]);
    }
    
    *dataTablePtr++ = n.number;
  }
}


#endif