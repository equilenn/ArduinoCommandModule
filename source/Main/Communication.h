#pragma once

typedef void (*ReplyCallback)(const String &result);
typedef void (*DispatcherCallback)(const String &str_command, ReplyCallback reply_callback);

#define CommunicationInstance Communication::instance()
#define LOG(data) Communication::write_data(data)
#define FLUSH_LOG(data) Communication::flush_data(data)

class Communication
{
private:
  Communication()
  {
    cache_command.reserve(200);
    cache_command = "";

    Serial.begin(9600);
  }

public:
  static Communication &instance()
  {
    static Communication self;
    return self;
  }

  void set_callback(DispatcherCallback callback)
  {
    this->callback = callback;
  }

  void read_data()
  {
    while (Serial.available())
    {
      char inChar = (char)Serial.read();

      if (inChar == '\n')
        process_command();
      else if (inChar != '\r')
        cache_command += inChar;
    }
  }

  static void write_data(int value)
  {
    char buffer[25];
    sprintf(buffer, "%d", value);
    write_data(buffer);
  }

  static void write_data(const String &data)
  {
    Serial.println(data);
  }

  static void flush_data()
  {
    Serial.flush();
  }

private:
  void process_command()
  {
    assert(callback);
    callback(cache_command, Communication::write_data);
    cache_command = "";
  }

private:
  String cache_command;
  DispatcherCallback callback;
};

void serialEvent()
{
  CommunicationInstance.read_data();
}
