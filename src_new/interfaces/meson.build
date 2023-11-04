std_lib_interface_header = files('std_lib_interface.h')

interfaces_sources = std_lib_interface_header + files(
  'std_lib_interface.c'
)

interfaces_module = static_library(
  'interfaces_module',
  interfaces_sources,
  name_prefix: ''
)


