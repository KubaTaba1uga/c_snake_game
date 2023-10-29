root = join_paths('..', '..', '..')
src = join_paths(root, 'src')

interfaces = join_paths(src, 'interfaces')
user = join_paths(src, 'user')
utils = join_paths(src, 'utils')
game_config = join_paths(src, 'game_config')
game_config_private = join_paths(game_config, '_private')
create_game_config = join_paths(game_config_private, 'create_game_config')

test_utils = ['utils.h', 'utils.c']


# Game config test file
test_game_config_name = 'test_game_config.c'

test_game_config_src = files([test_game_config_name, 
                              user / 'user_type.h',
                              game_config / 'game_type.h',
                              game_config / 'game_size.h',
                              game_config / 'game_difficulty.h',
                              game_config_private / 'game_config.c',
                              ] + test_utils) 

test_game_config_exe = executable('test_game_config',
  sources: [
   test_game_config_src,
   cmock_gen_runner.process(test_game_config_name),
   cmock_gen_mock.process(interfaces / 'std_lib_interface.h'),
  ],
  include_directories: [src,
                        user,
                        interfaces,
                        game_config,
                        game_config_private,
                        ],
  dependencies: test_dependencies,
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ]
)

test('test_game_config', test_game_config_exe)


# Create game config from cli test file
test_create_game_config_cli_name = 'test_p_create_game_config_from_cli.c'

test_create_game_config_cli_src = files([test_create_game_config_cli_name,
                                         game_config_private / 'game_config.c',
                                         game_config_private / '_p_game_config.h',
                                         create_game_config / '_p_create_game_config_from_cli.c',
                                         utils / 'logging_utils.c',
                                         utils / 'logging_utils.h',
                                        ] + test_utils)

test_create_game_config_cli_exe = executable('test_create_game_config_cli',
  sources: [
   test_create_game_config_cli_src,
   cmock_gen_runner.process(test_create_game_config_cli_name),
   cmock_gen_mock.process(interfaces / 'std_lib_interface.h'),
  ],
  include_directories: [src,
                        user,
                        utils,
                        interfaces,
                        game_config,
                        game_config_private,
                        create_game_config
                       ],
  dependencies: test_dependencies,
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ]
)
test('test_create_game_config_cli', test_create_game_config_cli_exe)
