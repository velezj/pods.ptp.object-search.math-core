
#include <math-core/roots.hpp>
#include <iostream>


using namespace math_core;

double f(const double& x)
{
  return 3.0 + 2.0 * x + 1.0 * x*x - 3.0 * x*x*x;
}


int main( int argc, char** argv )
{

  size_t eps_tol_bits = 10;
  size_t max_iter = 100;
  
  double l,u;
  bool res;

  l = 0;
  u = 10;
  res = find_zero_crossing_range_with_guess( f, l, u );
  std::cout << "find_zero_crossing_range()= " << res 
	    << "  [" << l << " , " 
	    << u << "]" << std::endl;

  l = 0;
  u = 1e10;
  res = find_root_with_guess( f, eps_tol_bits, max_iter, l, u );
  std::cout << "find_root()= " << res 
	    << "  [" << l << " , " 
	    << u << "]" << std::endl;
  
  long r;
  l = 0;
  u = 10;
  res = find_integer_root_with_guess( f, max_iter, l, u, r );
  std::cout << "find_integer_root()= " << res
	    << " " << r << std::endl;


  // res = find_zero_crossing_range( f, l, u );
  // std::cout << "find_zero_crossing_range()= " << res 
  // 	    << "  [" << l << " , " 
  // 	    << u << "]" << std::endl;

  // max_iter = 1e5;
  // res = find_root( f, eps_tol_bits, max_iter, l, u );
  // std::cout << "find_root()= " << res 
  // 	    << "  [" << l << " , " 
  // 	    << u << "]" << std::endl;


  return 0;
}
