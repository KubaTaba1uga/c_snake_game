# Template for new C projects
# ******************************************************************************
# *    Project
# ******************************************************************************
project('c_snake_game', 'c',
         version: '0.0.1',
	 meson_version: '>=1.0.1',
	 default_options: [
            'werror=true',
            'c_std=c11',
         ],
)

# ******************************************************************************
# *    Logging
# ******************************************************************************
cmake = import('cmake')

opt_var = cmake.subproject_options()
# by default stumpless uses c11, which makes all implicit declaration to gnu library
#  compile errors. Overriding c11 to gnu11 fixes the errors.
opt_var.set_override_option('c_std', 'gnu11')
opt_var.set_override_option('werror', 'false')

logging_proj = cmake.subproject('stumpless', options: opt_var)
logging_dep = logging_proj.dependency('stumpless')

# ******************************************************************************
# *    Lists
# ******************************************************************************
char_lists_proj = subproject('char_lists', default_options: ['enable_tests=false',
                                                             'arl_type=char',
                                                             'arl_prefix=chr'])
char_lists_dep = char_lists_proj.get_variable('arl_lib_dep')

# ******************************************************************************
# *    App
# ******************************************************************************
subdir('src')
main = executable('main', link_with: main_module)

# ******************************************************************************
# *    Tests
# ******************************************************************************
subdir('test')

