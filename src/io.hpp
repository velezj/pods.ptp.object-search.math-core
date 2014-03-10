
#if !defined( __IO_HPP__ )
#define __IO_HPP__

#include "lcmtypes/p2l_math_core.hpp"
#include <iosfwd>
#include <string>

namespace math_core {

  
  // Description:
  // Output stream operators
  std::ostream& operator<< (std::ostream& os,
			    const nd_point_t& p );
  std::ostream& operator<< (std::ostream& os,
			    const nd_vector_t& v );
  std::ostream& operator<< (std::ostream& os,
			    const nd_direction_t& d );
  std::ostream& operator<< (std::ostream& os,
			    const line_t& line );
  std::ostream& operator<< (std::ostream& os,
			    const line_segment_t& segment );
  std::ostream& operator<< (std::ostream& os,
			    const nd_aabox_t& box );
  std::ostream& operator<< (std::ostream& os,
			    const std::vector<double>& v );


  // Description:
  // convertt ot JSON formatted string (no newlines!)
  std::string to_json( const nd_point_t& p );
  std::string to_json( const nd_vector_t& v );
  std::string to_json( const nd_direction_t& d );
  std::string to_json( const nd_aabox_t& b );
  std::string to_json( const dense_matrix_t& mat );
  
}

#endif

