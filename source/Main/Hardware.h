#pragma once

class Hardware
{
public:
  static void setup() {
    LOG("SETUP");
    pinMode(LED_BUILTIN, OUTPUT);
  }

  static void turn_led_off() {
    LOG("OFF");
    digitalWrite(LED_BUILTIN, LOW);
  }

  static void turn_led_on() {
    LOG("ON");
    digitalWrite(LED_BUILTIN, HIGH);
  }

  static int status() {
    LOG("STATUS");
    return digitalRead(LED_BUILTIN);
  }
};
