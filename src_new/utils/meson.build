utils_sources = files(
  'std_lib_utils.c', 'std_lib_utils.h',
  'logging_utils.c', 'logging_utils.h',
  'str_utils.c', 'str_utils.h',  
)

utils_module = library(
  'utils_module',
  utils_sources,
  dependencies: [logging_dep],
  name_prefix: ''
)


