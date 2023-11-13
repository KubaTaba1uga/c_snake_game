#include "../../../interfaces/std_lib_interface.h"
#include "../../controller.h"
#include "../../controller_type.h"

#include <stdlib.h>

// TO-DO init proxy before creating controller private
// TO-DO make relation between controller & proxy
// TO-DO make stdin proxy singleton
controller_ptr init_controller_local(controller_ptr controller) {
  set_controller_type(controller, CONTROLLER_LOCAL);
  set_controller_private(controller, NULL);

  return controller;
}

void destroy_controller_local_private(controller_ptr controller) {
  app_free(controller);
}
