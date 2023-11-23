#include "../../../interfaces/std_lib_interface.h"
#include "../../controller_type.h"
#include "../controller_private.h"
#include "stream_proxy.h"

#include <stdio.h>
#include <stdlib.h>

stream_proxy_ptr get_stdin_proxy(void) {
  // Kindo singleton pattern
  static stream_proxy_ptr stream_proxy = NULL;

  if (stream_proxy)
    return stream_proxy;

  return create_stream_proxy(stdin);
}

controller_ptr init_controller_local(controller_ptr controller) {
  stream_proxy_ptr stdin_proxy = get_stdin_proxy();
  if (!stdin_proxy)
    return NULL;

  set_controller_type(controller, CONTROLLER_LOCAL);
  set_controller_private(controller, stdin_proxy);

  return controller;
}

void destroy_controller_local(controller_ptr controller) {
  app_free(controller);
  destroy_stream_proxy(get_stdin_proxy());
}
