
#include "extrema.hpp"



namespace math_core {

  
  //======================================================================

  namespace impl {
    double negative_shimmy_f( double x, void* user ) {
      boost::function1<double,double> *f = static_cast<boost::function1<double,double>* >( user );
      return -(*f)(x);
    }
    double shimmy_f( double x, void* user ) {
      boost::function1<double,double> *f = static_cast<boost::function1<double,double>* >( user );
      return (*f)(x);
    }
  }
  
  //======================================================================
  
  template<>
  double
  find_max( const boost::function1<double,double>& f,
	    const double& low,
	    const double& high,
	    const double& guess) 
  {
    int status;
    unsigned long max_iterations = 10000;
    unsigned long iteration = 0;
    const gsl_min_fminimizer_type* T;
    gsl_min_fminimizer *s;
    gsl_function F;

    // the epsilons for convergence
    double absolute_epsilon = 0.001;
    double relative_epsilon = 0.0;
    
    // the minimum and interval
    double min, interval_low, interval_high;
    
    // setup the gsl function as teh negative shimmy (since we want a max)
    F.function = &impl::negative_shimmy_f;
    F.params = const_cast<void*>( (void*)&f );
    
    // use the brent minimizer , allocate it
    T = gsl_min_fminimizer_brent;
    s = gsl_min_fminimizer_alloc( T );
    gsl_min_fminimizer_set( s, &F, guess, low, high );

    // temporaryly set the gsl error function to nothing
    // we will handle error explicitly here
    gsl_error_handler_t* old_error_handler 
      = gsl_set_error_handler_off();

    // iterate the minimizer until we have succedded OR
    // we have reached max iterations
    // OR we have a bad function (minimum not in range
    do {

      ++iteration;
      status = gsl_min_fminimizer_iterate(s);

      // handle errors
      if( status == GSL_EBADFUNC ) {
	// this means the function had a bad value, 
	// we don't really know what to do here so we throw an
	// exception
	throw std::domain_error("While finding maximum of function, encountered bad value (either NaN of Inf)." );
      }
      
      
      // get current min and interval
      min = gsl_min_fminimizer_x_minimum(s);
      interval_high = gsl_min_fminimizer_x_upper(s);
      interval_low = gsl_min_fminimizer_x_lower(s);

      // check if we have the best minima, so just stop
      if( status == GSL_FAILURE ) {
	std::cout << "find_max found \"best\" maxima but it was weird, stopping and returning current best." << std::endl;
	break;
      }
      
      // check if we are done
      status = gsl_min_test_interval( interval_low,
				      interval_high,
				      absolute_epsilon,
				      relative_epsilon );
      
    } while( iteration < max_iterations && 
	     status == GSL_CONTINUE );
    
    // restore the gsl error handler
    gsl_set_error_handler( old_error_handler );

    // free minimizer
    gsl_min_fminimizer_free(s);

    // return the found maxima
    return min;
    
  }


  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================


}
