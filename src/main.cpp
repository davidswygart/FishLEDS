#include <Arduino.h>
#include "Ble.h"
Ble ble;

// Color Target LEDs
const int RGBW_pins[4] = {13,27,25,32};//R/G/B/W

int currentColor[4] = {200,0,0,180};
int savedColors[5][4] = {
  {0,0,0,0},
  {200,0,0,180},
  {151,161,161,255},
  {200,0,0,180},
  {0,0,0,0},
  };
// 7 AM -> 25,200
// 9 AM -> 32,400
// 2 PM -> 50,400
// 9 PM -> 75,600
// 10 PM -> 79,200
// midnight -> 86,400
unsigned long currentTimeSeconds = 33000;
unsigned long savedTimes[5] = {25200, 32400, 50400, 75600, 79200};//{25200, 32400, 50400, 75600, 79200};


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

int lastUpdateTimeSeconds = 0;
void updateTime(){
  unsigned long now = millis()/1000;
  currentTimeSeconds += now - lastUpdateTimeSeconds; 
  lastUpdateTimeSeconds = now;

  if (currentTimeSeconds > 86400){
    currentTimeSeconds = currentTimeSeconds - 86400;
  }
}


int nextTimeInd(){
  int nextTime = 0;
  for (int i=0; i<5; i++){
    if(currentTimeSeconds<savedTimes[i]){
      nextTime=i;
      break;
    }
  }
  return nextTime;
}

void updateColor(int nextColorInd){
  int timeDif = savedTimes[nextColorInd] - currentTimeSeconds;

  for (int ledInd=0; ledInd<4; ledInd++){
    int futureVal = savedColors[nextColorInd][ledInd];
    int currentVal = currentColor[ledInd];
    int colorDif = futureVal - currentVal;
    int change = colorDif / timeDif;
    currentColor[ledInd] = currentVal + change;
    ledcWrite(ledInd, currentColor[ledInd]);
    Serial.print(currentColor[ledInd]); Serial.print(" , ");
    
  }
  Serial.println();
  
}

void loop() {
  updateTime();
  int ind = nextTimeInd();
  updateColor(ind);
  delay(1000);
}