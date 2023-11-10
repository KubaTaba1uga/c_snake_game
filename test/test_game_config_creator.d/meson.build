subdir('test_cli.d')

##################################
# TEST CREATE GAME CONFIG AUTO
##################################
test_create_game_config_auto_file = files('test_create_game_config_auto.c')

test_create_game_config_auto_exe = executable('test_create_game_config_auto',
  sources: [
    test_create_game_config_auto_file,
    std_lib_mock,
    cmock_gen_runner.process(test_create_game_config_auto_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    test_utils_module,
    game_config_creator_module,
  ],
)

test('test_create_game_config_auto', test_create_game_config_auto_exe)
