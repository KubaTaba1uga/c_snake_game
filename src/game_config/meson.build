game_config_sources = files('game_config.h', 
                           'game_size.h', 
                           'game_difficulty.h',
                           'user_type.h',
                           )

subdir('_private')

game_config_links = [
  interfaces_module,
  proj_config_module
]

game_config_deps = declare_dependency(
  link_with: game_config_links
)

game_config_module = static_library(
  'game_config_module',
  game_config_sources,
  dependencies: game_config_deps,
  name_prefix: '',
)

app_modules += game_config_module
