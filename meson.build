project(
  'falling_sand',
  'cpp',
)

cmake = import('cmake')

raylib_subproject = cmake.subproject('raylib-cpp')

raylib_dependency = raylib_subproject.dependency('raylib')
raylib_cpp_dependency = raylib_subproject.dependency('raylib-cpp')

executable(
  'falling_sand',
  sources: [
    'src/cell.cpp',
    'src/main.cpp',
    'src/sandbox.cpp',
  ],
  dependencies: [raylib_dependency, raylib_cpp_dependency],
)
