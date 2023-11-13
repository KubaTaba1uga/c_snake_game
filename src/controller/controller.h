#ifndef _controller_h
#define _controller_h

#include "controller_type.h"

/*******************************************************************************
 *   API
 ******************************************************************************/
typedef struct controller *controller_ptr;

controller_ptr create_controller(controller_type_t type);
void destroy_controller(controller_ptr controller);

controller_type_t get_controller_type(controller_ptr controller);
void set_controller_type(controller_ptr controller, controller_type_t type);

void *get_controller_private(controller_ptr controller);
void set_controller_private(controller_ptr controller, void *private);

#endif
