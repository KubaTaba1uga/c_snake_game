#ifndef _stream_proxy_h
#define _stream_proxy_h

#include <stdio.h>

/*******************************************************************************
 *   API
 ******************************************************************************/
typedef struct stream_proxy *stream_proxy_ptr;

stream_proxy_ptr create_stream_proxy(FILE *stream);
void destroy_stream_proxy(stream_proxy_ptr stream_proxy);
size_t get_length_proxy(stream_proxy_ptr stream_proxy);
char *read_stream_proxy(stream_proxy_ptr stream_proxy, char buffer[]);
stream_proxy_ptr flush_stream_proxy(stream_proxy_ptr stream_proxy);

#endif
