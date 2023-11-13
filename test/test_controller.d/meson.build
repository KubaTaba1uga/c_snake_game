##################################
# TESTS CONFIG
##################################
controller_tests_deps = [test_dependencies, lists_dep]

##################################
# TEST STREAM PROXY
##################################
test_stream_proxy_file = files('test_stream_proxy.c')

test_stream_proxy_exe = executable('test_stream_proxy',
  sources: [
    test_stream_proxy_file,
    std_lib_mock,
    cmock_gen_runner.process(test_stream_proxy_file),
  ],
  include_directories: app_src_dirs,
  dependencies: controller_tests_deps,
  link_with: [
    controller_module,
    test_utils_module,
  ],
  link_args: [
    # allow static functions testing
    '-zmuldefs',
  ],
)

test('test_stream_proxy', test_stream_proxy_exe)
