#include <math-core/policy_number.hpp>
#include <iostream>


using namespace math_core;


int main( int argc, char** argv ) 
{

  typedef bounded_below_above_number_t<double,-5,5> num_t;
  num_t n( 10.0 );
  std::cout << "n.int    = " << n.convert_to<int>() << std::endl;
  std::cout << "n.double = " << n.convert_to<double>() << std::endl;
  std::cout << "n.float  = " << n.convert_to<float>() << std::endl;

  for( size_t i = 0; i < 10; ++i ) {
    n /= 10.0;
    std::cout << "/= 10 ..." << std::endl;
    std::cout << "  n.int    = " << n.convert_to<int>() << std::endl;
    std::cout << "  n.double = " << n.convert_to<double>() << std::endl;
    std::cout << "  n.float  = " << n.convert_to<float>() << std::endl;
  }

  for( size_t i = 0; i < 20; ++i ) {
    n *= 10.0;
    std::cout << "*= 10 ..." << std::endl;
    std::cout << "  n.int    = " << n.convert_to<int>() << std::endl;
    std::cout << "  n.double = " << n.convert_to<double>() << std::endl;
    std::cout << "  n.float  = " << n.convert_to<float>() << std::endl;
  }  

  return 0;
}
