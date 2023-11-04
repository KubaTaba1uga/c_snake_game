##################################
# TEST GAME CONFIG
##################################
test_game_config_file = files('test_game_config.c')

test_game_config_src = test_game_config_file

test_game_config_exe = executable('test_game_config',
  sources: [
   test_game_config_src,
   std_lib_mock,
   cmock_gen_runner.process(test_game_config_file),
  ],
  include_directories: [app_src_dirs],
  dependencies: test_dependencies,
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ],
  link_with: [
    test_utils_module,
    game_config_module,
    interfaces_module,
    proj_config_module
  ]
)

test('test_game_config', test_game_config_exe)

