
#include <math-core/math_function.hpp>
#include <iostream>


using namespace math_core;


class f : public math_core::math_function_t<double,double>
{
public:
  
  virtual
  double operator() ( const double& x ) const {
    return x + 2.0; 
  }
};

class g : public math_function_t<double,double>
{
public:
  
  virtual
  double operator() ( const double& x ) const {
    return x * 2.0; 
  }
};



int main()
{

  boost::shared_ptr<math_function_t<double,double> > f0( new f() );
  boost::shared_ptr<math_function_t<double,double> > g0( new g() );
  boost::shared_ptr<math_function_t<double,double> > fXg = f0 * g0;
  for( double x = 0; x < 10; ++x ) {
    std::cout << "x: " << x << "  fXg(x): " << (*fXg)(x) << std::endl;
  }

  return 0;
}
