/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>
#include <stdlib.h>

// Test framework
#include "controller/_private/local/stream_proxy.h"
#include "mock_std_lib_interface.h"
#include <unity.h>

// App
#include "controller/_private/local/stream_proxy.c"

/*******************************************************************************
 *    API
 ******************************************************************************/

size_t stream_proxy_expect_size = 0;

stream_proxy_ptr create_stream_proxy_mock(void) {
  stream_proxy_ptr mock;

  stream_proxy_expect_size = sizeof(struct stream_proxy);

  mock = malloc(stream_proxy_expect_size);

  if (!mock)
    TEST_FAIL_MESSAGE("Unable to allocate memory for stream proxy.");

  return mock;
}
