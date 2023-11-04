##################################
# TEST GAME CONFIG
##################################
test_game_config_file = files('test_game_config.c')

test_game_config_exe = executable('test_game_config',
  sources: [
    test_game_config_file,
    std_lib_mock,
    cmock_gen_runner.process(test_game_config_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    test_utils_module,
    game_config_module,
    proj_config_module,
  ],
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ],
)

test('test_game_config', test_game_config_exe)

##################################
# TEST GAME TYPE
##################################
test_game_type_file = files('test_game_type.c')

test_game_type_exe = executable('test_game_type',
  sources: [
   test_game_type_file,
   std_lib_mock,
   cmock_gen_runner.process(test_game_type_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    test_utils_module,
    game_config_module,
    proj_config_module,
  ],
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ],
)

test('test_game_type', test_game_type_exe)

