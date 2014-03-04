
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
	return polynomial_t( std::vector<double>() );
      }
      std::vector<double> d_coeffs;
      for( size_t i = 0; i < degree(); ++i ) {
	d_coeffs.push_back( (i + 1) * _coeffs[i+1] );
      }
      return polynomial_t( d_coeffs );
    }

    // Description:
    // Evaluates the polinomial for some x
    double evaluate( const double& x ) const {
      if( degree() < 1 ) {
	return 0;
      }
      double res = 0;
      for( size_t i = 0; i < _coeffs.size(); ++i ) {
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

  protected:

  private:

    std::vector<double> _coeffs;
    //boost::optional<polynomial_t> _derivative;

  };
  
  //====================================================================


}

//====================================================================

// Description:
// Stream operator for polynomials
std::ostream& operator<< (std::ostream&  os, const math_core::polynomial_t& p );

//====================================================================



#endif

