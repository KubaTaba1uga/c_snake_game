controller_sources = files('controller.h', 
                           'controller_type.h',
                           )

subdir('_private')

controller_links = [
  interfaces_module,
  proj_config_module
]

controller_deps = declare_dependency(
  link_with: controller_links,
  dependencies: lists_dep
)

controller_module = static_library(
  'controller_module',
  controller_sources,
  dependencies: controller_deps,
  name_prefix: '',
)

app_modules += controller_module
