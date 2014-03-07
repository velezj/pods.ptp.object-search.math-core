
#include "roots.hpp"
#include <limits>
#include <boost/math/tools/roots.hpp>
#include <iostream>



namespace math_core {

  //======================================================================

  bool find_zero_crossing_range
  ( const std::function<double(const double&)>& f,
    double& lower,
    double& upper,
    const double& eps_tolerance )
  {
    lower = 0.49 * std::numeric_limits<double>::lowest();
    upper = 0.49 * std::numeric_limits<double>::max();
    return find_zero_crossing_range_with_guess
      (f, lower, upper, eps_tolerance ); 
  }

  //======================================================================

  bool find_zero_crossing_range_with_guess
  ( const std::function<double(const double&)>& f,
    double& lower,
    double& upper,
    const double& eps_tolerance )
  {
    // evaluate function at ends
    double f_lower = f(lower);
    double f_upper = f(upper);

    // std::cout << "zc[" << lower << "," << upper << "]("
    // 	      << f_lower << "," << f_upper << ")"
    // 	      << std::endl;
      

    // we are done if they have different signs
    if( f_lower * f_upper < 0 
	&& std::isfinite(f_lower)
	&& std::isfinite(f_upper) ) {
      return true;
    }

    // if the range is too small, then we cannot find a zero
    // crossing within it
    if( (upper - lower) < eps_tolerance ) {
      return false;
    }

    // ok, divide the range into three ranges and recurse
    double mid = lower + (upper - lower) / 2;
    double lower_mid = lower + (mid - lower) / 2;
    double upper_mid = mid + (upper - mid) / 2;
    
    // check ranges starting from the central range,
    // since this is recursive this is really a depth-first
    // search
    bool res = false;
    double check_lower;
    double check_upper;

    // lower_mid -> upper-mid
    check_lower = lower_mid;
    check_upper = upper_mid;
    res = find_zero_crossing_range_with_guess
      (f,check_lower,check_upper);
    if( res ) {
      lower = check_lower;
      upper = check_upper;
      return res;
    }
    
    // lower -> mid
    check_lower = lower;
    check_upper = mid;
    res = find_zero_crossing_range_with_guess
      (f,check_lower,check_upper);
    if( res ) {
      lower = check_lower;
      upper = check_upper;
      return res;
    }

    // mid -> upper
    check_lower = mid;
    check_upper = upper;
    res = find_zero_crossing_range_with_guess
      (f,check_lower,check_upper);
    if( res ) {
      lower = check_lower;
      upper = check_upper;
      return res;
    }
    
    // no luck!
    return false;
  }

  //======================================================================

  bool find_root
  ( const std::function<double(const double&)>& f,
    const size_t& eps_tol_bits,
    const size_t& max_iter,
    double& lower,
    double& upper )
  {
    
    // ok, since no guess ,first try to find a szero crossing
    // then find a root within it
    bool res = find_zero_crossing_range( f, lower, upper, exp(eps_tol_bits) );
    if( !res )
      return false;
    
    // use the zero crossing range as a guess
    return find_root_with_guess( f, eps_tol_bits, max_iter, lower, upper );
  }

  //======================================================================

  bool find_root_with_guess
  ( const std::function<double(const double&)>& f,
    const size_t& eps_tol_bits,
    const size_t& max_iter,
    double& lower,
    double& upper )
  {
    boost::uintmax_t max_iters = max_iter;
    boost::math::tools::eps_tolerance<double> tol( eps_tol_bits );
    std::pair<double,double> result =
      boost::math::tools::toms748_solve
      ( f, lower, upper, tol, max_iters );

    // setup return range
    lower = result.first;
    upper = result.second;
    
    // we could not find a root if we hit
    // max iterations, otherwise we did!
    if( max_iters >= max_iter ) {
      return false;
    } else {
      return true;
    }
  }

  //======================================================================

  bool
  find_integer_root
  ( const std::function<double(const double&)>& f,
    const size_t& max_iter,
    long& root )
  {
    // ok, since no guess ,first try to find a szero crossing
    // then find a root within it
    double lower, upper;
    bool res = find_zero_crossing_range( f, lower, upper );
    if( !res )
      return false;
    
    // use the zero crossing range as a guess
    return find_integer_root_with_guess( f, max_iter, lower, upper, root );
  }

  //======================================================================

  bool
  find_integer_root_with_guess
  ( const std::function<double(const double&)>& f,
    const size_t& max_iter,
    const double& lower,
    const double& upper,
    long& root )
  {
    boost::uintmax_t max_iters = max_iter;
    boost::math::tools::equal_nearest_integer tol;
    std::pair<double,double> result =
      boost::math::tools::toms748_solve
      ( f, lower, upper, tol, max_iters );
    
    // we could not find a root if we hit
    // max iterations, otherwise we did!
    if( max_iters >= max_iter ) {
      return false;
    } else {
      root = static_cast<long>(result.first);
      return true;
    }
  }

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
