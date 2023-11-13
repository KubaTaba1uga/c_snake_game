proj_config_sources = files(['error.h', 'constant.h'])

subdir('_private')

proj_config_module = shared_library(
  'proj_config_module',
  proj_config_sources,
  name_prefix: ''
)

app_modules += proj_config_module
