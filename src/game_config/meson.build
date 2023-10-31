game_config_sources = files(['game_config.h', 
                           'game_type.h',
                           'game_size.h', 
                           'game_difficulty.h',
                          ])
game_config_sources += global_sources

subdir('_private')

game_config_module = shared_library(
  'game_config_module',
  game_config_sources,
  link_with: [user_module, interfaces_module, utils_module]
)

app_modules += [game_config_module]
