cmake_minimum_required(VERSION 2.6.0)

# pull in the pods macros. See cmake/pods.cmake for documentation
set(POD_NAME math-core)
include(cmake/pods.cmake)

# automatically build LCM types.  This also defines a number of CMake
# variables, see cmake/lcmtypes.cmake for details
include(cmake/lcmtypes.cmake)
lcmtypes_build()


#set(CMAKE_CXX_FLAGS "-std=c++0x -pedantic -Wall -O2 -g")
#set(CMAKE_CXX_FLAGS "-std=c++0x -pedantic -Wall -O0 -g3")

add_definitions( -std=c++0x -pedantic -Wall )
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")


# math-core library
add_library( math-core SHARED
  src/io.cpp
  src/geom.cpp
  src/matrix.cpp
  src/utils.cpp
  src/extrema.cpp
  )
pods_install_headers( 
  src/geom.hpp
  src/io.hpp
  src/matrix.hpp
  src/utils.hpp
  src/extrema.hpp
  src/math_function.hpp
  DESTINATION
  math-core )
pods_use_pkg_config_packages(math-core gsl lcmtypes_math-core eigen3 boost-1.51.0 )
pods_install_libraries( math-core )
pods_install_pkg_config_file(math-core
    CFLAGS
    LIBS -lmath-core
    REQUIRES gsl eigen3 boost-1.51.0
    VERSION 0.0.1)


# add the test subdirectory
add_subdirectory( test )