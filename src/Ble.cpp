#include <NimBLEDevice.h>
#include <Arduino.h>
#include <WiFi.h>
#include "Ble.h"
#include "globals.h"

void ServerCallbacks::onConnect(NimBLEServer* pServer) {
    Serial.println("Client connected");
}

void ServerCallbacks::onDisconnect(NimBLEServer* pServer) {
    Serial.println("Client disconnected");
    NimBLEDevice::startAdvertising();
}

struct uint8_structArray {
    uint8_t vals[4];
};

void LedsCallbacks::onWrite(NimBLECharacteristic* pCharacteristic){
    uint8_structArray s = {pCharacteristic->getValue<uint8_structArray>()};

    Serial.print("LED written: red="); Serial.print(s.vals[0]);
    Serial.print("; green= ");Serial.print(s.vals[1]);
    Serial.print("; blue= ");Serial.print(s.vals[2]);
    Serial.print("; white= ");Serial.println(s.vals[3]);

    int numberOfTargetLeds = sizeof(RGBW_pins)/sizeof(RGBW_pins[0]);
    for(int i=0; i<numberOfTargetLeds; i++){
        ledcWrite(i, s.vals[i]);
    }
}

void Ble::begin(){
    NimBLEDevice::setPower(ESP_PWR_LVL_P9); //Set max power for best signal
    String devName = "FISH_" + WiFi.macAddress();
    NimBLEDevice::init(devName.c_str());
    server = NimBLEDevice::createServer();
    server->setCallbacks(new ServerCallbacks());
    service = server->createService("00000000-151b-11ec-82a8-0242ac130003");
    
    leds = service->createCharacteristic("00000001-151b-11ec-82a8-0242ac130003");
    leds->setCallbacks(new LedsCallbacks());

    bool worked = service->start();
    
    Serial.print("service started = ");
    Serial.println(worked);

    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising(); //Might be unessessary
    pAdvertising->addServiceUUID("aaaaaaaa-151b-11ec-82a8-0242ac130003"); 
}