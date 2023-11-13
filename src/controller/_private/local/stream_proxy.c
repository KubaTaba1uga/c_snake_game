#include <ar_list.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

#include "../../../interfaces/std_lib_interface.h"
#include "../../../proj_config/error.h"
#include "stream_proxy.h"

struct stream_proxy {
  FILE stream;

  bool not_read;
  bool not_flushed;
};

stream_proxy_ptr create_stream_proxy(FILE stream) {
  stream_proxy_ptr proxy;

  proxy = app_malloc(sizeof(struct stream_proxy));

  if (!proxy) {
    errno = ERROR_OOM;
    return NULL;
  }

  proxy->stream = stream;
  proxy->not_read = true;
  proxy->not_flushed = true;

  return proxy;
}

void destroy_stream_proxy(stream_proxy_ptr stream_proxy) {
  app_free(stream_proxy);
}

void flush_stream_proxy(stream_proxy_ptr stream_proxy) {}
