#pragma once

typedef void (*ReplyCallback) (const String & result);
typedef void (*DispatcherCallback) (String str_command, ReplyCallback callback);

#define CommunicationInstance Communication::instance()
#define LOG(data) Serial.println(data)

class Communication
{
private:
  Communication() {
    cache_command.reserve(200);
    cache_command = "";

    Serial.begin(9600);
  }

public:
  static Communication & instance() {
    static Communication self;
    return self;
  }

  void set_callback(DispatcherCallback callback) {
      this->callback = callback;
  }

  void read_serial_data() {
    while (Serial.available()) {
      char inChar = (char)Serial.read();

      if (inChar == '\n')
        process_command();
      else if (inChar != '\r')
        cache_command += inChar;
    }
  }

  static void write_data(const String & data) {
    Serial.println(data);
  }

private:
  void process_command() {
    assert(callback);
    callback(cache_command, Communication::write_data);
    cache_command = "";
  }

private:
  String cache_command;
  DispatcherCallback callback;
};

void serialEvent() {
  CommunicationInstance.read_serial_data();
}
