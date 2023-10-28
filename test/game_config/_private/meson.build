root = join_paths('..', '..', '..')
src = join_paths(root, 'src')

interfaces = join_paths(src, 'interfaces')
user = join_paths(src, 'user')
game_config = join_paths(src, 'game_config')
game_config_private = join_paths(game_config, '_private')

test_game_config_name = 'test_game_config.c'

test_game_config_src = files([test_game_config_name, 
                              user / 'user_type.h',
                              game_config / 'game_type.h',
                              game_config / 'game_size.h',
                              game_config / 'game_difficulty.h',
                              game_config_private / 'game_config.c',
                              ])

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
                        game_config_private],
  dependencies: test_dependencies,
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ]
)

test('test_game_config', test_game_config_exe)
