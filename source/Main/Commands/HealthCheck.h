
#pragma once

class HealthCheck : public AbstractCommand
{
public:
  HealthCheck() : AbstractCommand() { }
  HealthCheck(const String & str_command, ReplyCallback reply_callback)
    : AbstractCommand(str_command, reply_callback) { }

  virtual String class_name() const override { return "HealthCheck"; }
  virtual String description() const override { return "Is your heart beating ?"; }

  virtual void run() override {
    LOG(class_name());
    reply("AT+OK");
  };

  virtual AbstractCommand * make(const String & str_command, ReplyCallback reply_callback) override {
    return new HealthCheck(str_command, reply_callback);
  };
};
