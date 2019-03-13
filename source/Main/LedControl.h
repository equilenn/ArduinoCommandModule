#pragma once

#include "CommandHelper.h"
#include "PinManager.h"

class LedControl
{
public:
  static void run(const String & str_command, ReplyCallback reply) {
    const String & arg = CommandHelper::extract_arg(0, str_command);

    if (arg == "ON") {
      turn_on();
      reply("AT+OK");
    }

    else if (arg == "OFF") {
      turn_off();
      reply("AT+OK");
    }

    else if (arg == "TGL") {
      toggle();
      reply("AT+OK");
    }

    else if (arg == "ST") {
      int value = status();
      if (value == HIGH)
        reply("LED+ON");
      else if (value == LOW)
        reply("LED+OFF");
      else
        reply("LED+UNKNOWN");
    }

    else
      reply("AT+UC");
  }

  static void setup() {
    pinMode(PIN(UNOCARD_LED), OUTPUT);
  }

  static void turn_off() {
    digitalWrite(PIN(UNOCARD_LED), LOW);
  }

  static void turn_on() {
    digitalWrite(PIN(UNOCARD_LED), HIGH);
  }

  static void toggle() {
    digitalWrite(PIN(UNOCARD_LED), status() == HIGH ? LOW : HIGH);
  }

  static int status() {
    return digitalRead(PIN(UNOCARD_LED));
  }

};
