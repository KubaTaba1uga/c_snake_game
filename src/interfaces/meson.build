std_lib_interface_header = files('std_lib_interface.h')

interfaces_sources = std_lib_interface_header + files(
  'std_lib_interface.c'
)

interfaces_module = shared_library(
  'interfaces_module',
  interfaces_sources
)

app_modules += [interfaces_module]
