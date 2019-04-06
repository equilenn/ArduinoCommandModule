#pragma once

#include "Hash.h"

#include "PinManager.h"
#include "Communication.h"
#include "Relay.h"

class Button
{
  public:
    Button(int index, int minAnalogValue, int maxAnalogValue, String command_str)
        : m_index(index),
          m_minAnalogValue(minAnalogValue),
          m_maxAnalogValue(maxAnalogValue),
          m_command_str(command_str)
    {
    }

    bool matchValue(int value)
    {
        return value >= m_minAnalogValue && value <= m_maxAnalogValue;
    }

    void exec()
    {
        Relay::run(m_command_str, nullptr);
    }

  private:
    int m_index;
    int m_minAnalogValue;
    int m_maxAnalogValue;
    String m_command_str;
};

class ButtonManager
{
  private:
    ButtonManager() : m_currentValue(1023),
                      shutter_up(0, 0, 50, ""),
                      shutter_down(0, 480, 550, ""),
                      ready(true)
    {
    }

    void readValue()
    {
        m_currentValue = analogRead(A5);
        // LOG(m_currentValue);

        if (shutter_up.matchValue(m_currentValue))
        {
            if (ready)
            {
                Relay::toggle(PIN(RELAY_01_PIN));
                Relay::turn_on(PIN(RELAY_02_PIN));
                ready = false;
            }
        }
        else if (shutter_down.matchValue(m_currentValue))
        {
            if (ready)
            {
                Relay::toggle(PIN(RELAY_01_PIN));
                Relay::turn_off(PIN(RELAY_02_PIN));
                ready = false;
            }
        }
        else
            ready = true;
    }

  public:
    static ButtonManager &instance()
    {
        static ButtonManager self;
        return self;
    }

    static void setup()
    {
        ButtonManager &self = instance();
    }

    static void loop()
    {
        ButtonManager &self = instance();
        static long previous_time = 0;
        if (millis() - previous_time >= 100)
        {
            self.readValue();
            previous_time = millis();
        }
    }

  private:
    int m_currentValue;
    Button shutter_up;
    Button shutter_down;

    bool ready;
};
