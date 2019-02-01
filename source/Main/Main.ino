#define __ASSERT_USE_STDERR
#include <assert.h>

#include "Hash.h"

#include "CommandDispatcher.h"
#include "Communication.h"

#include "HealthCheck.h"
#include "LedControl.h"

void health_check(String c) { LOG("Heart is beating"); }
void on(String c) { digitalWrite(LED_BUILTIN, HIGH); }
void off(String c) { digitalWrite(LED_BUILTIN, LOW); }

// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
  LOG("Assertion failed in: " + String(__file));
  LOG("Function: " + String(__func));
  LOG("[Line " + String(__lineno, DEC) + "]: " + String(__sexp));
  LOG("Program terminated");
  FLUSH_LOG();
  abort();
}

void setup() {
  CommandDispatcher::instance();
  Communication::instance();
  CommunicationInstance.set_callback(&CommandDispatcher::process_command);

  CommandDispatcherInstance.register_command("HC", HealthCheck::run);
  CommandDispatcherInstance.register_command("LED", LedControl::run);
  // CommandDispatcherInstance.register_command("AT+ON", on);
  // CommandDispatcherInstance.register_command("AT+OFF", off);
  // LOG(CommandDispatcherInstance.is_known_command("AT+HC") ? "OUI" : "NON");

  LOG("AT+READY");
}

void loop() {
}
