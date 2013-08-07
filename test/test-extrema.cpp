
#include <math-core/extrema.hpp>
#include <iostream>

using namespace boost;
using namespace math_core;



double f( double x )
{
  return 1.0 / ( (x-3) * (x-3) + 5 );
}

int main()
{

  // find the maximum of f (it's at 3)
  double max_x
    = find_max<double>( boost::function1<double,double>(f), -10.0, 10.0, 0.0 );

  std::cout << "Max X: " << max_x << std::endl;

  return 0;
}
