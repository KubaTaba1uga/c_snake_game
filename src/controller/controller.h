#ifndef _controller_h
#define _controller_h

#include "controller_type.h"

/*******************************************************************************
 *   API
 ******************************************************************************/
typedef struct controller *controller_ptr;

controller_ptr create_controller(controller_type_t type);
void destroy_controller(controller_ptr controller);

#endif
