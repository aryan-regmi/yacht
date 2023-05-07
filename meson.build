project('yacht', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++14'])


# Library
# ========================================================== #
subdir('src')
yacht_lib = library(
  'yacht',
  sources,
  include_directories: []
)

# Executable
# ========================================================== #
exe = executable('yacht', 'yacht.cpp',
  link_with: yacht_lib,
  install : true)

