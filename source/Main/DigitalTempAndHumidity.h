#pragma once

#include <SimpleDHT.h>

static const int DHT_SENSOR_PIN = 2;

class DigitalTempAndHumidity
{
public:
  static DigitalTempAndHumidity & instance() {
    static DigitalTempAndHumidity self;
    return self;
  }

  static void setup() {
    DigitalTempAndHumidity & self = instance();
  }

  static void loop() {
    DigitalTempAndHumidity & self = instance();
    static int previous_time = 0;
    if (millis() / 1000 - previous_time >= 3) {
      self.read();
      previous_time = millis() / 1000;
    }
  }

  void read() {
    byte _temp = 0, _hum = 0;

    if ( dht11.read(&_temp, &_hum, NULL) == SimpleDHTErrSuccess ) {
      // Serial.print( "read: " );
      // Serial.print( "T = " );
      // Serial.print( _temp, 1 );
      // Serial.print( " deg. C, H = " );
      // Serial.print( _hum, 1 );
      // Serial.println( "%" );
      this->temperature = (int)_temp;
      this->humidity = (int)_hum;
    }
  }

  int get_temp() {
    return temperature;
  }

  int get_humidity() {
    return humidity;
  }

private:
  int temperature;
  int humidity;

  DigitalTempAndHumidity() : dht11(DHT_SENSOR_PIN), temperature(0), humidity(0) {
  }

  SimpleDHT11 dht11;
};
