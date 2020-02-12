#pragma once

#include "CommandHelper.h"

class HealthCheck
{
public:
  static void run(const String &str_command, ReplyCallback reply)
  {
    reply("AT+OK");
  };
};
