#include <Arduino.h>
#include "globals.h"
#include "Ble.h"
Ble ble;

void setupLed(int pin, int channel){
    pinMode(pin, OUTPUT);
    ledcSetup(channel, 5000, 8); //frequeny 5000, 8 bit
    ledcAttachPin(pin, channel);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Serial connection successful");
  
  int numberOfTargetLeds = sizeof(RGBW_pins)/sizeof(RGBW_pins[0]);
  for (int i=0; i<numberOfTargetLeds; i++){
    setupLed(RGBW_pins[i], i);
  }

  ble.begin(); //Startup the bluetooth server
  NimBLEDevice::getAdvertising()->start(0);
}

void loop() {
}