
#include "gsl_utils.hpp"
#include <iostream>
#include <cstdlib>


namespace math_core {


  //=========================================================================

  void gsl_ignore_representation_errors( const char* reason,
					 const char* file,
					 int line,
					 int gsl_errno )
  {
    // ignore ERANGE errors
    if( gsl_errno == GSL_ERANGE ) {
      return;
    }
    
    // print error to stderr and abort()
    std::cerr << "GSL ERROR: " << reason 
	      << "  AT: {" << file 
	      << ", line: " << line << " }"
	      << "  [No: " << gsl_errno << "]" << std::endl;
    abort();
  }

  //=========================================================================

  gsl_scoped_error_function_t
  gsl_error_handler_scope( gsl_error_handler_t* handler )
  {
    return gsl_scoped_error_function_t( handler );
  }
  
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================


}
