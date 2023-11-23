#ifndef _controller_private_h
#define _controller_private_h

#include "../controller.h"

controller_type_t get_controller_type(controller_ptr controller);
void set_controller_type(controller_ptr controller, controller_type_t type);

void *get_controller_private(controller_ptr controller);
void set_controller_private(controller_ptr controller, void *private);

#endif
