
#include <math-core/polynomial_fit.hpp>
#include <math-core/io.hpp>
#include <iostream>

using namespace math_core;


int main( int argc, char** argv )
{

  std::vector<double> x = {0,  1,  2,  3,  4,  5,  6,   7,   8,   9,   10};
  std::vector<double> y = {1,  6,  17, 34, 57, 86, 121, 162, 209, 262, 321};
  size_t degree = 4;
  dense_matrix_t cov;
  double chisq;
  std::vector<double> coeffs;
  
  polynomial_least_squares_fit( degree,
				x, y,
				coeffs,
				chisq,
				cov );

  std::cout << "Fit Poly: ";
  for( size_t i = 0; i < coeffs.size(); ++i ) {
    std::cout << "+ " << coeffs[i] << " x^" << i << " ";
  }
  std::cout << std::endl;
  std::cout << "ChiSq: " << chisq << "  Cov: " << std::endl;
  std::cout << as_eigen_mat( cov ) << std::endl;

  return 0;
}
