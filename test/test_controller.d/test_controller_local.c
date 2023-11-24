#include "../utils/controller_test_utils.h"
#include "controller/_private/local/controller_local.c"
#include "mock_std_lib_interface.h"
#include "unity.h"
#include <chr_list.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char user_input[] = {'W', 'W', 'W', 'W', 'W', 'S',
                           'A', 'D', 'S', 'S', 'S'};
stream_proxy_ptr stream_proxy_mock;
FILE *tmp_file;

void setUp() {
  size_t i;

  stream_proxy_mock = create_stream_proxy_mock();

  tmp_file = tmpfile();
  if (!tmp_file)
    TEST_FAIL_MESSAGE("Unable to open temporary file");

  for (i = 0; i < sizeof(user_input) / sizeof(char); i++) {
    fputc(user_input[i], tmp_file);
  }
  fseek(tmp_file, 0, SEEK_SET);
}

void tearDown() { destroy_stream_proxy_mock(stream_proxy_mock); }
