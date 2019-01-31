
#pragma once

#include "SerialCommunication.h"

class HealthCheck
{
  String name() {
    return "HealthCheck";
  }
  String description() {
    return "Is your heart beating ?";
  }
  String process() {
    return "";
  }
}
