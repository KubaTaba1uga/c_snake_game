##################################
# TEST CLI UTILS
##################################
test_cli_utils_file = files('test_utils.c')

test_cli_utils_exe = executable('test_cli_utils',
  sources: [
    test_cli_utils_file,
    cmock_gen_runner.process(test_cli_utils_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    game_config_creator_module,
  ],
)

test('test_cli_utils', test_cli_utils_exe)

##################################
# TEST CREATE GAME SIZE CLI
##################################
test_create_game_size_cli_file = files('test_create_game_size_cli.c')

test_create_game_size_cli_exe = executable('test_create_game_size_cli',
  sources: [
    test_create_game_size_cli_file,
    cmock_gen_runner.process(test_create_game_size_cli_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    test_utils_module,
    game_config_creator_module,
  ],
)

test('test_create_game_size_cli', test_create_game_size_cli_exe)


##################################
# TEST CREATE GAME DIFFICULTY CLI
##################################
test_create_game_difficulty_cli_file = files('test_create_game_difficulty_cli.c')

test_create_game_difficulty_cli_exe = executable('test_create_game_difficulty_cli',
  sources: [
    test_create_game_difficulty_cli_file,
    cmock_gen_runner.process(test_create_game_difficulty_cli_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    test_utils_module,
    game_config_creator_module,
  ],
)

test('test_create_game_difficulty_cli', test_create_game_difficulty_cli_exe)


##################################
# TEST CREATE USER TYPE CLI
##################################
test_create_user_type_cli_file = files('test_create_user_type_cli.c')

test_create_user_type_cli_exe = executable('test_create_user_type_cli',
  sources: [
    test_create_user_type_cli_file,
    cmock_gen_runner.process(test_create_user_type_cli_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    test_utils_module,
    game_config_creator_module,
  ],
)

test('test_create_user_type_cli', test_create_user_type_cli_exe)

##################################
# TEST CREATE USERS TYPES CLI
##################################
test_create_users_types_cli_file = files('test_create_users_types_cli.c')

test_create_users_types_cli_exe = executable('test_create_users_types_cli',
  sources: [
    test_create_users_types_cli_file,
    cmock_gen_runner.process(test_create_users_types_cli_file),
  ],
  include_directories: app_src_dirs,
  dependencies: test_dependencies,
  link_with: [
    test_utils_module,
    game_config_creator_module,
  ],
)

test('test_create_users_types_cli', test_create_users_types_cli_exe)
