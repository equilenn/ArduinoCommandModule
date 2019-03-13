#pragma once

#include "PinManager.h"

class Hardware
{
public:
  static void setup() {
    pinMode(PIN(UNOCARD_LED), OUTPUT);
  }

  static void turn_led_off() {
    digitalWrite(PIN(UNOCARD_LED), LOW);
  }

  static void turn_led_on() {
    digitalWrite(PIN(UNOCARD_LED), HIGH);
  }

  static int status() {
    return digitalRead(PIN(UNOCARD_LED));
  }
};
