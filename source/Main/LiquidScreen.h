#include <LiquidCrystal.h>

#include "CommandHelper.h"
#include "AnalogTemperature.h"

class LiquidScreen
{
public:
  static LiquidScreen & instance() {
    static LiquidScreen self;
    return self;
  }

  static void setup() {
    LiquidScreen & self = instance();

    self.lcd->begin(16, 2); // l’écran dispose de 16 colonnes et 2 lignes
    self.lcd->print("Hello, World!");
  }

  static void run(const String & str_command, ReplyCallback reply) {
    LiquidScreen & self = instance();
    self.display_temperature();
  }

  void display_second_from_begining() {
    assert(lcd);
    lcd->setCursor(0, 1); // Cursor on column 0, row 1
    lcd->print(millis() / 1000);
  }

  void display_temperature() {
    assert(lcd);
    float temp = AnalogTemperature::get_temp_celcius();
    lcd->setCursor(0, 0); // Cursor on column 0, row 1
    lcd->print("Temp: " + String(temp, 2) + "C      ");
  }

private:
  LiquidScreen() {
    lcd = new LiquidCrystal(7, 8, 9, 10, 11, 12);
  }

  LiquidCrystal * lcd;
};
