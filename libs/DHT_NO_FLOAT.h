#ifndef DHT_NO_FLOAT_h
#define DHT_NO_FLOAT_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define	DHT_OK				 0	//	Data OK
#define	DHT_ERROR_CHECKSUM	-1	//	Data are not correct, disturbance from other device on the same pin
#define	DHT_ERROR_DATA		-2	//	data is not as per datasheet 
#define	DHT_ERROR_NO_REPLY	-3	//	no sensor

class DHT{
	public:
		int		read(int pinDHT);	
		int 	hum;				//	humidity * 10 in %
		int	tem;				//	temperarure * 10 in °C
	private:
		int		readSDA(int pinDHT);//	reads SDA to reply[]
		int		model[];			//	model of a sensor
		uint8_t	reply[6];			//	inner array of 5 bytes, (data type: u - unsingned, int - integer, 8 - bits number, _t - type)
};

#endif