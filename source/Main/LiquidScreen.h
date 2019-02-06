#include <LiquidCrystal.h>

#include "Communication.h"
#include "CommandHelper.h"
#include "AnalogTemperature.h"
#include "DigitalTempAndHumidity.h"

class LiquidScreen
{
public:
  static LiquidScreen & instance() {
    static LiquidScreen self;
    return self;
  }

  static void setup() {
    LiquidScreen & self = instance();
  }

  static void loop() {
    LiquidScreen & self = instance();
    static int previous_time = 0;
    if (millis() / 1000 - previous_time >= 1) {
      self.refresh();
      previous_time = millis() / 1000;
    }
  }

  static void run(const String & str_command, ReplyCallback reply) {
    LiquidScreen & self = instance();
    self.refresh();
  }

  void refresh() {
    display_temperature();
    display_digital_temperature();
    display_second_from_begining();
  }

  void display_second_from_begining() {
    assert(lcd);
    lcd->setCursor(10, 0); // Cursor on column 0, row 1
    lcd->print(millis() / 1000);
  }

  void display_temperature() {
    assert(lcd);
    float temp = AnalogTemperature::get_temp_celcius();
    lcd->setCursor(0, 0); // Cursor on column 0, row 1
    lcd->print("T: " + String(temp, 2) + "C      ");
  }

  void display_digital_temperature() {
    LOG("display_digital_temperature");
    DigitalTempAndHumidity & controller = DigitalTempAndHumidity::instance();

    assert(lcd);
    lcd->setCursor(0, 1);
    lcd->print("T:" + String(controller.get_temp()) + "C");
    lcd->setCursor(8, 1);
    lcd->print("H:" + String(controller.get_humidity()) + "%");
  }

private:
  LiquidScreen() {
    lcd = new LiquidCrystal(7, 8, 9, 10, 11, 12);
    lcd->begin(16, 2); // l’écran dispose de 16 colonnes et 2 lignes
    lcd->print("Hello, World!");
  }

  LiquidCrystal * lcd;
};
