game_config_files = files(['game_config.h', 
                           'game_type.h',
                           'game_size.h', 
                           'game_difficulty.h',
                          ])

subdir('_private')

game_config_module = shared_library(
  'game_config_module',
  game_config_files,
  link_with: [user_module, interfaces_module, utils_module]
)
