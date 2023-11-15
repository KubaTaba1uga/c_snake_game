#ifndef _controller_test_utils_h
#define _controller_test_utils_h

#include "controller/_private/local/stream_proxy.h"
#include <stddef.h>

extern size_t stream_proxy_expect_size;

stream_proxy_ptr create_stream_proxy_mock(void);
void destroy_stream_proxy_mock(stream_proxy_ptr mock);

#endif
