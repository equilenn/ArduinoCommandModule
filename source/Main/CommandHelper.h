#pragma once

class CommandHelper
{
public:
  static String extract_target_command(const String &str_command)
  {
    const int start = String("AT+").length();
    const int index = str_command.indexOf("+", start);
    return str_command.substring(start, index);
  }

  static String extract_whole_command(const String &str_command)
  {
    const int start = String("AT+").length();
    const int index = str_command.indexOf("+", start);
    return str_command.substring(index + 1, str_command.length());
  }

  // no_arg starts at 0 for the first argument
  static String extract_arg(int no_arg, const String &str_command)
  {
    no_arg++;
    int count = 0, start = 0;
    int end = String("AT+").length();
    do
    {
      start = end + 1;
      end = str_command.indexOf("+", start);
      count++;
    } while (count <= no_arg);
    String result = str_command.substring(start, end < 0 ? str_command.length() : end);
    return result;
  }
};
