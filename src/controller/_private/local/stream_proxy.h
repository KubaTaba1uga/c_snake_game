#ifndef _stream_proxy_h
#define _stream_proxy_h

#include <stdio.h>

/*******************************************************************************
 *   API
 ******************************************************************************/
typedef struct stream_proxy *stream_proxy_ptr;

stream_proxy_ptr create_stream_proxy(FILE stream);
void destroy_stream_proxy(stream_proxy_ptr stream_proxy);

#endif
