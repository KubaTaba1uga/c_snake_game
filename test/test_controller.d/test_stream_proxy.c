#include "../utils/controller_test_utils.h"
#include "controller/_private/local/stream_proxy.c"
#include "mock_std_lib_interface.h"
#include "unity.h"
#include <stddef.h>
#include <stdio.h>

stream_proxy_ptr stream_proxy_mock;
FILE *tmp_file;

void setUp() {
  stream_proxy_mock = create_stream_proxy_mock();

  tmp_file = fopen("tmp.file", "w+");
  if (!tmp_file)
    TEST_FAIL_MESSAGE("Unable to open temporary file");
}

void tearDown() { destroy_stream_proxy_mock(stream_proxy_mock); }

void test_flush_stream_data_success(void) {
  stream_proxy_ptr stream_proxy;

  app_malloc_ExpectAndReturn(stream_proxy_expect_size, stream_proxy_mock);

  stream_proxy = create_stream_proxy(tmp_file);

  flush_stream_proxy(stream_proxy);
}
