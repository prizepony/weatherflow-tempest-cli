project('tempest-cli', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

project_description = 'CLI tool for the Weatherflow Tempest API'

inc_dirs = [
  'include',
  '/opt/homebrew/include'
]

boost_dep = dependency('boost', modules : ['program_options','log'])

executable('tempest-cli',
           'src/main.cpp',
           include_directories : [ inc_dirs ],
           dependencies : [ boost_dep ],
           install : false)
