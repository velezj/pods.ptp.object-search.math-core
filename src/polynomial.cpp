#include "polynomial.hpp"
#include <gsl/gsl_integration.h>

#include <iostream>

namespace math_core {


  //====================================================================

  // Description:
  // gsl arc-length functional
  double arc_length_function( double x, void* params ) {
    polynomial_t* poly = static_cast<polynomial_t*>(params);
    polynomial_t d_poly = poly->derivative();
    double d_f = d_poly.evaluate( x );
    return sqrt( 1 + d_f * d_f );
  }


  //====================================================================

  double polynomial_t::arc_length( const double& a,
				   const double& b ) const
  {
    size_t deg = degree();

    if( deg < 1 ) {
      return 0.0;
    }
    
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

  //====================================================================

}

//====================================================================

std::ostream& operator<< (std::ostream&  os, const math_core::polynomial_t& p )
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
