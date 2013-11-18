
#if !defined( __MATRIX_HPP__ )
#define __MATRIX_HPP__


#include <lcmtypes/p2l_math_core.hpp>
#include <eigen3/Eigen/Eigen>

namespace math_core {

  
  // Description:
  // Eigen wrapper for dense_matrix_t types
  typedef Eigen::Map< Eigen::Matrix< double, 
				     Eigen::Dynamic, 
				     Eigen::Dynamic, 
				     Eigen::RowMajor > > 
  eigen_dense_matrix_map_t;

  // Description:
  // Wrap a dense_matrix_t into an Eigen form.
  // this is a wrap, hece nop const in the argument since
  // changing the resulting matrix will change the given one.
  eigen_dense_matrix_map_t as_eigen_mat( dense_matrix_t& mat );


  // Description:
  // Copy a dense_matrix_t to an Eigen matrix
  Eigen::MatrixXd to_eigen_mat( const dense_matrix_t& mat );

  // Description:
  // Copy a vector into eigned form
  Eigen::VectorXd to_eigen_mat( const nd_vector_t& vec );

  // Description:
  // Copy an std::vector to an eigen vector
  Eigen::VectorXd to_eigen_mat( const std::vector<double>& vec );

  // Description:
  // Returns an nd_vector_t from an eigne vector or matrix
  nd_vector_t to_vector( const Eigen::VectorXd& vec );
  nd_vector_t to_vector( const Eigen::MatrixXd& vec );

  // Description:
  // Copies from eigne matrix to dense_matrix_t
  dense_matrix_t to_dense_mat( const Eigen::MatrixXd& mat );

  // Description:
  // Returns true if the given matrix is diagonal (withinb epsillon)
  bool is_diagonal( const dense_matrix_t& mat, const double epsilon = 1e-10 );

  // Description:
  // Returns a dense matrix with given diagonal (and zero everywhere else)
  dense_matrix_t diagonal_matrix( const nd_point_t& d );
}


#endif

