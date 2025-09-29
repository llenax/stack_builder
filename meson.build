project('stack_builder', 'c',
  version : '0.1',
  default_options : [
    'warning_level=3',   # roughly like -Wall
    'buildtype=debug'     # -g
  ]
)

cc = meson.get_compiler('c')

srcs = files(
  'src/main.c',
  'src/game.c',
  'src/entity.c',
  'src/camera.c',
  'src/gamestate.c',
  'src/math.c'
)

raylib_dep = dependency('raylib', required: true)

exe = executable('main',
  srcs,
  dependencies : [raylib_dep],
  link_args : ['-lm'],
  install : false,
  build_by_default : true
)

# optional run target
run_target('run',
  command : [exe],
  depends : exe,
  env : ['LD_LIBRARY_PATH=' + meson.project_source_root() / 'raylib/lib']
)
