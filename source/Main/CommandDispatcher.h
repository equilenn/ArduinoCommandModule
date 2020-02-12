#pragma once

#include "Communication.h"
#include "CommandHelper.h"

typedef void (*CommandCallback)(const String &str_command, ReplyCallback reply);

#define CommandDispatcherInstance CommandDispatcher::instance()

class CommandDispatcher
{
private:
  CommandDispatcher()
  {
  }

public:
  static CommandDispatcher &instance()
  {
    static CommandDispatcher self;
    return self;
  }

  static void process_command(const String &str_command, ReplyCallback reply_callback)
  {
    LOG("Received Command: " + str_command);
    const String &target = CommandHelper::extract_target_command(str_command);

    if (CommandDispatcherInstance.is_known_command(target))
    {
      CommandCallback command = CommandDispatcherInstance.registered_commands.value(target, nullptr);
      assert(command);
      command(str_command, reply_callback);
    }
    else
      LOG("AT+UT" + str_command);
  }

  void register_command(const String &target, CommandCallback callback)
  {
    registered_commands.insert(target, callback);
  }

  bool is_known_command(const String &target)
  {
    return registered_commands.contains(target);
  }

private:
  Hash<String, CommandCallback> registered_commands;
};
