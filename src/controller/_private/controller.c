#include "../controller.h"
#include "../../interfaces/std_lib_interface.h"
#include "../controller_type.h"

#include <stdlib.h>

struct controller {
  controller_type_t type;

  void *private;
};

controller_ptr create_controller(controller_type_t type) {
  controller_ptr controller;

  controller = app_malloc(sizeof(struct controller));

  if (!controller) {
    // TO-DO log msg
    // TO-DO set errno
    return NULL;
  }

  controller->type = type;
  controller->private = NULL;

  return controller;
}

void destroy_controller(controller_ptr controller) { app_free(controller); }

controller_type_t get_controller_type(controller_ptr controller) {
  return controller->type;
}
void set_controller_type(controller_ptr controller, controller_type_t type) {
  controller->type = type;
}

void *get_controller_private(controller_ptr controller) {
  return controller->private;
}
void set_controller_private(controller_ptr controller, void *private) {
  controller->private = private;
};
