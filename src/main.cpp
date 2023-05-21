#include <Arduino.h>

const int RGB_pins[4] = {32,25,27,13};//W/B/G/R
const int RGB_leds[4] = {0,1,2,3};

void blink(int channel){
  for (int i=100; i<255; i++){
    ledcWrite(channel, i);
    delay(50);
  }

  delay(1000);

  for (int i=255; i>100; i--){
    ledcWrite(channel, i);
    delay(50);
  }

    // ledcWrite(channel, 255); //write each led high then low as a debug check
    // delay(7000);
    ledcWrite(channel, 0); //write each led high then low as a debug check
    delay(200);
}

void setupLed(int pin, int channel){
    pinMode(pin, OUTPUT);
    ledcSetup(channel, 5000, 8); //frequeny 5000, 8 bit
    ledcAttachPin(pin, channel);
    //blink(channel);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Serial connection successful");
  
  int numberOfTargetLeds = sizeof(RGB_pins)/sizeof(RGB_pins[0]);
  for (int i=0; i<numberOfTargetLeds; i++){
    setupLed(RGB_pins[i], RGB_leds[i]);
  }


  ledcWrite(0, 255);
  ledcWrite(1, 127);
  ledcWrite(2, 127);
  ledcWrite(3, 127);
}

void loop() {
  // int numberOfTargetLeds = sizeof(RGB_pins)/sizeof(RGB_pins[0]);
  // for (int i=0; i<numberOfTargetLeds; i++){
  //   blink(RGB_leds[i]);
  // }


}