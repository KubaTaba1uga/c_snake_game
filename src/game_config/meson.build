game_config_files = files(['game_config.h', 
                           'game_type.h',
                           'game_size.h', 
                           'game_difficulty.h',
                          ])

subdir('_private')

game_config_includes = [join_paths('..', 'interfaces'),
                       ]

game_config_module = shared_library(
  'game_config_module',
  game_config_files,
  include_directories: game_config_includes,
  link_with: [user_module, interfaces_module]
)
