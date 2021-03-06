
#include "io.hpp"
#include <iostream>
#include <sstream>


namespace math_core {



  //========================================================================

  std::ostream& operator<< (std::ostream& os, const nd_point_t& p ) {
    os << "(";
    for( std::size_t i = 0; i < p.n - 1; ++i ) {
      os << p.coordinate[i] << ",";
    }
    if( p.n > 0 ) {
      os << p.coordinate[ p.n - 1 ];
    }
    os << ")";
    return os;
  }

  //========================================================================
  
  std::ostream& operator<< (std::ostream& os, const nd_vector_t& v ) {
    os << "[";
    for( std::size_t i = 0; i < v.n - 1; ++i ) {
      os << v.component[i] << ",";
    }
    if( v.n > 0 ) {
      os << v.component[ v.n - 1 ];
    }
    os << "]";
    return os;
  }

  //========================================================================

  std::ostream& operator<< (std::ostream& os, const nd_direction_t& d ) {
    os << "<";
    for( std::size_t i = 0; i < d.n - 1; ++i ) {
      os << d.value[i] << ",";
    }
    if( d.n > 0 ) {
      os << d.value[ d.n - 1 ];
    }
    os << ">";
    return os;
  }

  //========================================================================

  std::ostream& operator<< (std::ostream& os, const line_t& line )
  {
    os << "{Line " << line.origin << " " << line.direction << "}";
    return os;
  }

  //========================================================================

  std::ostream& operator<< (std::ostream& os, const line_segment_t& segment )
  {
    os << "{Seg " << segment.start << " " << segment.end << "}";
    return os;
  }

  //========================================================================

  std::ostream& operator<< (std::ostream& os, const nd_aabox_t& box )
  {
    os << "{Box " << box.start << " " << box.end << "}";
    return os;
  }

  //========================================================================

  std::ostream& operator<< (std::ostream& os, const std::vector<double>& v )
  {
    for( size_t i = 0; i < v.size(); ++i ) {
      os << v[i] << ", ";
    }
    return os;
  }
  

  //========================================================================

  std::string to_json( const nd_point_t& p )
  {
    std::ostringstream oss;
    oss << "[ ";
    for( size_t i = 0; i < p.n; ++i ) {
      oss << p.coordinate[i];
      if( i < p.n - 1 ) {
	oss << ",";
      }
    }
    oss << "]";
    return oss.str();
  }

  //========================================================================
  
  std::string to_json( const nd_vector_t& v )
  {
    std::ostringstream oss;
    oss << "[ ";
    for( size_t i = 0; i < v.n; ++i ) {
      oss << v.component[i];
      if( i < v.n - 1 ) {
	oss << ",";
      }
    }
    oss << "]";
    return oss.str();
  }

  //========================================================================

  std::string to_json( const nd_direction_t& d )
  {
    std::ostringstream oss;
    oss << "[ ";
    for( size_t i = 0; i < d.n; ++i ) {
      oss << d.value[i];
      if( i < d.n - 1 ) {
	oss << ",";
      }
    }
    oss << "]";
    return oss.str();
  }


  //========================================================================
  
  std::string to_json( const nd_aabox_t& b )
  {
    std::ostringstream oss;
    oss << "{ \"object_class\" : \"nd_aabox_t\" , ";
    oss << "  \"start\" : " << to_json( b.start ) << " , ";
    oss << "  \"end\" : " << to_json( b.end );
    oss << " }";
    return oss.str();
  }

  
  //========================================================================

  std::string to_json( const dense_matrix_t& mat )
  {
    std::ostringstream oss;
    oss << "{ \"object_class\" : \"dense_matrix_t\" , ";
    oss << "  \"rows\" : " << mat.rows << " , ";
    oss << "  \"cols\" : " << mat.cols << " , ";
    oss << "  \"num_elements\" : " << mat.num_elements << " , ";
    oss << "  \"data\" : [ ";
    for( size_t i = 0; i < mat.data.size(); ++i ) {
      oss << mat.data[i];
      if( i < mat.data.size() - 1 ) {
	oss << ",";
      }
    }
    oss << "] }";
    return oss.str();
  }

  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================
  //========================================================================



}
