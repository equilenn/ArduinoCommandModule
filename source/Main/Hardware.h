#pragma once

class Hardware
{
public:
  static void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
  }

  static void turn_led_off() {
    digitalWrite(LED_BUILTIN, LOW);
  }

  static void turn_led_on() {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  static int status() {
    return digitalRead(LED_BUILTIN);
  }
};
