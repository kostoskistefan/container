project(
  'container',
  'c',
  version: '1.0.0',
  license: 'MIT',
  default_options: [
    'default_library=static'
  ],
)

buildtype = 'release'

install_headers('include/container.h')
inc = include_directories('include')

container_lib = library(
  'container',
  'source/container.c',
  include_directories: inc,
  install: true,
)

container_dep = declare_dependency(
  include_directories: inc, 
  link_with: container_lib,
)

pkg = import('pkgconfig')
pkg.generate(container_lib)
