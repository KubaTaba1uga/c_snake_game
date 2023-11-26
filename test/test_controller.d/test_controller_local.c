#include "../utils/controller_test_utils.h"
#include "controller/_private/local/controller_local.c"
#include "controller/controller.h"
#include "controller/controller_type.h"
#include "controller/user_value.h"
#include "mock_std_lib_interface.h"
#include "proj_config/constant.h"
#include "unity.h"
#include <chr_list.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char user_input[] = {'W', 'W', 'W', 'W', 'W', 'S',
                           'A', 'D', 'S', 'S', 's'};
stream_proxy_ptr stream_proxy_mock;
controller_local_private *private_mock;
controller_ptr local_controller_mock;
FILE *tmp_file;

FILE *create_tmpfile(size_t n, char values[n]) {
  FILE *file;
  size_t i;

  file = tmpfile();
  if (!file)
    TEST_FAIL_MESSAGE("Unable to open temporary file");

  for (i = 0; i < n; i++) {
    fputc(values[i], file);
  }
  rewind(file);

  return file;
}

void setUp() {

  stream_proxy = NULL;
  counter = 0;

  stream_proxy_mock = create_stream_proxy_mock();
  local_controller_mock = create_local_controller_mock();
  private_mock = get_controller_private(local_controller_mock);

  tmp_file =
      create_tmpfile(sizeof(user_input) / sizeof(char), (char *)user_input);

  keys_mappings = create_key_mappings();
}

void tearDown() {
  destroy_stream_proxy_mock(stream_proxy_mock);
  destroy_local_controller_mock(local_controller_mock);
  destroy_keys_mapping();

  fclose(tmp_file);
}

void test_create_controller_local_success() {
  controller_ptr controller;
  controller_local_private *private;

  app_malloc_ExpectAndReturn(controller_expected_size, local_controller_mock);
  controller = create_controller(CONTROLLER_LOCAL);

  TEST_ASSERT_NOT_NULL(controller);

  app_malloc_ExpectAndReturn(stream_proxy_expect_size, stream_proxy_mock);
  app_malloc_ExpectAndReturn(local_controller_private_expected_size,
                             private_mock);

  private = (controller_local_private *)get_controller_private(controller);
  TEST_ASSERT_NULL(private);

  controller = init_controller_local(controller);

  TEST_ASSERT_NOT_NULL(controller);

  private = (controller_local_private *)get_controller_private(controller);

  TEST_ASSERT_NOT_NULL(private);
  TEST_ASSERT_NOT_NULL(private->stdin_proxy);
}

void test_create_controller_local_multiple_counter() {
  controller_ptr controller;
  controller_local_private *private;
  size_t i;

  for (i = 0; i < 2; i++) {
    app_malloc_ExpectAndReturn(controller_expected_size, local_controller_mock);
    controller = create_controller(CONTROLLER_LOCAL);

    if (i == 0)
      app_malloc_ExpectAndReturn(stream_proxy_expect_size, stream_proxy_mock);

    app_malloc_ExpectAndReturn(local_controller_private_expected_size,
                               private_mock);
    controller = init_controller_local(controller);

    TEST_ASSERT_NOT_NULL(controller);

    private = (controller_local_private *)get_controller_private(controller);

    TEST_ASSERT_NOT_NULL(private);
    TEST_ASSERT_EQUAL(i, private->keys_mapping_i);
  }
}

void test_read_controller_local_success_default_0(void) {
  controller_ptr controller;
  controller_local_private *private;
  user_value_t received;
  void *no_err;

  /* Test prep */
  app_malloc_ExpectAndReturn(controller_expected_size, local_controller_mock);
  controller = create_controller(CONTROLLER_LOCAL);

  TEST_ASSERT_NOT_NULL(controller);

  app_malloc_ExpectAndReturn(stream_proxy_expect_size, stream_proxy_mock);
  app_malloc_ExpectAndReturn(local_controller_private_expected_size,
                             private_mock);

  private = (controller_local_private *)get_controller_private(controller);
  TEST_ASSERT_NULL(private);

  // Add stream to proxy
  stream_proxy = create_stream_proxy(tmp_file);
  // Load data from stream to proxy
  no_err = flush_stream_proxy(stream_proxy);
  TEST_ASSERT_TRUE(no_err);

  controller = init_controller_local(controller);
  TEST_ASSERT_NOT_NULL(controller);

  /* Test logic */
  received = read_controller_local(controller);

  TEST_ASSERT_EQUAL(DOWN, received);
}

void test_read_controller_local_default_1(void) {
  const char user_input[] = {'z', '4', '2', '8', 'z', 'z'};

  FILE *file;
  controller_ptr controller;
  user_value_t received;
  void *no_err;

  /* Test prep */
  app_malloc_ExpectAndReturn(controller_expected_size, local_controller_mock);
  controller = create_controller(CONTROLLER_LOCAL);

  TEST_ASSERT_NOT_NULL(controller);

  app_malloc_ExpectAndReturn(stream_proxy_expect_size, stream_proxy_mock);
  app_malloc_ExpectAndReturn(local_controller_private_expected_size,
                             private_mock);

  // Write user input to stream
  file = create_tmpfile(sizeof(user_input) / sizeof(char), (char *)user_input);
  // Add stream to proxy
  stream_proxy = create_stream_proxy(file);
  // Load data from stream to proxy
  no_err = flush_stream_proxy(stream_proxy);
  fclose(file);

  TEST_ASSERT_TRUE(no_err);

  counter = 1;
  controller = init_controller_local(controller);
  TEST_ASSERT_NOT_NULL(controller);

  /* Test logic */
  received = read_controller_local(controller);

  TEST_ASSERT_EQUAL(UP, received);
}

void test_read_controller_local_success_no_mapped_keys(void) {
  const char user_input[] = {'k', 'S', 'j', 'r', '8', '9', 'x'};

  FILE *file;
  controller_ptr controller;
  user_value_t received;
  void *no_err;

  /* Test prep */
  app_malloc_ExpectAndReturn(controller_expected_size, local_controller_mock);
  controller = create_controller(CONTROLLER_LOCAL);

  TEST_ASSERT_NOT_NULL(controller);

  app_malloc_ExpectAndReturn(stream_proxy_expect_size, stream_proxy_mock);
  app_malloc_ExpectAndReturn(local_controller_private_expected_size,
                             private_mock);

  // Write user input to stream
  file = create_tmpfile(sizeof(user_input) / sizeof(char), (char *)user_input);
  // Add stream to proxy
  stream_proxy = create_stream_proxy(file);
  // Load data from stream to proxy
  no_err = flush_stream_proxy(stream_proxy);
  fclose(file);

  TEST_ASSERT_TRUE(no_err);

  controller = init_controller_local(controller);
  TEST_ASSERT_NOT_NULL(controller);

  /* Test logic */
  received = read_controller_local(controller);

  TEST_ASSERT_EQUAL(ENUM_INVALID, received);
}
