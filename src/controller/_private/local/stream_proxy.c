
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <chr_list.h>

#include "../../../interfaces/std_lib_interface.h"
#include "../../../proj_config/error.h"
#include "stream_proxy.h"

static chr_ptr create_stream_data(void);
static stream_proxy_ptr reset_stream_data(stream_proxy_ptr stream_proxy);
static void destroy_stream_data(stream_proxy_ptr stream_proxy);

struct stream_proxy {
  FILE *stream;
  chr_ptr data;
  bool not_read;
};

stream_proxy_ptr create_stream_proxy(FILE *stream) {
  stream_proxy_ptr proxy;

  proxy = app_malloc(sizeof(struct stream_proxy));

  if (!proxy) {
    errno = ERROR_OOM;
    return NULL;
  }

  proxy->stream = stream;
  proxy->data = NULL;
  proxy->not_read = true;

  return proxy;
}

void destroy_stream_proxy(stream_proxy_ptr stream_proxy) {
  destroy_stream_data(stream_proxy);
  app_free(stream_proxy);
}

stream_proxy_ptr flush_stream_proxy(stream_proxy_ptr stream_proxy) {
  void *recived;
  char c;

  errno = 0;

  recived = reset_stream_data(stream_proxy);

  if (!recived) {
    // TO-DO log message
    goto ERROR;
  }

  while ((c = fgetc(stream_proxy->stream)) != EOF) {
    chr_append(stream_proxy->data, c);
  }

  chr_append(stream_proxy->data, 0);

  return stream_proxy;

ERROR:
  return NULL;
}

stream_proxy_ptr reset_stream_data(stream_proxy_ptr stream_proxy) {
  chr_ptr list;

  destroy_stream_data(stream_proxy);

  list = create_stream_data();

  if (!list)
    goto ERROR;

  stream_proxy->data = list;
  stream_proxy->not_read = true;

  return stream_proxy;

ERROR:
  return NULL;
}

void destroy_stream_data(stream_proxy_ptr stream_proxy) {
  if (stream_proxy->data)
    chr_destroy(stream_proxy->data);

  stream_proxy->data = NULL;
}

chr_ptr create_stream_data(void) {
  const size_t DEFAULT_SIZE = 255;
  chr_ptr list;
  chr_error err;

  err = chr_create(&list, DEFAULT_SIZE);

  if (err) {
    switch (err) {
    case CHR_ERROR_OUT_OF_MEMORY:
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
