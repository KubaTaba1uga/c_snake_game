/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>
#include <stdlib.h>

// Test framework
#include "controller/_private/local/stream_proxy.h"
#include "controller/controller.h"
#include "mock_std_lib_interface.h"
#include <unity.h>

// App
#include "controller/_private/controller.c"
#include "controller/_private/controller_private.h"
#include "controller/_private/local/controller_local.c"
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

void destroy_stream_proxy_mock(stream_proxy_ptr mock) { free(mock); }

size_t controller_expected_size = 0;
size_t local_controller_private_expected_size = 0;

controller_ptr create_local_controller_mock(void) {
  controller_local_private *private_mock;
  controller_ptr controller_mock;

  local_controller_private_expected_size = sizeof(controller_local_private);
  controller_expected_size = sizeof(struct controller);

  private_mock = malloc(local_controller_private_expected_size);
  if (!private_mock)
    TEST_FAIL_MESSAGE(
        "Unable to allocate memory for controller local private data.");

  controller_mock = malloc(controller_expected_size);
  if (!controller_mock) {
    TEST_FAIL_MESSAGE("Unable to allocate memory for local controller.");
  }

  controller_mock->private = private_mock;

  return controller_mock;
}

void destroy_local_controller_mock(controller_ptr controller_mock) {
  void *private = get_controller_private(controller_mock);
  free(private);
  free(controller_mock);
}
