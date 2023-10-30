root = join_paths('..', '..', '..', '..')
src = join_paths(root, 'src')

interfaces = join_paths(src, 'interfaces')
user = join_paths(src, 'user')
utils = join_paths(src, 'utils')
game_config = join_paths(src, 'game_config')
game_config_private = join_paths(game_config, '_private')
create_game_config = join_paths(game_config_private, 'create_game_config')
create_game_config_cli = join_paths(create_game_config, 'cli')

test_utils = [join_paths('..', 'utils.h'), join_paths('..', 'utils.c')]

test_create_game_config_cli_name = 'test_p_create_game_config_from_cli.c'

test_create_game_config_cli_src = files([test_create_game_config_cli_name,
                                         create_game_config_cli / '_p_create_size_cli.c',
                                         create_game_config_cli / '_p_create_size_cli.h',
                                         create_game_config_cli / '_p_create_game_config_cli.c',
#                                         create_game_config_cli / '_p_create_game_config_cli.h',                                         
                                         game_config_private / 'game_config.c',
                                         game_config_private / '_p_game_config.h',
                                         
#                                         user / 'user_type.h',
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
                        create_game_config,
                        create_game_config_cli
                       ],
  dependencies: test_dependencies,
  link_args: [
     # allows static functions testing
    '-zmuldefs',
  ]
)
test('test_create_game_config_cli', test_create_game_config_cli_exe)
