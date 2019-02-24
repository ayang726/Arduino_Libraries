#ifndef ADS1115_COMM_h
#define ADS1115_COMM_h

#include <Adafruit_ADS1015.h>

class ADS1115_COMM{

	
	private: 
		int numDevices = 4;
		uint8_t addrArray[4];
		
		
		Adafruit_ADS1115 ads1;
        Adafruit_ADS1115 ads2;
        Adafruit_ADS1115 ads3;
        Adafruit_ADS1115 ads4;
	public:
		uint16_t rawInputs[4][4];
		float analogValues[4][4];
        Adafruit_ADS1115 adsArray[4];

		ADS1115_COMM();
        void scanSingleEnded();
		float sixteenBitToAnalogConversion(int);

		uint16_t readRawValueFrom(int, int);
		float readAnalogValueFrom(int, int);
		float mapFloat(float, float, float, float, float);
};

#endif