#include "ADS1115_COMM.h"


const uint8_t deviceAddress1 = 0b1001000; // GND
const uint8_t deviceAddress2 = 0b1001001; // VDD
const uint8_t deviceAddress3 = 0b1001010; // SDA
const uint8_t deviceAddress4 = 0b1001011; // SCL
const uint8_t deviceAddresses[] {deviceAddress2,deviceAddress1,deviceAddress3,deviceAddress4};

ADS1115_COMM::ADS1115_COMM () {
	// this -> numDevices = numDevices;

	for (int i = 0; i < numDevices; ++i)
	{
		addrArray[i] = deviceAddresses[i];
	}
    
    ads1 = Adafruit_ADS1115(deviceAddress1);
    ads2 = Adafruit_ADS1115(deviceAddress2);
    ads3 = Adafruit_ADS1115(deviceAddress3);
    ads4 = Adafruit_ADS1115(deviceAddress4);

    // The ADC input range (or gain) can be changed via the following
    // functions, but be careful never to exceed VDD +0.3V max, or to
    // exceed the upper and lower limits if you adjust the input range!
    // Setting these values incorrectly may destroy your ADC!
    //                                                                ADS1015  ADS1115
    //                                                                -------  -------
    // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
    // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
    // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
    // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
    // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
    // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

    // ads1.setGain(GAIN_TWO);
    // ads2.setGain(GAIN_TWO);
    // ads3.setGain(GAIN_TWO);
    // ads4.setGain(GAIN_TWO);

    ads1.begin();
    ads2.begin();
    ads3.begin();
    ads4.begin();

    adsArray[0] = ads1;
    adsArray[1] = ads2;
    adsArray[2] = ads3;
    adsArray[3] = ads4;

}

float ADS1115_COMM::mapFloat(float val, float fromLow, float fromHigh, float toLow, float toHigh) {
    return (val - fromLow) / (fromHigh - fromLow) * (toHigh - toLow) + toLow;
}


void ADS1115_COMM::scanSingleEnded() {
    int numChannel = 4;
    for (int i = 0; i < numDevices; i++){ 
        for (int j = 0; j < numChannel  ; j++) {
            rawInputs[i][j] = adsArray[i].readADC_SingleEnded(j);
            analogValues[i][j] = ADS1115_COMM::mapFloat(rawInputs[i][j],-32768,32768,-24.576,24.576);
        }
    }
}

// Not used
float ADS1115_COMM::sixteenBitToAnalogConversion(int input) {
  return (float) input / 65535 * 16 + 4;
}

uint16_t ADS1115_COMM::readRawValueFrom(int deviceNum, int channel) {
	return rawInputs[deviceNum][channel];
}
float ADS1115_COMM::readAnalogValueFrom(int deviceNum, int channel) {
    return analogValues[deviceNum][channel];
}

