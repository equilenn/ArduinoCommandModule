#pragma once

#include "../Hardware.h"

class LedControl : public AbstractCommand
{
public:
  LedControl() : AbstractCommand() { }
  LedControl(const String & str_command, ReplyCallback reply_callback)
    : AbstractCommand(str_command, reply_callback) { }

  virtual String class_name() const override { return "HealthCheck"; }
  virtual String description() const override { return "Is your heart beating ?"; }

  virtual void run() override {
    LOG(class_name());
    const String & arg = AbstractCommand::extract_arg(0, str_command);
    LOG(arg == "ON" ? "OUI" : "NON");
    if (arg == "ON")
      Hardware::turn_led_on();
    else
      Hardware::turn_led_off();
    reply("AT+OK");
  };

  virtual AbstractCommand * make(const String & str_command, ReplyCallback reply_callback) override {
    return new HealthCheck(str_command, reply_callback);
  };
};
