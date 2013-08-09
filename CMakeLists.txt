cmake_minimum_required(VERSION 2.6.0)

# pull in the pods macros. See cmake/pods.cmake for documentation
set(POD_NAME p2l-math-core)
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
add_library( p2l-math-core SHARED
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
pods_use_pkg_config_packages(p2l-math-core gsl-1.16 lcmtypes_p2l-math-core eigen3 boost-1.54.0 )
pods_install_libraries( p2l-math-core )
pods_install_pkg_config_file(p2l-math-core
    CFLAGS
    LIBS -lp2l-math-core
    REQUIRES gsl-1.16 eigen3 boost-1.54.0
    VERSION 0.0.1)


# add the test subdirectory
add_subdirectory( test )
