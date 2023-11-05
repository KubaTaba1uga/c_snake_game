#include "game_config_creator/_private/cli/utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unity.h>

inline void fill_value(size_t size, char dest[size], const char *src, char c);

void fill_value(size_t size, char dest[size], const char *src, char c) {

  strncpy(dest, src, size);

  if (c)
    memset(dest + strlen(dest), c, size - strlen(dest));

  dest[size - 1] = 0;
}

void test_sanitize_user_value_cut(void) {
  const size_t expected_size = 100;
  const size_t buffer_size = 500;
  const char input_value[] = "big";
  const char c = 'a';

  char expected_value[expected_size];
  char user_value[buffer_size];
  char buffer[buffer_size];
  void *received;

  fill_value(buffer_size, user_value, input_value, c);
  fill_value(expected_size, expected_value, input_value, c);
  memset(buffer, 0, buffer_size);

  received = sanitize_user_input(user_value, expected_size, buffer);

  TEST_ASSERT_NOT_NULL(received);
  TEST_ASSERT_EQUAL_STRING(expected_value, received);
}

void test_sanitize_user_value_trim_ws(void) {
  const size_t buffer_size = 100;
  const char input_value[] = "             big                   ";
  const char expected_value[] = "big";

  char buffer[buffer_size];
  void *received;

  received = sanitize_user_input((char *)input_value, buffer_size, buffer);

  TEST_ASSERT_NOT_NULL(received);
  TEST_ASSERT_EQUAL_STRING(expected_value, received);
}
