
#if !defined( __P2L_MATH_CORE_gsl_utils_HPP__ )
#define __P2L_MATH_CORE_gsl_utils_HPP__

#include <gsl/gsl_errno.h>
#include <iostream>
#include <vector>
#include <gsl/gsl_vector.h>


namespace math_core {
  
  // Description:
  // Resets the gsl error handler at scope exit
  class gsl_scoped_error_function_t
  {
  public:
    
    gsl_scoped_error_function_t( gsl_error_handler_t* new_handler )
      : _handler( new_handler )
    {
      _old_handler = gsl_set_error_handler( _handler );
      //std::cout << "Scoping GSL error handler" << std::endl;
    }

    virtual ~gsl_scoped_error_function_t()
    {
      gsl_set_error_handler( _old_handler );
      //std::cout << "De-Scoping GSL error handler" << std::endl;
    }

    gsl_error_handler_t *_handler, *_old_handler;

  };

  
  // Description:
  // Sets a GSL error function locally (within hte current scope)
  // and unsets at scope-exit
  gsl_scoped_error_function_t
  gsl_error_handler_scope( gsl_error_handler_t* handler );
  
  
  
  // Description:
  // Some useful error handler functions
 
  // ignore ERANGE errors (overflow/underflow)
  void gsl_ignore_representation_errors( const char* reason,
					 const char* file,
					 int line,
					 int gsl_errno );

  // ignore "math" errors
  void gsl_ignore_math_caveat_errors( const char* reason,
				      const char* file,
				      int line,
				      int gsl_errno );
    

  // Description:
  // Returns a *new* allocated gsl vector from vector
  // This *must* be free'd when done!
  gsl_vector* new_gsl_vector( const std::vector<double>& v );
  
  // Description:
  // Creates and returns avector from a gsl_vector*
  std::vector<double> to_vector(const gsl_vector* v );
  
}


#endif

