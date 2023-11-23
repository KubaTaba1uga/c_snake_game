// TO-DO add logging for chr_list errors
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
  // Not read is required to disallow proxy users
  //  flushing not read data. It would lead to traces.
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

/* Especially usefull when allocating buffer for read_stream_proxy.
 */
size_t get_length_proxy(stream_proxy_ptr stream_proxy) {
  return chr_length(stream_proxy->data);
}

/* Buffer has to be bigger than list's length, otherwise behaviour is undefined.
 */
char *read_stream_proxy(stream_proxy_ptr stream_proxy, char buffer[]) {
  chr_error err;

  err = chr_slice(stream_proxy->data, 0, chr_length(stream_proxy->data) - 1,
                  buffer);
  if (err) {
    errno = ERROR_ARL;
    return NULL;
  }

  stream_proxy->not_read = false;

  return buffer;
}

// Substitute data with new data
stream_proxy_ptr flush_stream_proxy(stream_proxy_ptr stream_proxy) {
  void *recived;
  char c;
  chr_error err;

  if (stream_proxy->not_read)
    return stream_proxy;

  recived = reset_stream_data(stream_proxy);

  if (!recived) {
    // TO-DO log message
    goto ERROR;
  }

  while ((c = fgetc(stream_proxy->stream)) != EOF) {
    err = chr_append(stream_proxy->data, c);

    if (err) {
      errno = ERROR_ARL;
      goto ERROR;
    }
  }

  stream_proxy->not_read = true;

  return stream_proxy;

ERROR:
  return NULL;
}

stream_proxy_ptr reset_stream_data(stream_proxy_ptr stream_proxy) {
  chr_ptr list;

  // TO-DO clear instead of alloc/dealloc, should make code quicker. Is it true?
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
