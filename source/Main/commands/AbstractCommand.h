#pragma once

#include "../Communication.h"

typedef void (*ReplyCallback) (const String & str_command);

class AbstractCommand
{
public:
  AbstractCommand() { }
  AbstractCommand(const String & str_command, ReplyCallback reply_callback)
    : str_command(str_command), reply_callback(reply_callback) { }

  virtual String class_name() const = 0;
  virtual String description() const { return ""; }

  virtual void run() = 0;
  virtual AbstractCommand * make(const String & str_command, ReplyCallback reply_callback) = 0;

  void reply(const String & result) {
    assert(reply_callback);
    reply_callback(result);
  }

  void set_reply_callback(ReplyCallback reply_callback) {
    this->reply_callback = reply_callback;
  }

  static String extract_target_command(const String & str_command) {
    const int start = String("AT+").length();
    const int index = str_command.indexOf("+", start);
    return str_command.substring(start, index);
  }

  // no_arg starts at 0 for the first argument
  static String extract_arg(int no_arg, const String & str_command) {
    no_arg++;
    int count = 0, start = 0;
    int end = String("AT+").length();
    do {
      // LOG("start:" + String(start, DEC));
      // LOG("end:" + String(end, DEC));
      start = end + 1;
      end = str_command.indexOf("+", start);
      count++;
    } while (count <= no_arg);
    String result =  str_command.substring(start, end < 0 ? str_command.length() : end);
    // LOG("\"" + result + "\"");
    return result;
  }

protected:
  String str_command;
  ReplyCallback reply_callback;
};
