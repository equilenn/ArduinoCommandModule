
#include "PinManager.h"

class AnalogTemperature
{
public:
  static AnalogTemperature &instance()
  {
    static AnalogTemperature self;
    return self;
  }

  static void setup()
  {
    AnalogTemperature &self = instance();
  }

  static float get_temp_celcius()
  {
    int analog_value = analogRead(PIN(ANALOG_TEMPERATURE));
    double tempK = log(10000.0 * ((1024.0 / analog_value - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK)) * tempK);
    float tempC = tempK - 273.15;
    // float tempF = (tempC * 9.0)/ 5.0 + 32.0;
    return tempC;
  }

private:
  AnalogTemperature()
  {
  }
};
