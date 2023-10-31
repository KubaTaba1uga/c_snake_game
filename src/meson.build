app_modules = []

global_sources = files(
   'config.h', 'error.h'
)

main_sources = files('main.c')

subdir('user')
subdir('utils')
subdir('interfaces')
subdir('game_config')

main_module = shared_library(
  'main_module',
  main_sources,
  link_with: app_modules
)




