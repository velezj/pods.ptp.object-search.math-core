#include "polynomial.hpp"
#include <gsl/gsl_integration.h>
#include <limits>

#include <iostream>

namespace math_core {


  //====================================================================

  // Description:
  // gsl arc-length functional
  double arc_length_function( double x, void* params ) {
    polynomial_t* poly = static_cast<polynomial_t*>(params);
    polynomial_t d_poly = poly->derivative();
    //d_poly.reduce_degree();
    double d_f = d_poly.evaluate( x );
    return sqrt( 1 + d_f * d_f );
  }

  //====================================================================

  bool polynomial_t::is_zero_poly() const
  {
    for( double c : _coeffs ) {
      if( c != 0.0 ) {
	return false;
      }
    }
    return true;
  }

  //====================================================================

  double polynomial_t::arc_length( const double& a,
				   const double& b ) const
  {
    if( is_zero_poly() ) {
      if( a == b ) {
	return 0.0;
      } else {
	return std::numeric_limits<double>::infinity();
      }
    }
    
    size_t deg = degree();

    if( deg < 1 ) {
      return 0.0;
    }

    // compute the "reduced" degree
    polynomial_t temp( _coeffs );
    temp.reduce_degree();
    deg = temp.degree();
    
    gsl_integration_glfixed_table *tbl;
    tbl = gsl_integration_glfixed_table_alloc( (deg + 1) / 2 + 1 );

    // get the gsl_function for arc length
    gsl_function arc_f;
    arc_f.function = &arc_length_function;
    arc_f.params = const_cast<void*>( static_cast<const void*>(this) );
    
    // perform fast integration
    double res = 
      gsl_integration_glfixed( &arc_f, a, b, tbl );

    // free resources
    gsl_integration_glfixed_table_free( tbl );

    // return arc length
    return res;
  }

  
  //====================================================================

  double
  polynomial_t::arc_length_chord_approx
  ( const double& start_x,
    const double& end_x,
    const double& tol,
    double& midpoint_err ) const
  {
    double mid_x = start_x + ( end_x - start_x ) / 2.0;
    double start_y = evaluate( start_x );
    double end_y = evaluate( end_x );
    double mid_y = evaluate( mid_x );
    double chord_length = sqrt( (end_y - start_y) * (end_y - start_y) +
				(end_x - start_x) * (end_x - start_x) );
    double c_s = sqrt( (end_y - mid_y) * (end_y - mid_y) +
		       (end_x - mid_x) * (end_x - mid_x) );
    double c_e = sqrt( (mid_y - start_y) * (mid_y - start_y) +
		       (mid_x - start_x) * (mid_x - start_x) );
    double c = c_s + c_e;
    midpoint_err = fabs( chord_length - c );

    // recurse if not within tolerance
    if( midpoint_err > tol ) {
      double le, re;
      chord_length = 
	arc_length_chord_approx( start_x, mid_x, tol / 2.0, le )
	+ arc_length_chord_approx( mid_x, end_x, tol / 2.0, re );
      midpoint_err = le + re;
    }

    return chord_length;
  }

  //====================================================================


  double
  polynomial_t::find_point_arc_length_away( const double& start_x,
					    const double& target_arc_length,
					    const double& tol) const
  {
    
    if( is_zero_poly() ) {
      // this is tought, return infinity here
      return std::numeric_limits<double>::infinity();
    }

    size_t max_iter = 100;
    size_t iteration = 0;

    // ok, search for an end_x which is "too" far then shirnk down
    // initially guess as if we are on a straight line
    double end_x = start_x + target_arc_length;
    double ac = arc_length( start_x, end_x );
    while( ac < target_arc_length && iteration < max_iter ) {
      end_x = start_x + (end_x - start_x) * 2.0;
      ac = arc_length( start_x, end_x );
      ++iteration;
    }

    // check if we magically happened to guess right
    if( fabs( ac - target_arc_length ) <= tol ) {
      return end_x;
    }

    // Ok, now shrink down to find it
    double guess_x = start_x + (end_x - start_x) / 2.0;
    ac = arc_length( start_x, guess_x );
    while( fabs( ac - target_arc_length ) > tol
	   && iteration < max_iter ) {
      if( ac < target_arc_length ) {
	guess_x = start_x + guess_x + (end_x - guess_x) / 2.0;
      } else {
	end_x = guess_x;
	guess_x = start_x + (end_x - start_x) / 2.0;
      }
      ac = arc_length( start_x, guess_x );
      +iteration;
    }
    return guess_x;
  }


  //====================================================================

  double
  polynomial_t::find_point_arc_length_away_chord_approx
  ( const double& start_x,
    const double& target_arc_length,
    const double& tol,
    const double& approx_tol) const
  {
    
    if( is_zero_poly() ) {
      // this is tought, return infinity here
      return std::numeric_limits<double>::infinity();
    }

    size_t max_iter = 100;
    size_t iteration = 0;
    double ce;

    // ok, search for an end_x which is "too" far then shirnk down
    // initially guess as if we are on a straight line
    double end_x = start_x + target_arc_length;
    double ac = arc_length_chord_approx( start_x, end_x, approx_tol, ce );
    while( ac < target_arc_length && iteration < max_iter ) {
      end_x = start_x + (end_x - start_x) * 2.0;
      ac = arc_length_chord_approx( start_x, end_x, approx_tol, ce );
      ++iteration;
    }

    // check if we magically happened to guess right
    if( fabs( ac - target_arc_length ) < tol ) {
      return end_x;
    }

    // Ok, now shrink down to find it
    double guess_x = start_x + (end_x - start_x) / 2.0;
    ac = arc_length_chord_approx( start_x, guess_x, approx_tol, ce );
    while( fabs( ac - target_arc_length) > tol
	   && iteration < max_iter ) {
      if( ac < target_arc_length ) {
	guess_x = start_x + guess_x + (end_x - guess_x) / 2.0;
      } else {
	end_x = guess_x;
	guess_x = start_x + (end_x - start_x) / 2.0;
      }
      ac = arc_length_chord_approx( start_x, guess_x, approx_tol, ce );
      +iteration;
    }
    return guess_x;
  }


  //====================================================================
  
  std::ostream& operator<< (std::ostream&  os, const polynomial_t& p )
  {
    bool printed_something = false;
    for( size_t i = 0; i < p.coefficients().size(); ++i ) {
      if( p.coefficients()[i] == 0 ) {
	if( i + 1 == p.coefficients().size() && printed_something == false ) {
	  // pass downwards since we need to print something!
	} else {
	  continue;
	}
      }
      if( i > 0 && printed_something ) {
	os << " + ";
      }
      os << p.coefficients()[i];
      printed_something = true;
      if( i > 0 ) {
	os << "x^" << i;
      }
    }
    return os;
  }
  
  //====================================================================

}


