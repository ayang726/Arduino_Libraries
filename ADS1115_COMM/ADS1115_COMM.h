#ifndef ADS1115_COMM_h
#define ADS1115_COMM_h

#include <Adafruit_ADS1015.h>
// #include <vector>

class ADS1115_COMM{

	
	private: 
		int numDevices = 4;
		uint8_t deviceAddresses[];
		// vector <DeviceChannel2Scan> deviceChannel2Scan;
		
		Adafruit_ADS1115 ads1;
        Adafruit_ADS1115 ads2;
        Adafruit_ADS1115 ads3;
        Adafruit_ADS1115 ads4;
	public:
		uint16_t rawInputs[4][4];
		float analogValues[4][4];
        Adafruit_ADS1115 adsArray[4];
		void setup();
		void loop();
		ADS1115_COMM();
		// addDeviceChannel(String, int)
        void scanSingleEnded();
		float sixteenBitToAnalogConversion(int);

		uint16_t readRawValueFrom(int, int);
		float readAnalogValueFrom(int, int);
		float mapFloat(float, float, float, float, float);
};

// struct DeviceChannel2Scan
// {
// 	public:
// 		DeviceChannel2Scan(Adafruit_ADS1115*, int)
// 		Adafruit_ADS1115* device;
// 		int channel;
// };


#endif