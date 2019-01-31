
#pragma once

typedef void (*SerialCallback) (String str_command);

#define SerialCommunicationInstance SerialCommunication::instance()
#define LOG(data) Serial.println(data)

class SerialCommunication
{
private:
  SerialCommunication() {
    cache_command.reserve(200);
    cache_command = "";

    Serial.begin(9600);
  }

public:
  static SerialCommunication & instance() {
    static SerialCommunication self;
    return self;
  }

  void set_callback(SerialCallback callback) {
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

private:
  void process_command() {
    assert(callback);
    callback(cache_command);
    cache_command = "";
  }

private:
  String cache_command;
  SerialCallback callback;
};

void serialEvent() {
  SerialCommunicationInstance.read_serial_data();
}
