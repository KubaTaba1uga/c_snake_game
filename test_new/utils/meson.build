test_utils_sources = files('game_config_test_utils.h', 'game_config_test_utils.c')

test_utils_module = library('test_utils_module',
  sources: [
   test_utils_sources,
   std_lib_mock,
  ],
  include_directories: [app_src_dirs],
  dependencies: test_dependencies,
  link_with: [game_config_module],
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ],
  name_prefix: ''
)


