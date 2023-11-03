game_config_creator_sources = files()

subdir('_private')

game_config_creator_module = library(
  'game_config_creator_module',
  game_config_creator_sources,
  link_with: [interfaces_module, game_config_module],
  name_prefix: ''
)
