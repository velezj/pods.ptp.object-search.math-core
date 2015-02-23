
#if !defined( __MATH_CORE_roots_HPP__ )
#define __MATH_CORE_roots_HPP__

#include <functional>
#include <cstddef>


namespace math_core {

  //======================================================================

  // Description:
  // Find a range for 1d function which has a zero crossing.
  // There are two versions, one which takes an initial large range
  // and tries to shrink this range and one which assumes the maximum
  // range for the datatype double.
  // Return function returns where a zero crossing range could be found.
  //
  // The eps_tolerance is the smallest interval to be able to
  // check for a zero crossing before we give up in that interval.
  bool find_zero_crossing_range
  ( const std::function<double(const double&)>& f,
    double& lower,
    double& upper,
    const double& eps_tolerance = 1e-10);
  bool find_zero_crossing_range_with_guess
  ( const std::function<double(const double&)>& f,
    double& lower,
    double& upper,
    const double& eps_tolerance = 1e-10 );

  //======================================================================

  // Description:
  // Finds a root for the 1D function.
  // There are two versions, on which take in a range where the root
  // exists and the other which first searches for a crossing then
  // for a root.
  // Returns true if a root found, and an interval where the root exists.
  // max_iter is set to the maximum iteration reached,
  // and is used as input to choose a maximum willing to iterate.
  // eps-tol is the number of bits of tolerance wanted in the 
  // returned range for the root location.
  //
  // the with_guess variante uses the lower/upper given as an initial
  // guess of the range the root is in (and will not look elsewhere!)
  bool find_root
  ( const std::function<double(const double&)>& f,
    const size_t& eps_tol_bits,
    const size_t& max_iter,
    double& lower,
    double& upper );
  bool find_root_with_guess
  ( const std::function<double(const double&)>& f,
    const size_t& eps_tol_bits,
    const size_t& max_iter,
    double& lower,
    double& upper );
  

  //======================================================================

  // Description:
  // Find an integer root.
  // Similar to find_root but stops whenever we have reached 
  // an integer root (so the interval is the same integer!).
  bool find_integer_root
  ( const std::function<double(const double&)>& f,
    const size_t& max_iter,
    long& root );
  bool find_integer_root_with_guess
  ( const std::function<double(const double&)>& f,
    const size_t& max_iter,
    const double& lower,
    const double& upper,
    long& root);


  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================

}


#endif
