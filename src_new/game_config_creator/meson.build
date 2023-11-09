game_config_creator_sources = files()

subdir('_private')

game_config_creator_links = [game_config_module]
game_config_creator_links += utils_module

game_config_creator_deps = declare_dependency(
  link_with: game_config_creator_links,
) 

game_config_creator_module = static_library(
  'game_config_creator_module',
  game_config_creator_sources,
  dependencies: game_config_creator_deps,
  name_prefix: ''
)

app_modules += game_config_creator_module
