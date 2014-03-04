
#include "polynomial_fit.hpp"
#include <gsl/gsl_multifit.h>


namespace math_core {


  //====================================================================

  void polynomial_least_squares_fit( const size_t degree,
				     const std::vector<double>& x,
				     const std::vector<double>& y,
				     polynomial_t& poly,
				     double& chi_sq,
				     dense_matrix_t& cov )
  {
    gsl_multifit_linear_workspace *ws;
    gsl_matrix *gsl_cov, *gsl_X;
    gsl_vector *gsl_y, *gsl_c;
    size_t num_obs = x.size();

    std::vector<double> coeffs;
    poly = polynomial_t(coeffs);
    
    // allocate our least square matrix X
    // and other gsl vec/mat
    gsl_X = gsl_matrix_alloc( num_obs, degree );
    gsl_y = gsl_vector_alloc( num_obs );
    gsl_c = gsl_vector_alloc( degree );
    gsl_cov = gsl_matrix_alloc( degree, degree );
    
    // fill in the gsl matrixes/vectors
    for( size_t i = 0; i < num_obs; ++i ) {
      gsl_matrix_set( gsl_X, i, 0, 1.0 );
      for( size_t j = 0; j < degree; ++j ) {
	gsl_matrix_set( gsl_X, i, j, pow( x[i], j ) );
      }
      gsl_vector_set( gsl_y, i, y[i] );
    }

    // create gsl workspace and fit hte polinomaial
    double gsl_chisq;
    ws = gsl_multifit_linear_alloc( num_obs, degree );
    gsl_multifit_linear( gsl_X, gsl_y, gsl_c, gsl_cov, &gsl_chisq, ws );

    // get back the results and store into wanted formats
    for( size_t i = 0; i < degree; ++i ) {
      coeffs.push_back( gsl_vector_get( gsl_c, i ) );
    }
    poly = polynomial_t(coeffs);
    chi_sq = gsl_chisq;
    Eigen::MatrixXd e_cov( degree, degree );
    for( size_t i = 0; i < degree; ++i ) {
      for( size_t j = 0; j < degree; ++j ) {
	e_cov(i,j) = gsl_matrix_get( gsl_cov, i, j );
      }
    }
    cov = to_dense_mat( e_cov );

    // free resources
    gsl_multifit_linear_free(ws);
    gsl_matrix_free( gsl_X );
    gsl_matrix_free( gsl_cov );
    gsl_vector_free( gsl_y );
    gsl_vector_free( gsl_c );
  }


  //====================================================================

  

}
