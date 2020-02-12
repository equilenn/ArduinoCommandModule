#define __ASSERT_USE_STDERR
#include <assert.h>

#include "Hash.h"

#include "CommandDispatcher.h"
#include "Communication.h"
#include "Bluetooth.h"

#include "HealthCheck.h"
#include "LedControl.h"
#include "LiquidScreen.h"
#include "DigitalTempAndHumidity.h"
#include "ButtonManager.h"
#include "Relay.h"

// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp)
{
  LOG("Assertion failed in: " + String(__file));
  LOG("Function: " + String(__func));
  LOG("[Line " + String(__lineno, DEC) + "]: " + String(__sexp));
  LOG("Program terminated");
  FLUSH_LOG();
  abort();
}

void setup()
{
  CommandDispatcher::instance();
  Communication::instance();
  CommunicationInstance.set_callback(&CommandDispatcher::process_command);

  Bluetooth::instance();
  BluetoothInstance.set_callback(&CommandDispatcher::process_command);

  LedControl::setup();
  // DigitalTempAndHumidity::setup();
  // LiquidScreen::setup();
  // ButtonManager::setup();
  Relay::setup();

  CommandDispatcherInstance.register_command("BT", Bluetooth::run);
  // CommandDispatcherInstance.register_command("HC", HealthCheck::run);
  CommandDispatcherInstance.register_command("LED", LedControl::run);
  // CommandDispatcherInstance.register_command("LS", LiquidScreen::run);
  // CommandDispatcherInstance.register_command("RE", Relay::run);

  LOG("AT+READY");
}

void loop()
{
  Bluetooth::loop();
  LiquidScreen::loop();
  ButtonManager::loop();
  // DigitalTempAndHumidity::loop();
}
