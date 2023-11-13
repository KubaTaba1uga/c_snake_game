#include <ar_list.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../interfaces/std_lib_interface.h"
#include "../../../proj_config/error.h"
#include "l_error.h"
#include "stream_proxy.h"

static arl_ptr create_stream_data(void);
static stream_proxy_ptr reset_stream_data(stream_proxy_ptr stream_proxy);
static void destroy_stream_data(stream_proxy_ptr stream_proxy);

struct stream_proxy {
  FILE *in_stream;
  arl_ptr data;
  bool not_read;
};

stream_proxy_ptr create_stream_proxy(FILE *stream) {
  stream_proxy_ptr proxy;

  proxy = app_malloc(sizeof(struct stream_proxy));

  if (!proxy) {
    errno = ERROR_OOM;
    return NULL;
  }

  proxy->in_stream = stream;
  proxy->data = NULL;
  proxy->not_read = true;

  return proxy;
}

void destroy_stream_proxy(stream_proxy_ptr stream_proxy) {
  app_free(stream_proxy);
}

stream_proxy_ptr flush_stream_proxy(stream_proxy_ptr stream_proxy) {
  void *err;

  errno = 0;

  err = reset_stream_data(stream_proxy);

  if (err) {
    // TO-DO log message
    goto ERROR;
  }

ERROR:
  return NULL;
}

stream_proxy_ptr reset_stream_data(stream_proxy_ptr stream_proxy) {
  arl_ptr list;

  destroy_stream_data(stream_proxy);

  list = create_stream_data();

  if (!list)
    goto ERROR;

  stream_proxy->data = list;

ERROR:
  return NULL;
}

void destroy_stream_data(stream_proxy_ptr stream_proxy) {
  if (stream_proxy->data)
    arl_destroy(stream_proxy->data);

  stream_proxy->data = NULL;
}

arl_ptr create_stream_data(void) {
  const size_t DEFAULT_SIZE = 255;
  arl_ptr list;
  l_error_t err;

  err = arl_create(&list, DEFAULT_SIZE);

  if (err) {
    switch (err) {
    case L_ERROR_OUT_OF_MEMORY:
      errno = ERROR_OOM;
      goto ERROR;
    default:
      errno = ERROR_ARL;
      goto ERROR;
    }
  }

  return list;

ERROR:
  return NULL;
}
