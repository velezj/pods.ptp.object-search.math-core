
#if !defined( __IO_HPP__ )
#define __IO_HPP__

#include "lcmtypes/math_core.hpp"
#include <iosfwd>

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
}

#endif

