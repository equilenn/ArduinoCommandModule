#pragma once

#include "CommandHelper.h"
#include "Hardware.h"

class LedControl
{
public:
  static void run(const String & str_command, ReplyCallback reply) {
    const String & arg = CommandHelper::extract_arg(0, str_command);

    if (arg == "ON") {
      Hardware::turn_led_on();
      reply("AT+OK");
    }
    else if (arg == "OFF") {
      Hardware::turn_led_off();
      reply("AT+OK");
    }
    else
      reply("AT+UC");
}
};