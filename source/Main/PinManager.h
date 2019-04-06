#pragma once

#define PIN(x) PinManager::getPin(x)

#include "Hash.h"

enum ePin
{
  UNOCARD_LED,
  DHT_SENSOR_PIN,
  RELAY_01_PIN,
  RELAY_02_PIN,
  BLUETOOTH_TX,
  BLUETOOTH_RX,
  ANALOG_TEMPERATURE,
  ANALOG_BUTTONS
};

class PinManager
{
public:
  PinManager()
  {
    // LiquidScreen : 7, 8, 9, 10, 11, 12
    pins.insert(UNOCARD_LED, LED_BUILTIN); // Pin 13
    pins.insert(DHT_SENSOR_PIN, 2);
    pins.insert(RELAY_01_PIN, 3);
    pins.insert(RELAY_02_PIN, 4);
    pins.insert(BLUETOOTH_RX, 5);
    pins.insert(BLUETOOTH_TX, 6);

    pins.insert(ANALOG_TEMPERATURE, A0);
    pins.insert(ANALOG_BUTTONS, A5);
  }

  static int getPin(ePin pin)
  {
    static PinManager self;
    return self.pins.value(pin);
  }

private:
  Hash<ePin, int> pins;
};
