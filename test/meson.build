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

test_dependencies = [logging_dep, unity_dependency, cmock_dependency]

cmock_gen_runner = generator(
  find_program(_scripts / 'create_runner.rb'),
  output: '@BASENAME@_Runner.c',
  arguments: ['@INPUT@', '@OUTPUT@'],
)

cmock_gen_mock = generator(
   find_program(_scripts / 'create_mock.rb'),
   output: ['mock_@BASENAME@.c', 'mock_@BASENAME@.h', '@PLAINNAME@'],
   arguments: ['@INPUT@', '@BUILD_DIR@'],
)

# Required by generators
_interfaces = join_paths(_src, 'interfaces')
_interfaces_dir = include_directories(_interfaces)
app_src_dirs += [_interfaces_dir]

std_lib_mock = cmock_gen_mock.process(std_lib_interface_header)

###############
# SUBDIRS
###############
subdir('test_cmock.d')
subdir('game_config')
