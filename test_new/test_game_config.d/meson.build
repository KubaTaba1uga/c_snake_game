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
   cmock_gen_runner.process(test_game_type_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    game_config_module,
    proj_config_module,
  ],
)

test('test_game_type', test_game_type_exe)

##################################
# TEST GAME DIFFICULTY
##################################
test_game_difficulty_file = files('test_game_difficulty.c')

test_game_difficulty_exe = executable('test_game_difficulty',
  sources: [
   test_game_difficulty_file,
   cmock_gen_runner.process(test_game_difficulty_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    game_config_module,
    proj_config_module,
  ],
)

test('test_game_difficulty', test_game_difficulty_exe)

##################################
# TEST GAME SIZE
##################################
test_game_size_file = files('test_game_size.c')

test_game_size_exe = executable('test_game_size',
  sources: [
   test_game_size_file,
   cmock_gen_runner.process(test_game_size_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    game_config_module,
    proj_config_module,
  ],
)

test('test_game_size', test_game_size_exe)
