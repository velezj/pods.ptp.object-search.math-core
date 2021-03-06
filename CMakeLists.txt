cmake_minimum_required(VERSION 2.6.0)

# pull in the pods macros. See cmake/pods.cmake for documentation
set(POD_NAME object-search.math-core)
include(cmake/pods.cmake)

# # automatically build LCM types.  This also defines a number of CMake
# # variables, see cmake/lcmtypes.cmake for details
# include(cmake/lcmtypes.cmake)
# lcmtypes_build()


#set(CMAKE_CXX_FLAGS "-std=c++0x -pedantic -Wall -O2 -g")
#set(CMAKE_CXX_FLAGS "-std=c++0x -pedantic -Wall -O0 -g3")

#add_definitions( -std=c++0x -Wall -fdiagnostics-show-option -fPIC )
add_definitions( -std=c++0x -Wall -fdiagnostics-show-option -Wno-unused-local-typedefs -fPIC -g )
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")

option ( USE_PEDANTIC "Turn on -pendantic mode in gcc. This will spit out *lots* of warnings from lcm :-(, but hopefully none from the rest of the code" OFF)
if( USE_PEDANTIC )
    add_definitions( -pedantic )
endif (USE_PEDANTIC)



# math-core library
add_library( object-search.math-core SHARED
  src/io.cpp
  src/geom.cpp
  src/matrix.cpp
  src/utils.cpp
  src/extrema.cpp
  src/gsl_utils.cpp
  src/polynomial.cpp
  src/polynomial_fit.cpp
  src/roots.cpp
  )
pods_install_headers(
  src/types.hpp
  src/geom.hpp
  src/io.hpp
  src/matrix.hpp
  src/utils.hpp
  src/extrema.hpp
  src/math_function.hpp
  src/gsl_utils.hpp
  src/mpt.hpp
  src/polynomial.hpp
  src/polynomial_fit.hpp
  src/roots.hpp
  src/policy_number.hpp
  src/exception.hpp
  DESTINATION
  math-core )


pods_use_pkg_config_packages(object-search.math-core
  gmp-5.1.3
  gsl-1.16
  eigen3
  boost-1.54.0
  object-search.common
  nlopt-2.4.1  )
pods_install_libraries( object-search.math-core )
pods_install_pkg_config_file(object-search.math-core
    CFLAGS
    LIBS -lobject-search.math-core
    REQUIRES gsl-1.16 eigen3 boost-1.54.0 object-search.common gmp-5.1.3 nlopt-2.4.1
    VERSION 1.0.0)


# add the test subdirectory
add_subdirectory( test )
