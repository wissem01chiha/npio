# This file is part of npio library.
# menson is supported paratilly , official supported build systems are cmake and bazel
# meson.build require meson >= 0.47.0 and zlib >= 1.2.11 installed
# on host system
project('npio', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

sources = [
  'npio.c'
]

npio = library('npio', sources,
  install : true
)

test_sources = [
  'test/example.c'
]

if get_option('test').enabled()
  foreach t : test_sources
    testname = t.split('/')[-1].split('.')[0]
    exe = executable(testname, t,
      link_with : npio
    )
    test(testname, exe)
  endforeach
endif 