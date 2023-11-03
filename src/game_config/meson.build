game_config_sources = files(['game_config.h', 
                           'game_type.h',
                           'game_size.h', 
                           'game_difficulty.h',
                           'create_game_config.h'
                          ])
game_config_sources += global_sources

subdir('_private')

game_config_module = library(
  'game_config',
  game_config_sources,
  link_with: [user_module, interfaces_module, utils_module],
  name_prefix: '',
  name_suffix: 'module'
             
)

app_modules += [game_config_module]
