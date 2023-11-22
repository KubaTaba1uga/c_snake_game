###############
# PATHS
###############
_scripts = join_paths('..', 'scripts')
_src = join_paths('..', 'src')
_src_dir = include_directories(_src)

app_src_dirs = [_src_dir]

###############
# DEPS
###############
cmock_subproject = subproject('cmock')

unity_dependency = cmock_subproject.get_variable('unity_dep')
cmock_dependency = cmock_subproject.get_variable('cmock_dep')

test_dependencies = [unity_dependency, cmock_dependency]

cmock_gen_runner = generator(
  find_program(_scripts / 'create_runner.rb'),
  output: '@BASENAME@_Runner.c',
  arguments: ['@INPUT@', '@OUTPUT@'],
)

# Required by std_lib_mock
_interfaces = join_paths(_src, 'interfaces')
_interfaces_dir = include_directories(_interfaces)
app_src_dirs += [_interfaces_dir]


cmock_prog = find_program(_scripts / 'create_mock.rb')
std_lib_mock = custom_target('std_lib_mock',
                             output: ['mock_std_lib_interface.h', 'mock_std_lib_interface.c'],
                             input: [std_lib_interface_header],
                             command: [cmock_prog, std_lib_interface_header, '@OUTDIR@'],
                           )

###############
# SUBDIRS
###############
subdir('utils')
subdir('test_cmock.d')
subdir('test_game_config.d')
subdir('test_game_config_creator.d')
subdir('test_controller.d')
