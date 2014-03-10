
#if !defined( __MATH_CORE_exception_HPP__ )
#define __MATH_CORE_exception_HPP__

#include <boost/exception/all.hpp>
#include <stdexcept>

namespace math_core {

  //========================================================================

  // Description:
  // Base class exception for p2l system
  class base_exception_t : public virtual std::exception,
			   public virtual boost::exception
  {};

  //========================================================================

  //========================================================================

}

#endif
