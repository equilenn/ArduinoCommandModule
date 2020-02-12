#pragma once

#include <SoftwareSerial.h>
// #include <ArduinoBlue.h>

#include "Communication.h"
#include "PinManager.h"

#define BluetoothInstance Bluetooth::instance()

class Bluetooth
{
private:
  Bluetooth() : device(PIN(BLUETOOTH_TX), PIN(BLUETOOTH_RX))
  {
    cache_command.reserve(200);
    cache_command = "";

    device.begin(9600);
  }

public:
  static Bluetooth &instance()
  {
    static Bluetooth self;
    return self;
  }

  void set_callback(DispatcherCallback callback)
  {
    this->callback = callback;
  }

  void read_data()
  {
    while (device.available())
    {
      char inChar = (char)device.read();

      if (inChar == '\n')
        process_command();
      else if (inChar != '\r')
        cache_command += inChar;
    }
  }

  static void run(const String &str_command, ReplyCallback reply)
  {
    const String &result = CommandHelper::extract_whole_command(str_command);
    instance().write_data(result);
    reply("BT: " + result);
  }

  static void write_data(const String &data)
  {
    instance().device.print(data);
  }

  static void flush_data()
  {
    instance().device.flush();
  }

  static void loop()
  {
    instance().read_data();
  }

private:
  void process_command()
  {
    LOG(cache_command);
    assert(callback);
    callback(cache_command, Bluetooth::write_data);
    cache_command = "";
  }

private:
  SoftwareSerial device;
  String cache_command;
  DispatcherCallback callback;
};
