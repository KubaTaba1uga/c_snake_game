##################################
# SETUP
##################################
test_utils = [join_paths('..', 'utils.h'), join_paths('..', 'utils.c')]



##################################
# TEST CREATE GAME CONFIG
##################################
test_create_game_config_cli_name = 'test_p_create_game_config_from_cli.c'

test_create_game_config_cli_src = files([test_create_game_config_cli_name] + test_utils)

test_create_game_config_cli_objects = [game_config_module.extract_all_objects(recursive: true)]
test_create_game_config_cli_objects +=  utils_module.extract_all_objects()

test_create_game_config_cli_exe = executable('test_create_game_config_cli',
  sources: [
   test_create_game_config_cli_src,
   std_lib_mock,
   cmock_gen_runner.process(test_create_game_config_cli_name),
  ],
  objects: test_create_game_config_cli_objects,
  include_directories: [app_src_dirs],
  dependencies: test_dependencies,
  link_args: [
     # allows static functions testing
    '-zmuldefs',
  ]
)
test('test_create_game_config_cli', test_create_game_config_cli_exe)

##################################
# TEST CREATE SIZE
##################################
test_create_size_cli_name = 'test_p_create_size_cli.c'

test_create_size_cli_src = files([test_create_size_cli_name] + test_utils)
  
test_create_size_cli_objects = [game_config_module.extract_all_objects(recursive: true)]
test_create_size_cli_objects +=  utils_module.extract_all_objects()

test_create_size_cli_exe = executable('test_create_size_cli',
  sources: [
   test_create_size_cli_src,
   std_lib_mock,
   cmock_gen_runner.process(test_create_size_cli_name),
  ],
  objects: test_create_size_cli_objects,  
  include_directories: [app_src_dirs],
  dependencies: test_dependencies,
  link_args: [
     # allows static functions testing
    '-zmuldefs',
  ]
)
test('test_create_size_cli', test_create_size_cli_exe)

##################################
# TEST CREATE DIFFICULTY
##################################
test_create_difficulty_cli_name = 'test_p_create_difficulty_cli.c'

test_create_difficulty_cli_src = files([test_create_difficulty_cli_name] + test_utils)
  
test_create_difficulty_cli_objects = [game_config_module.extract_all_objects(recursive: true)]
test_create_difficulty_cli_objects +=  utils_module.extract_all_objects()

test_create_difficulty_cli_exe = executable('test_create_difficulty_cli',
  sources: [
   test_create_difficulty_cli_src,
   std_lib_mock,
   cmock_gen_runner.process(test_create_difficulty_cli_name),
  ],
  objects: test_create_difficulty_cli_objects,  
  include_directories: [app_src_dirs],
  dependencies: test_dependencies,
  link_args: [
     # allows static functions testing
    '-zmuldefs',
  ]
)
test('test_create_difficulty_cli', test_create_difficulty_cli_exe)
