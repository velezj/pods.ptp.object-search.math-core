
#if !defined( __MATH_CORE_EXTREMA_HPP__ )
#define __MATH_CORE_EXTREMA_HPP__


#include <boost/function.hpp>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_min.h>
#include <iostream>

namespace math_core {


  // Description:
  // Searches for a maximum in a 1D function
  template< typename T_InputDomain, typename T_OutputDomain >
  T_InputDomain
  find_max( const boost::function1<T_OutputDomain, T_InputDomain>& f,
	    const T_InputDomain& low,
	    const T_InputDomain& high,
	    const T_InputDomain& guess );

}

#endif

