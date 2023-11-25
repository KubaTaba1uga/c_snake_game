#include "../utils/controller_test_utils.h"
#include "controller/_private/local/stream_proxy.c"
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

void tearDown() {
  destroy_stream_proxy_mock(stream_proxy_mock);
  fclose(tmp_file);
}

void test_create_stream_proxy_success(void) {
  stream_proxy_ptr stream_proxy;

  app_malloc_ExpectAndReturn(stream_proxy_expect_size, stream_proxy_mock);

  stream_proxy = create_stream_proxy(tmp_file);

  TEST_ASSERT_EQUAL(stream_proxy->stream, tmp_file);
  TEST_ASSERT_NULL(stream_proxy->data);
  TEST_ASSERT_EQUAL(true, stream_proxy->not_read);
}

void test_flush_stream_data_success(void) {
  stream_proxy_ptr stream_proxy;
  char recived;
  size_t i;

  app_malloc_ExpectAndReturn(stream_proxy_expect_size, stream_proxy_mock);

  stream_proxy = create_stream_proxy(tmp_file);

  TEST_ASSERT_NULL(stream_proxy->data);

  stream_proxy->not_read = false;

  stream_proxy = flush_stream_proxy(stream_proxy);

  TEST_ASSERT_NOT_NULL(stream_proxy);
  TEST_ASSERT_NOT_NULL(stream_proxy->data);
  TEST_ASSERT_EQUAL(sizeof(user_input) / sizeof(char),
                    chr_length(stream_proxy->data));
  TEST_ASSERT_TRUE(stream_proxy->not_read);

  for (i = 0; i < sizeof(user_input) / sizeof(char); i++) {
    TEST_ASSERT_EQUAL(CHR_SUCCESS, chr_get(stream_proxy->data, i, &recived));
    TEST_ASSERT_EQUAL(user_input[i], recived);
  }
}

void test_read_stream_data_success(void) {
  stream_proxy_ptr stream_proxy;
  char *recived;

  app_malloc_ExpectAndReturn(stream_proxy_expect_size, stream_proxy_mock);

  stream_proxy = create_stream_proxy(tmp_file);

  TEST_ASSERT_NULL(stream_proxy->data);

  stream_proxy->not_read = false;

  stream_proxy = flush_stream_proxy(stream_proxy);

  TEST_ASSERT_NOT_NULL(stream_proxy);
  TEST_ASSERT_NOT_NULL(stream_proxy->data);

  char buffer[chr_length(stream_proxy->data)];

  recived = read_stream_proxy(stream_proxy, buffer);

  TEST_ASSERT_NOT_NULL(recived);

  TEST_ASSERT_EQUAL_CHAR_ARRAY(user_input, recived,
                               chr_length(stream_proxy->data) - 1);
  TEST_ASSERT_FALSE(stream_proxy->not_read);
}
