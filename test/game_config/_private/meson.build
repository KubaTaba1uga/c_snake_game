##################################
# SETUP
##################################
test_utils = files('utils.h', 'utils.c')


##################################
# TEST GAME CONFIG
##################################
test_game_config_objects = [game_config_module.extract_all_objects(recursive: true)]
test_game_config_objects += utils_module.extract_all_objects()

test_game_config_file = files('test_game_config.c')

test_game_config_src = test_game_config_file + test_utils

test_game_config_exe = executable('test_game_config',
  sources: [
   test_game_config_src,
   std_lib_mock,
   cmock_gen_runner.process(test_game_config_file),
  ],
  objects: test_game_config_objects,
  include_directories: [app_src_dirs],
  dependencies: test_dependencies,
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ]
)

test('test_game_config', test_game_config_exe)

subdir('create_game_config')
