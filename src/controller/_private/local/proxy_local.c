#include <stdbool.h>
#include <stdio.h>

#include "../../../interfaces/std_lib_interface.h"
#include "proxy_local.h"

struct stream_proxy {
  FILE stream;
  bool not_read;
};

proxy_local_ptr create_proxy_local(FILE stream) {

  app_malloc(sizeof(stream_proxy))
}
