
#include <math-core/polynomial.hpp>
#include <iostream>


using namespace math_core;

int main(int argc, char** argv )
{

  // create a particular polinomial and compute it's arc length
  polynomial_t line0( {0,1} );
  polynomial_t line1( {0,1,0} );
  polynomial_t quartic0( {0,1,1} );
  polynomial_t cubic0( {1,1,1,1} );

  std::cout << "Arc lengths (0, 10): " << std::endl;
  std::cout << line0 << " : " << line0.arc_length( 0, 10 ) << std::endl;
  std::cout << line1 << " : " << line1.arc_length( 0, 10 ) << std::endl;
  std::cout << quartic0 << " : " << quartic0.arc_length( 0, 10 ) << std::endl;
  std::cout << cubic0 << " : " << cubic0.arc_length( 0, 10 ) << std::endl;

  return 0;
}
