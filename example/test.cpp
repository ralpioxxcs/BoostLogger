#include "BoostLogger.hpp"

using namespace SimpleLogger;

int main() {

  LOG(GET_LOGGER, TRACE) << "This is trace log";
  LOG(GET_LOGGER, DEBUG) << "This is debug log";
  LOG(GET_LOGGER, WARNING) << "This is warning log";
  LOG(GET_LOGGER, INFO) << "This is info log";

  return 0;
}