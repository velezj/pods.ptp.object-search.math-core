

# a simple test for projections into subspaces
add_executable( p2l-math-core-test-projection
  test-projection.cpp)
pods_use_pkg_config_packages( p2l-math-core-test-projection p2l-math-core  )
pods_install_executables( p2l-math-core-test-projection )



# a simple test for extrema finding
add_executable( p2l-math-core-test-extrema
  test-extrema.cpp)
pods_use_pkg_config_packages( p2l-math-core-test-extrema p2l-math-core  )
pods_install_executables( p2l-math-core-test-extrema )


# test math_function
add_executable( p2l-math-core-test-math-function
  test-math-function.cpp)
pods_use_pkg_config_packages( p2l-math-core-test-math-function p2l-math-core  )
pods_install_executables( p2l-math-core-test-math-function )


# test polynomial
add_executable( p2l-math-core-test-polynomial
  test-polynomial.cpp)
pods_use_pkg_config_packages( p2l-math-core-test-polynomial p2l-math-core  )
pods_install_executables( p2l-math-core-test-polynomial )



# test polynomial fit
add_executable( p2l-math-core-test-polynomial-fit
  test-polynomial-fit.cpp)
pods_use_pkg_config_packages( p2l-math-core-test-polynomial-fit p2l-math-core  )
pods_install_executables( p2l-math-core-test-polynomial-fit )


# test roots
add_executable( p2l-math-core-test-roots
  test-roots.cpp)
pods_use_pkg_config_packages( p2l-math-core-test-roots p2l-math-core  )
pods_install_executables( p2l-math-core-test-roots )

# test policy number
add_executable( p2l-math-core-test-policy-number
  test-policy-number.cpp)
pods_use_pkg_config_packages( p2l-math-core-test-policy-number p2l-math-core  )
pods_install_executables( p2l-math-core-test-policy-number )




