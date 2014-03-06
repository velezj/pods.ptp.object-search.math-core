
#include <math-core/extrema.hpp>
#include <iostream>

using namespace boost;
using namespace math_core;



double f( double x )
{
  return 1.0 / ( (x-3) * (x-3) + 5 );
}

double f_multi( std::vector<double> x ) 
{
  double sum = 0;
  for( size_t i = 0; i < x.size(); ++i ) {
    sum += f(x[i]) * (i+1);
  }
  return sum;
}

int main()
{

  // find the maximum of f (it's at 3)
  double max_x
    = find_max<double>( boost::function1<double,double>(f), -10.0, 10.0, 0.0 );

  std::cout << "Max X: " << max_x << std::endl;

  // find a maximum for multi f
  double max_val;
  std::vector<double> max_multi_x
    = find_global_extrema(stop.relative_tolerance(1e-5).max_evaluations(1e4),
			  f_multi,
			  { 0.1, 0.2, 0.3, 0.4, 0.5 },
			  { 0.0, 0.0, 0.0, 0.0, 0.0 },
			  { 10, 10, 10, 10, 10 },
			  extrema_maximize,
			  max_val );
  
  std::cout << "Max multi-x: (" << max_val << ") = ";
  for( size_t i = 0; i < max_multi_x.size(); ++i ) {
    std::cout << max_multi_x[i] << ", ";
  }
  std::cout << std::endl;
			   
  // find min of multix
  double min_val;
  std::vector<double> min_multi_x
    = find_global_extrema(stop.relative_tolerance(1e-5).max_evaluations(1e4),
			  f_multi,
			  { 0.1, 0.2, 0.3, 0.4, 0.5 },
			  { 0.0, 0.0, 0.0, 0.0, 0.0 },
			  { 10, 10, 10, 10, 10 },
			  extrema_minimize,
			  min_val );
  
  std::cout << "Min multi-x: (" << min_val << ") = ";
  for( size_t i = 0; i < min_multi_x.size(); ++i ) {
    std::cout << min_multi_x[i] << ", ";
  }
  std::cout << std::endl;
  

  return 0;
}
