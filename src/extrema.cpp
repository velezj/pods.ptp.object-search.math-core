
#include "extrema.hpp"
#include "exception.hpp"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_min.h>
#include <nlopt.hpp>
#include <iostream>




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

    // temporaryly set the gsl error function to nothing
    // we will handle error explicitly here
    gsl_error_handler_t* old_error_handler 
      = gsl_set_error_handler_off();

    // use the brent minimizer , allocate it
    T = gsl_min_fminimizer_brent;
    s = gsl_min_fminimizer_alloc( T );
    gsl_min_fminimizer_set( s, &F, guess, low, high );

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
    
    
    // free minimizer
    gsl_min_fminimizer_free(s);

    // restore the gsl error handler
    gsl_set_error_handler( old_error_handler );


    // return the found maxima
    return min;
    
  }


  //======================================================================

  double _f_wrap(const std::vector<double>& x,
		 std::vector<double>& grad,
		 void* data )
  {
    assert( grad.empty() );
    std::function<double(const std::vector<double>&)>* f
      = static_cast<std::function<double(const std::vector<double>&)>* >(data);
    return (*f)( x );
  }

  std::vector<double>
  find_global_extrema
  (const stop_criteria_t& stop,
   const std::function<double(const std::vector<double>&)>& f,
   const std::vector<double>& initial_x_arg,
   const std::vector<double>& lower_bounds,
   const std::vector<double>& upper_bounds,
   const extrema_direction_enum& max_min,
   double& extrema_value)
  {

    // ok, clamp initial arguments to bounds
    std::vector<double> initial_x = initial_x_arg;
    for( size_t i = 0; i < initial_x_arg.size(); ++i ) {
      double l = lower_bounds[i];
      double u = upper_bounds[i];
      double x = initial_x[i];
      if( x < l ) {
	initial_x[i] = l;
      }
      if( x > u ) {
	initial_x[i] = u;
      }
    }

    // catch any exceptions from nlopt and wrap them as a
    // math exception and trethrow
    try {

      // create a new nlopt object and set it's algoruthm and dimension
      // since we use an algorithm which requires a local optimizer,
      // supply that algorithm as well
      nlopt::opt engine( nlopt::GN_MLSL_LDS, initial_x.size() );
      nlopt::opt local_opt( nlopt::LN_BOBYQA, initial_x.size() );
      engine.set_local_optimizer( local_opt );

      //nlopt::opt engine( nlopt::GN_ISRES, initial_x.size() );

      //nlopt::opt engine( nlopt::GN_DIRECT_L, initial_x.size() );
   
      // setup the bound contraints
      engine.set_lower_bounds( lower_bounds );
      engine.set_upper_bounds( upper_bounds );

      // set object function and min/max'ing
      void* f_data = const_cast<void*>(static_cast<const void*>(&f));
      if( max_min == extrema_maximize ) {
	engine.set_max_objective( _f_wrap, f_data );
      } else {
	engine.set_min_objective( _f_wrap, f_data );
      }

      // set stopping criteria
      if( stop.abs_value ) {
	engine.set_stopval( *stop.abs_value );
      }
      if( stop.max_time ) {
	engine.set_maxtime( *stop.max_time );
      }
      if( stop.max_evals ) {
	engine.set_maxeval( *stop.max_evals );
      }
      if( stop.rel_tolerance ) {
	engine.set_ftol_rel( *stop.rel_tolerance );
      }


      // perform the optimization
      std::vector<double> opt_x = initial_x;
      nlopt::result res = engine.optimize( opt_x, extrema_value );

      // ok, now we want to run a local optimizer with this as a starting
      // point to get a finer solution (unless we satisfied)
      bool tune = true;
      if( tune && res != nlopt::STOPVAL_REACHED ) {

	try {
	  //std::cout << "  local tune..." << std::endl;
	
	  nlopt::opt tune( nlopt::LN_COBYLA, initial_x.size() );
	  //nlopt::opt tune( nlopt::LN_BOBYQA, initial_x.size() );
	  tune.set_lower_bounds( lower_bounds );
	  tune.set_upper_bounds( upper_bounds );
	  if( max_min == extrema_maximize ) {
	    tune.set_max_objective( _f_wrap, f_data );
	  } else {
	    tune.set_min_objective( _f_wrap, f_data );
	  }
	  if( stop.abs_value ) {
	    tune.set_stopval( *stop.abs_value );
	  }
	  if( stop.max_time ) {
	    tune.set_maxtime( *stop.max_time );
	  }
	  if( stop.max_evals ) {
	    tune.set_maxeval( *stop.max_evals );
	  }
	  if( stop.rel_tolerance ) {
	    tune.set_ftol_rel( *stop.rel_tolerance );
	  }

	  // ok, make *sure* we are within the bounds
	  for( size_t i = 0; i < opt_x.size(); ++i ) {
	    double l = lower_bounds[i];
	    double u = upper_bounds[i];
	    double x = opt_x[i];
	    if( x < l || x > u ) {
	      std::cout << "!!!AHH: maximization returned oparameters outside boudns!: i=" << i << " x=" << x << " [" << l << "," << u << "]  {" 
			<< (x - l) << "," << (u-x) << "}" << std::endl;
	      if( x < l ) {
		opt_x[i] = l;
	      }
	      if( x > u ) {
		opt_x[i] = u;
	      }
	    }
	  }

	  res = tune.optimize( opt_x, extrema_value );
	} catch ( nlopt::roundoff_limited& e ) {
	  // ignore roundoff limited
	  std::cout << "  ..roundoff-limited local optimization, continuing" << std::endl; 
	}
      }

      // ok, make *sure* we are within the bounds
      bool rerun = false;
      std::vector<double> new_initial_x = opt_x;
      for( size_t i = 0; i < opt_x.size(); ++i ) {
	double l = lower_bounds[i];
	double u = upper_bounds[i];
	double x = opt_x[i];
	if( x < l || x > u ) {
	  std::cout << "!!!AHH: maximization returned oparameters outside boudns!: i=" << i << " x=" << x << " [" << l << "," << u << "]" << std::endl;
	  if( x < l ) {
	    new_initial_x[i] = l + 0.1 * ( u - l );
	  }
	  if( x > u ) {
	    new_initial_x[i] = u - 0.1 * ( u - l );
	  }
	  rerun = true;
	}
      }
      if( rerun ) {
	return find_global_extrema (stop,
				    f,
				    new_initial_x,
				    lower_bounds,
				    upper_bounds,
				    max_min,
				    extrema_value);
      }

      // return the found optimize
      return opt_x;
    }
    catch( nlopt::roundoff_limited& re ) {
      std::cout << "  ..roundoff-limited global optimization, continuing" << std::endl; 
    }
    catch( std::exception& e ) {
      nlopt_result res;
      int line;
      char ef[255], er[255];
      nlopt_last_error_info( &res, er, &line, ef );
      std::cout << "  NLOpt Error: " << er << "  (" << ef << " " << line 
		<< ") no: " << res << std::endl;
      BOOST_THROW_EXCEPTION( boost::enable_error_info(e)
			     << errorinfo_nlopt_errorno( res )
			     << errorinfo_nlopt_file( std::string(ef) )
			     << errorinfo_nlopt_reason( std::string(er) )
			     << errorinfo_nlopt_line( line ) );
    }
  }


  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================


}
