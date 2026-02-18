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
  'test/'
]

foreach t : test_sources
  testname = t.split('/')[-1].split('.')[0]
  exe = executable(testname, t,
    link_with : npio
  )
  test(testname, exe)
endforeach