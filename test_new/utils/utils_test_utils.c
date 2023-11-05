
#include "utils_test_utils.h"
#include "utils/logging_utils.h"

#ifndef LOGGING_ENABLED
#define LOGGING_ENABLED 0
#else
#define LOGGING_ENABLED 1
#endif

void set_up_loggers(void) {
  if (LOGGING_ENABLED)
    init_loggers();
}

void tear_down_loggers(void) { destroy_loggers(); }
