#pragma once

class Hardware
{
public:
  static void turn_led_on() {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  static void turn_led_off() {
    digitalWrite(LED_BUILTIN, LOW);
  }
};
