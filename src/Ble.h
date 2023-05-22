#pragma once
#include <NimBLEDevice.h>

class ServerCallbacks: public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer); //print that is connected
    void onDisconnect(NimBLEServer* pServer); //print that is disconnected
};

class LedsCallbacks: public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic* pCharacteristic); //turn on LEDs, or set flag for look to turn on LEDs
};

class Ble {
    public:
    NimBLEServer* server;
    NimBLEService* service;
    NimBLECharacteristic* leds;
    void begin();
};
