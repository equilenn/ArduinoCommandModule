
#include "CommandDispatcher.h"
#include "Communication.h"

void health_check(String c) { LOG("Heart is beating"); }
CommandDispatcher::instance().register_command("ATHC", health_check);
