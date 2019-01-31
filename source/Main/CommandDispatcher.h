#pragma once

#include "SerialCommunication.h"

typedef void (*CommandCallback) (String str_command);

#define CommandDispatcherInstance CommandDispatcher::instance()

class CommandDispatcher
{
private:
  CommandDispatcher() {
  }

public:
  static CommandDispatcher & instance() {
    static CommandDispatcher self;
    return self;
  }

  static void process_command(String str_command) {
    LOG("Received Command: " + str_command);
    if (CommandDispatcherInstance.is_known_command(str_command)) {
      CommandCallback callback = CommandDispatcherInstance.get_callback(str_command);
      assert(callback);
      callback(str_command);
    }
    else
      LOG("ATKO:\"" + str_command + "\"");
  }

  void register_command(const String & command, CommandCallback callback) {
    registered_commands.insert(command, callback);
  }

  bool is_known_command(const String & str_command) {
    return registered_commands.contains(str_command);
  }

  CommandCallback get_callback(const String & str_command) {
    return registered_commands.value(str_command, nullptr);
  }

private:
  Hash<String, CommandCallback> registered_commands;
};
