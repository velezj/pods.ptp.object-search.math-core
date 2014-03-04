

#if !defined( __MATH_CORE_plynomail_fit_HPP__ )
#define __MATH_CORE_plynomail_fit_HPP__

#include "matrix.hpp"
#include "polynomial.hpp"

namespace math_core {

  //====================================================================

  
  // Description:
  // Perform a least squares unqeighed fit for a given degree polynomail
  // for the data.
  // This will fill out the chi-squared result from fit as well as the 
  // covariance of the fit
  void polynomial_least_squares_fit( const size_t degree,
				     const std::vector<double>& x,
				     const std::vector<double>& y,
				     polynomial_t& poly,
				     double& chi_sq,
				     dense_matrix_t& cov );

  //====================================================================

}


#endif
