#include "../../../interfaces/std_lib_interface.h"
#include "../../controller_type.h"
#include "../../user_value.h"
#include "../controller_private.h"
#include "stream_proxy.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static stream_proxy_ptr stream_proxy = NULL;

typedef struct {
  user_value_t user_value;
  const char *string;
} key_mapping;

typedef struct {
  stream_proxy_ptr stdin_proxy;
  size_t keys_mapping_i;
} controller_local_private;

static key_mapping keys_mappings[][4] = {
    {
        {.user_value = UP, .string = "w"},
        {.user_value = DOWN, .string = "s"},
        {.user_value = LEFT, .string = "a"},
        {.user_value = RIGHT, .string = "d"},
    },
    {
        {.user_value = UP, .string = "8"},
        {.user_value = DOWN, .string = "5"},
        {.user_value = LEFT, .string = "4"},
        {.user_value = RIGHT, .string = "6"},
    },
};
static stream_proxy_ptr create_stdin_proxy(void);

controller_ptr init_controller_local(controller_ptr controller) {
  static size_t counter = 0;

  // Do not allow more controllers then there are configured key bindings.
  if (counter > sizeof(keys_mappings) / sizeof(key_mapping))
    return NULL;

  stream_proxy_ptr stdin_proxy = create_stdin_proxy();
  if (!stdin_proxy)
    return NULL;

  controller_local_private *private =
      app_malloc(sizeof(controller_local_private));
  if (!private)
    return NULL;

  private->stdin_proxy = stdin_proxy;
  private->keys_mapping_i = counter;

  counter++;

  set_controller_type(controller, CONTROLLER_LOCAL);
  set_controller_private(controller, &private);

  return controller;
}

void destroy_controller_local(controller_ptr controller) {
  controller_local_private *private = get_controller_private(controller);

  app_free(controller);
  app_free(private);
  destroy_stream_proxy(stream_proxy);

  stream_proxy = NULL;
}

/* char *read_controller_local(controller_ptr controller) { */
/*   controller_local_private *private = get_controller_private(controller); */
/*   stream_proxy_ptr stdin_proxy = private->stdin_proxy; */

/*   char buffer[get_length_proxy(stdin_proxy)]; */
/*   char *received; */

/*   received = read_stream_proxy(stdin_proxy, buffer); */
/*   if (!received) */
/*     return NULL; */

/*   // TO-DO translate buffer values to keys */
/* } */
/* controller_ptr flush_controller_local(controller_ptr controller) {} */

stream_proxy_ptr create_stdin_proxy(void) {
  if (!stream_proxy)
    stream_proxy = create_stream_proxy(stdin);

  return stream_proxy;
}
