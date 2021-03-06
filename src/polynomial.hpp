
#if !defined( __MATH_CORE_polynomial_HPP__ )
#define __MATH_CORE_polynomial_HPP__

//#include <boost/optional.hpp>
#include <vector>
#include <iosfwd>
#include <cmath>

namespace math_core {


  //====================================================================

  // Description:
  // A class which represnets a 1D polinomial.
  class polynomial_t
  {
  public:

    // Description:
    // Creates a new empty polynomail (0th degree)
    polynomial_t()
    {}

    // Description:
    // Creates a new polinomial with given coefficients.
    // The order is from lowest exponent to highest,
    // so coeffs = [ 0 1 3 5 ] = 0 + x + 3x^2 + 5x^3
    polynomial_t( const std::vector<double>& coeffs )
      : _coeffs( coeffs )
    {}

    // Description:
    // Drop any zero coefficients at higher orders
    void reduce_degree()
    {
      size_t true_size = _coeffs.size();
      for( size_t i = _coeffs.size(); i > 0; --i ) {
	if( _coeffs[ i-1 ] == 0 ) {
	  --true_size;
	} else {
	  break;
	}
      }
      if( true_size != _coeffs.size() ) {
	_coeffs = std::vector<double>( _coeffs.begin(),
				       _coeffs.begin() + true_size );
      }
    }


    // Description:
    // Returns the degree of the polinomial
    size_t degree() const {
      if( _coeffs.size() > 0 ) {
	return _coeffs.size() - 1;
      }
      return 0;
    }

    // Descrioption:
    // Returns hte coefficients
    std::vector<double> coefficients() const {
      return _coeffs;
    }

    // Description:
    // Returns the dirivative of this polinomial as a polinomial
    polynomial_t derivative() const {
      if( degree() < 1 ) {
	return polynomial_t();
      }
      std::vector<double> d_coeffs( degree() );
      for( size_t i = 0; i < degree(); ++i ) {
	d_coeffs[i] = ( (i + 1) * _coeffs[i+1] );
      }
      return polynomial_t( d_coeffs );
    }

    // Description:
    // Evaluates the polinomial for some x
    double evaluate( const double& x ) const {
      double res = 0;
      if( !_coeffs.empty() ) {
	res = _coeffs[0];
      }
      for( size_t i = 1; i < _coeffs.size(); ++i ) {
	res += ( _coeffs[i] * std::pow(x,i));
      }
      return res;
    }

    // Description:
    // Computes teh arc length from a start and end segment of this
    // polinomial.
    // This is a generic computation and hence is *not* closed form.
    double arc_length( const double& start_x,
		       const double& end_x ) const;

    // Description:
    // Returns an approximate point that is arc-length again
    // from the given point in the polynomial.
    // This essentialyl does a binayr search with the
    // arc-length function
    double find_point_arc_length_away( const double& start_x,
				       const double& target_arc_length,
				       const double& tol = 1e-6 ) const;

    // Description:
    // Returns an approximate point that is arc-length again
    // from the given point in the polynomial.
    // This essentialyl does a binayr search with the
    // chord-length function!
    double find_point_arc_length_away_chord_approx
    ( const double& start_x,
      const double& target_arc_length,
      const double& tol = 1e-2,
      const double& approx_tol = 1.0 ) const;

    // Description:
    // Returns the chord approximation of the arc length
    // and ensure that the midpoiint differences are less than
    // given value.
    // returns the actual midpoint error
    double
    arc_length_chord_approx
    ( const double& start_x,
      const double& end_x,
      const double& tol,
      double& midpoint_err ) const;


  protected:

    // Description:
    // Checks if this is a zero polynomial
    bool is_zero_poly() const;

  private:

    std::vector<double> _coeffs;


  };
  
  //====================================================================

  // Description:
  // Stream operator for polynomials
  std::ostream& operator<< (std::ostream&  os, const polynomial_t& p );


}

//====================================================================


//====================================================================



#endif

