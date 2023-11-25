#include "../../../interfaces/std_lib_interface.h"
#include "../../../proj_config/constant.h"
#include "../../../proj_config/error.h"
#include "../../controller_type.h"
#include "../../user_value.h"
#include "../controller_private.h"
#include "stream_proxy.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  user_value_t user_value;
  const char *string;
} key_mapping;

typedef struct {
  stream_proxy_ptr stdin_proxy;
  size_t keys_mapping_i;
} controller_local_private;

static stream_proxy_ptr stream_proxy = NULL;
static size_t counter = 0;
static size_t keys_mappings_limit = 0;
static size_t keys_mapped_amount = 0;
static key_mapping **keys_mappings = NULL;

// TO-DO initialize keys mapping dynamically, it would give user capability to
// define it's own key bindings, without need of recompilation

static stream_proxy_ptr create_stdin_proxy(void);
static user_value_t convert_mapping_to_user_value(key_mapping a_mapping,
                                                  char *string);

key_mapping **create_key_mappings(void) {
  // User should be able to define it's own key bindings,
  //   which would be used instead of default ones.
  // User should define seperate file for key bindings.
  // User can define 20 bindings, if two player are playing
  //   only first two are used.
  // TO-DO custom key bindings

  key_mapping default_keys_mappings[][4] = {
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
  size_t default_mappings_amount =
      sizeof(default_keys_mappings) / sizeof(default_keys_mappings[0]);

  keys_mappings = malloc(sizeof(default_keys_mappings));
  if (!keys_mappings) {
    errno = ERROR_OOM;
    return NULL;
  }

  keys_mappings_limit = default_mappings_amount;
  keys_mapped_amount = sizeof(default_keys_mappings[0]) / sizeof(key_mapping);

  memcpy(keys_mappings, default_keys_mappings, sizeof(default_keys_mappings));

  return keys_mappings;
}

controller_ptr init_controller_local(controller_ptr controller) {
  // Do not allow more controllers then there are configured key bindings.
  if (counter >= keys_mappings_limit)
    return NULL;

  stream_proxy_ptr stdin_proxy = create_stdin_proxy();
  if (!stdin_proxy)
    return NULL;

  controller_local_private *private =
      app_malloc(sizeof(controller_local_private));
  if (!private) {
    errno = ERROR_OOM;
    return NULL;
  }

  private->stdin_proxy = stdin_proxy;
  private->keys_mapping_i = counter;

  counter++;

  set_controller_type(controller, CONTROLLER_LOCAL);
  set_controller_private(controller, private);

  return controller;
}

void destroy_controller_local(controller_ptr controller) {
  controller_local_private *private = get_controller_private(controller);

  app_free(controller);
  app_free(private);
  destroy_stream_proxy(stream_proxy);

  stream_proxy = NULL;
}

void destroy_keys_mapping(void) {
  free(keys_mappings);
  keys_mappings = NULL;
}

user_value_t read_controller_local(controller_ptr controller) {
  controller_local_private *private = get_controller_private(controller);
  stream_proxy_ptr stdin_proxy = private->stdin_proxy;
  key_mapping *keys_mapping, a_mapping;

  char *received;
  size_t k, i;
  user_value_t tmp, user_value = ENUM_INVALID;

  flush_stream_proxy(stdin_proxy);

  char buffer[get_length_proxy(stdin_proxy)];

  received = read_stream_proxy(stdin_proxy, buffer);
  if (!received)
    return ENUM_INVALID;

  keys_mapping = keys_mappings[private->keys_mapping_i];

  // Error is here, propably copying from default mapping is fucked
  for (k = 0; k < get_length_proxy(stdin_proxy); k++) {
    for (i = 0; i < keys_mapped_amount; i++) {
      a_mapping = keys_mapping[i];

      tmp = convert_mapping_to_user_value(a_mapping, received + k);

      if (tmp != ENUM_INVALID) {
        user_value = tmp;
        break;
      }
    }
  };

  return user_value;
}

user_value_t convert_mapping_to_user_value(key_mapping a_mapping,
                                           char *string) {
  size_t mapping_value_len;
  size_t user_value_len;

  mapping_value_len = strlen(a_mapping.string);
  user_value_len = strlen(string);

  if (mapping_value_len > user_value_len)
    return ENUM_INVALID;

  if (!strncmp(a_mapping.string, string, mapping_value_len))
    return ENUM_INVALID;

  return a_mapping.user_value;
}
/* controller_ptr flush_controller_local(controller_ptr controller) {} */

stream_proxy_ptr create_stdin_proxy(void) {
  if (!stream_proxy)
    stream_proxy = create_stream_proxy(stdin);

  return stream_proxy;
}
