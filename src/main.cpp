#include <Arduino.h>
#include "Ble.h"
Ble ble;

// Color Target LEDs
const int RGBW_pins[4] = {13,27,25,32};//R/G/B/W



void setupLed(int pin, int channel){
    pinMode(pin, OUTPUT);
    ledcSetup(channel, 5000, 8); //frequeny 5000, 8 bit
    ledcAttachPin(pin, channel);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Serial connection successful");
  
  for (int i=0; i<4; i++){
    setupLed(RGBW_pins[i], i);
  }

  ble.begin(); //Startup the bluetooth server
  NimBLEDevice::getAdvertising()->start(0);
}


long int timeInSeconds = 78060;
// 86400 seconds in a day
// 9 AM -> 32400
// 9 PM -> 75600

void loop() {

  while(timeInSeconds<32400){
    delay(1000);
    timeInSeconds++;
  }


  for (int iSec=1; iSec<256; iSec++){
    for(int iLED=0; iLED<4; iLED++){
        ledcWrite(iLED, iSec);
    }
    delay(1000);
    timeInSeconds++;
  }

  while(timeInSeconds<75600){
    delay(1000);
    timeInSeconds++;
  }

  for (int iSec=255; iSec>-1; iSec--){
    for(int iLED=0; iLED<4; iLED++){
        ledcWrite(iLED, iSec);
    }
    delay(1000);
    timeInSeconds++;
  }

  while(timeInSeconds<86400){
    delay(1000);
    timeInSeconds++;
  }

  timeInSeconds = 0;
}