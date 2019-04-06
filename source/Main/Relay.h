#pragma once

#include "CommandHelper.h"
#include "Communication.h"
#include "PinManager.h"

class Relay
{
public:
  static void setup()
  {
    pinMode(PIN(RELAY_01_PIN), OUTPUT);
    pinMode(PIN(RELAY_02_PIN), OUTPUT);
    turn_off(PIN(RELAY_01_PIN));
    turn_off(PIN(RELAY_02_PIN));
  }

  static void run(const String &str_command, ReplyCallback reply)
  {
    const String &noRelay = CommandHelper::extract_arg(0, str_command);
    const String &action = CommandHelper::extract_arg(1, str_command);

    int pin = noRelay == "01" ? PIN(RELAY_01_PIN) : PIN(RELAY_02_PIN);

    if (action == "ON")
    {
      turn_on(pin);
      if (reply)
        reply("AT+OK");
    }

    else if (action == "OFF")
    {
      turn_off(pin);
      if (reply)
        reply("AT+OK");
    }

    else if (action == "TGL")
    {
      toggle(pin);
      if (reply)
        reply("AT+OK");
    }

    else if (action == "ST")
    {
      int value = status(pin);
      String result;
      if (value == LOW)
        result = "RE+ON";
      else if (value == HIGH)
        result = "RE+OFF";
      else
        result = "RE+UNKNOWN";

      if (reply)
        reply(result);
    }

    else
      reply("AT+RE+UC");
  }

  static void turn_off(int pin)
  {
    LOG(pin);
    LOG("turn_off");
    digitalWrite(pin, HIGH);
  }

  static void turn_on(int pin)
  {
    LOG(pin);
    LOG("turn_on");
    digitalWrite(pin, LOW);
  }

  static void toggle(int pin)
  {
    LOG(pin);
    LOG("toggle");
    digitalWrite(pin, status(pin) == HIGH ? LOW : HIGH);
  }

  static int status(int pin)
  {
    return digitalRead(pin);
  }
};
