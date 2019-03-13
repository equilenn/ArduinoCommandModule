#pragma once

#define PIN(x) PinManager::getPin(x)

#include "Hash.h"

enum ePin
{
  UNOCARD_LED,
  DHT_SENSOR_PIN,
  RELAY_PIN,
  BLUETOOTH_TX,
  BLUETOOTH_RX,
  ANALOG_TEMPERATURE
};

class PinManager
{
public:
  PinManager()
  {
    // LiquidScreen : 7, 8, 9, 10, 11, 12
    pins.insert(UNOCARD_LED, LED_BUILTIN); // Pin 13
    pins.insert(DHT_SENSOR_PIN, 2);
    pins.insert(RELAY_PIN, 3);
    pins.insert(BLUETOOTH_RX, 5);
    pins.insert(BLUETOOTH_TX, 6);

    pins.insert(ANALOG_TEMPERATURE, A0);
  }

  static int getPin(ePin pin)
  {
    static PinManager self;
    return self.pins.value(pin);
  }

private:
  Hash<ePin, int> pins;
};
