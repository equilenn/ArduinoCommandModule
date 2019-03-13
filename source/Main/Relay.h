#pragma once

#include "CommandHelper.h"
#include "Hardware.h"

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

    else if (arg == "ST")
    {
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

  static void turn_off()
  {
    LOG("OFF");
    Hardware::turn_led_off();
    digitalWrite(PIN(RELAY_PIN), LOW);
  }

  static void turn_on()
  {
    LOG("ON");
    Hardware::turn_led_on();
    digitalWrite(PIN(RELAY_PIN), HIGH);
  }

  static int status()
  {
    LOG("STATUS");
    return digitalRead(PIN(RELAY_PIN));
  }
};
