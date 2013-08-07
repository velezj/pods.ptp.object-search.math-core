

# a simple test for projections into subspaces
add_executable( test-projection
  test-projection.cpp)
pods_use_pkg_config_packages( test-projection math-core lcmtypes_math-core )
pods_install_executables( test-projection )



# a simple test for extrema finding
add_executable( math-core-test-extrema
  test-extrema.cpp)
pods_use_pkg_config_packages( math-core-test-extrema math-core lcmtypes_math-core )
pods_install_executables( math-core-test-extrema )


# test math_function
add_executable( math-core-test-math-function
  test-math-function.cpp)
pods_use_pkg_config_packages( math-core-test-math-function math-core lcmtypes_math-core )
pods_install_executables( math-core-test-math-function )

