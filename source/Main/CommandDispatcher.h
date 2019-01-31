#pragma once

#include "Communication.h"
#include "Commands/AbstractCommand.h"

typedef void (*DispatcherCallbackback) (String str_command);

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

  static void process_command(String str_command, ReplyCallback callback) {
    LOG("Received Command: " + str_command);
    const String & target = AbstractCommand::extract_target_command(str_command);
    LOG("target: " + target);

    if (CommandDispatcherInstance.is_known_command(target)) {
      AbstractCommand * command = CommandDispatcherInstance.make_command(target, str_command, callback);
      assert(command);
      command->run();
    }
    else
      LOG("AT+KO:" + str_command);
  }

  void register_command(const String & str_command, AbstractCommand * command) {
    registered_commands.insert(str_command, command);
  }

  bool is_known_command(const String & str_command) {
    return registered_commands.contains(str_command);
  }

  AbstractCommand * make_command(const String & target, const String & str_command, ReplyCallback callback) {
    AbstractCommand * maker = registered_commands.value(target, nullptr);
    assert(maker);
    return maker->make(str_command, callback);
  }

private:
  Hash<String, AbstractCommand*> registered_commands;
};
