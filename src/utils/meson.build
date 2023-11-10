utils_sources = files(
  'std_lib_utils.c', 'std_lib_utils.h',
  'logging_utils.c', 'logging_utils.h',
  'str_utils.c', 'str_utils.h',  
)

utils_objects = [proj_config_module.extract_all_objects()]

utils_deps = declare_dependency(
  dependencies: [logging_dep],
)

utils_module = static_library(
  'utils_module',
  utils_sources,
  objects: utils_objects,
  dependencies: utils_deps,
  name_prefix: ''
)


app_modules += utils_module
