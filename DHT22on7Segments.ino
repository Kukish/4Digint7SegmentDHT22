//We always have to include the library
#include "libs/LedControl.h"
#include "libs/DHT_NO_FLOAT.h"

DHT sensor;
int DHTpin = 3;
int result;

/*
 pin 2 is connected to the DataIn 
 pin 1 is connected to the CLK 
 pin 0 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(2,1,0,1);

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a max values */
  lc.setIntensity(0,15);

  /* and clear the display */
  lc.clearDisplay(0);

}

void loop() { 
    result = sensor.read(DHTpin);
    if(result == DHT_ERROR_CHECKSUM){
      lc.setDigit(0, 0, 8, false);
      delay(2500);
    }
    if(result == DHT_ERROR_DATA) {
      lc.setDigit(0, 1, 8, false);
      delay(1000);
    }
    if(result == DHT_ERROR_NO_REPLY) {
      lc.setDigit(0, 2, 8, false);
      delay(2500);
    }
    if(result == -4) {
      lc.setDigit(0, 3, 8, false);
      delay(2500);
    }
    
    printNumber(sensor.tem);
    lc.setChar(0, 3, 'c', false);
    delay(2500);
    lc.clearDisplay(0);
    
    printNumber(sensor.hum);
    lc.setChar(0, 3, 'h', false);
    lc.setLed(0, 3, 2, false);
    delay(2500);
}
  void printNumber(int num) {
    if(num > 99) {
      int hundreds = num / 100;
      int tens = (num - hundreds * 100) / 10;
      int ones = num - hundreds * 100 - tens * 10;
      lc.setDigit(0, 0, hundreds, false);
      lc.setDigit(0, 1, tens, true);
      lc.setDigit(0, 2, ones, false);
    } else {
      int tens = num / 10;
      int ones = num - tens * 10;
      lc.setDigit(0, 0, tens, true);
      lc.setDigit(0, 1, ones, false);
  }
}
