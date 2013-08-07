
#include "matrix.hpp"
#include "geom.hpp"
#include <stdexcept>



namespace math_core {

  //=========================================================================

  eigen_dense_matrix_map_t as_eigen_mat( dense_matrix_t& mat ) {
    double* data_ptr = &mat.data[0];
    eigen_dense_matrix_map_t em( data_ptr, mat.rows, mat.cols );
    return em;
  }

  //=========================================================================

  Eigen::MatrixXd to_eigen_mat( const dense_matrix_t& mat ) 
  {
    Eigen::MatrixXd m( mat.rows, mat.cols );
    for( int64_t row = 0; row < mat.rows; ++row ) {
      for( int64_t col = 0; col < mat.cols; ++col ) {
	
	int64_t col_major_index = mat.rows * col + row;
	int64_t row_major_index = mat.cols * row + col;

	m( col_major_index ) = mat.data[ row_major_index ];
      }
    } 

    return m;
  }

  //=========================================================================

  Eigen::VectorXd to_eigen_mat( const nd_vector_t& vec ) 
  {
    Eigen::VectorXd v( vec.n );
    for( int64_t i = 0; i < vec.n; ++i ) {
      v( i ) = vec.component[i];
    }
    return v;
  }

  //=========================================================================

  Eigen::VectorXd to_eigen_mat( const std::vector<double>& vec ) 
  {
    Eigen::VectorXd v( vec.size() );
    for( int64_t i = 0; i < vec.size(); ++i ) {
      v( i ) = vec[i];
    }
    return v;
  }


  //=========================================================================

  nd_vector_t to_vector( const Eigen::VectorXd& vec )
  {
    nd_vector_t v = zero_vector( vec.rows() );
    for( size_t i = 0; i < vec.rows(); ++i ) {
      v.component[i] = vec(i);
    }
    return v;
  }
  
  //=========================================================================

  nd_vector_t to_vector( const Eigen::MatrixXd& vec )
  {
    if( ! (vec.rows() == 1 ||
	   vec.cols() == 1))
      throw std::domain_error( "Cannot convert from a general MxN matroix to a vector!" );

    if( vec.rows() == 1 ) {
      nd_vector_t v = zero_vector( vec.rows() );
      for( size_t i = 0; i < vec.rows(); ++i ) {
	v.component[i] = vec(i,0);
      }
      return v;
    } else {
      nd_vector_t v = zero_vector( vec.cols() );
      for( size_t i = 0; i < vec.cols(); ++i ) {
	v.component[i] = vec(0,i);
      }
      return v;
    }
  }

  //=========================================================================

  dense_matrix_t to_dense_mat( const Eigen::MatrixXd& mat )
  {
    dense_matrix_t m;
    m.rows = mat.rows();
    m.cols = mat.cols();
    m.num_elements = m.rows * m.cols;
    m.data = std::vector<double>( m.num_elements );
    for( int64_t row = 0; row < mat.rows(); ++row ) {
      for( int64_t col = 0; col < mat.cols(); ++col ) {
	
	int64_t col_major_index = mat.rows() * col + row;
	int64_t row_major_index = mat.cols() * row + col;
	
	m.data[ row_major_index ] = mat( col_major_index );
      }
    } 
    
    return m;
  }

  //=========================================================================

  bool is_diagonal( const dense_matrix_t& mat, const double epsilon)
  {
    Eigen::MatrixXd m = to_eigen_mat( mat );
    bool diag = true;
    for( int i = 0; i < m.rows(); ++i ) {
      for( int j = 0; j < m.cols(); ++j ) {
	if( i == j )
	  continue;
	if( fabs(m(i,j)) > epsilon ) {
	  diag = false;
	  break;
	}
      }
      if( diag == false ) {
	break;
      }
    }
    return diag;
  }

  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================
  //=========================================================================

}
