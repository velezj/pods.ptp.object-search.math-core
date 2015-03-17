

# a simple test for projections into subspaces
add_executable( object-search.math-core-test-projection
  test-projection.cpp)
pods_use_pkg_config_packages( object-search.math-core-test-projection object-search.math-core  )
pods_install_executables( object-search.math-core-test-projection )



# a simple test for extrema finding
add_executable( object-search.math-core-test-extrema
  test-extrema.cpp)
pods_use_pkg_config_packages( object-search.math-core-test-extrema object-search.math-core  )
pods_install_executables( object-search.math-core-test-extrema )


# test math_function
add_executable( object-search.math-core-test-math-function
  test-math-function.cpp)
pods_use_pkg_config_packages( object-search.math-core-test-math-function object-search.math-core  )
pods_install_executables( object-search.math-core-test-math-function )


# test polynomial
add_executable( object-search.math-core-test-polynomial
  test-polynomial.cpp)
pods_use_pkg_config_packages( object-search.math-core-test-polynomial object-search.math-core  )
pods_install_executables( object-search.math-core-test-polynomial )



# test polynomial fit
add_executable( object-search.math-core-test-polynomial-fit
  test-polynomial-fit.cpp)
pods_use_pkg_config_packages( object-search.math-core-test-polynomial-fit object-search.math-core  )
pods_install_executables( object-search.math-core-test-polynomial-fit )


# test roots
add_executable( object-search.math-core-test-roots
  test-roots.cpp)
pods_use_pkg_config_packages( object-search.math-core-test-roots object-search.math-core  )
pods_install_executables( object-search.math-core-test-roots )

# test policy number
add_executable( object-search.math-core-test-policy-number
  test-policy-number.cpp)
pods_use_pkg_config_packages( object-search.math-core-test-policy-number object-search.math-core  )
pods_install_executables( object-search.math-core-test-policy-number )




