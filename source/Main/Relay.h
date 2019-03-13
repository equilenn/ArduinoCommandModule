#pragma once

#include "CommandHelper.h"

#include "PinManager.h"

class Relay
{
public:
  static void setup() {
    pinMode(PIN(RELAY_PIN), OUTPUT);
  }

  static void run(const String & str_command, ReplyCallback reply) {
    const String & arg = CommandHelper::extract_arg(0, str_command);

    if (arg == "ON")
    {
      turn_on();
      reply("AT+OK");
    }

    else if (arg == "OFF")
    {
      turn_off();
      reply("AT+OK");
    }

    else if (arg == "TGL") {
      toggle();
      reply("AT+OK");
    }

    else if (arg == "ST")
    {
      int value = status();
      if (value == LOW)
        reply("LED+ON");
      else if (value == HIGH)
        reply("LED+OFF");
      else
        reply("LED+UNKNOWN");
    }

    else
      reply("AT+UC");
  }

  static void turn_off()
  {
    digitalWrite(PIN(RELAY_PIN), HIGH);
  }

  static void turn_on()
  {
    digitalWrite(PIN(RELAY_PIN), LOW);
  }

  static void toggle()
  {
    digitalWrite(PIN(RELAY_PIN), status() == HIGH ? LOW : HIGH);
  }

  static int status()
  {
    return digitalRead(PIN(RELAY_PIN));
  }
};
