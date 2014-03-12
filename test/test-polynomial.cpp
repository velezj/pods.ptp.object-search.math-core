
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

  std::cout << "Derivative: " << std::endl;
  std::cout << "D( " << line0 << " ) = " << line0.derivative() << std::endl;
  std::cout << "D( " << line1 << " ) = " << line1.derivative() << std::endl;
  std::cout << "D( " << quartic0 << " ) = " << quartic0.derivative() << std::endl;
  std::cout << "D( " << cubic0 << " ) = " << cubic0.derivative() << std::endl;

  std::cout << "Arc lengths (0, 10): " << std::endl;
  std::cout << line0 << " : " << line0.arc_length( 0, 10 ) << std::endl;
  std::cout << line1 << " : " << line1.arc_length( 0, 10 ) << std::endl;
  std::cout << quartic0 << " : " << quartic0.arc_length( 0, 10 ) << std::endl;
  std::cout << cubic0 << " : " << cubic0.arc_length( 0, 10 ) << std::endl;

  double ac = 3.0;
  std::cout << line0 << " : " << ac 
	    << " away from 0 =  " 
	    << line0.find_point_arc_length_away( 0, ac ) 
	    << "  ac=" 
	    << line0.arc_length( 0, line0.find_point_arc_length_away( 0, ac ) )
	    << std::endl;
  std::cout << line1 << " : " << ac 
	    << " away from 0 =  " 
	    << line1.find_point_arc_length_away( 0, ac ) 
	    << "  ac=" 
	    << line1.arc_length( 0, line1.find_point_arc_length_away( 0, ac ) )
	    << std::endl;
  std::cout << quartic0 << " : " << ac 
	    << " away from 0 =  " 
	    << quartic0.find_point_arc_length_away( 0, ac ) 
	    << "  ac=" 
	    << quartic0.arc_length( 0, quartic0.find_point_arc_length_away( 0, ac ) )
	    << std::endl;
  std::cout << cubic0 << " : " << ac 
	    << " away from 0 =  " 
	    << cubic0.find_point_arc_length_away( 0, ac ) 
	    << "  ac=" 
	    << cubic0.arc_length( 0, cubic0.find_point_arc_length_away( 0, ac ) )
	    << std::endl;

  return 0;
}
