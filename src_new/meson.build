app_modules = []

subdir('proj_config')
subdir('utils')
subdir('interfaces')
subdir('game_config')
subdir('game_config_creator')

main_sources = files('main.c')

main_module = shared_library(
  'main_module',
  main_sources,
  link_with: app_modules
)
