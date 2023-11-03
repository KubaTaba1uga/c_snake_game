game_config_sources = files(['game_config.h', 
                           'game_type.h',
                           'game_size.h', 
                           'game_difficulty.h',
                           'user_type.h',
                            ])

subdir('_private')

game_config_module = library(
  'game_config_module',
  game_config_sources,
  link_with: [interfaces_module],
  name_prefix: ''
)
