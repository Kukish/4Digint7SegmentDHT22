#include "DHT_NO_FLOAT.h"

int	DHT::read(int PinDHT){
//	read SDA bus
	int i=readSDA(PinDHT); if(i<0){return i;}
	hum=reply[1]+(reply[0]<<8);
	tem=(reply[3]+((reply[2]&0x7F)<<8))*((reply[2]&0x80?1:1));
	return 0;
}

int	DHT::readSDA(int PinDHT){
//	nullify array
	reply[0]=reply[1]=reply[2]=reply[3]=reply[4]=0;
//	pull down bus for 25ms
	pinMode(PinDHT,OUTPUT); digitalWrite(PinDHT,LOW); delay(25);
//	pull up bus
	pinMode(PinDHT,INPUT);
//	check sensor for "start" signal
	if(pulseIn(PinDHT,HIGH,600)==0){return -3;}
//	read sensor (40 bits)
	for(int i=0,j=0; i<40; i++){
		j=pulseIn(PinDHT,HIGH,600); 
		if(j){
			reply[i/8]<<=1; reply[i/8]+=j>45?1:0;}
		else{return -2;
		}
	}
//	check if sensor sends more than 40 bits
	if(pulseIn(PinDHT,HIGH,600)>0){return -4;}
//	verify checksum
	if(((reply[0]+reply[1]+reply[2]+reply[3])&0xff)!=reply[4]){return -1;}
//	get sensor model
//  not used in this skecth as I use DHT22 sensor only
	if(reply[1]||reply[3]||reply[2]&0x80){model[PinDHT]=22;}else if(reply[0]>3||reply[2]>4){model[PinDHT]=11;}
	return 0;
}
