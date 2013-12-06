
#if !defined( __P2L_MATH_CORE_mpt_HPP__ )
#define __P2L_MATH_CORE_mpt_HPP__


//#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/gmp.hpp>

//======================================================================

// Description:
// The default high precision number's digit precision
// This can be define *before* including this file to change it,
// otherwise a default value is used of 50
#if !defined( P2L_MATH_CORE_MPT_PRECISION )
#define P2L_MATH_CORE_MPT_PRECISION 50
#endif

//======================================================================

namespace math_core {
  namespace mpt {


    //======================================================================

    // Description:
    // A high-precision floating point number.
    // This will have the default precision 
    // (defined in P2L_MATH_CORE_MPT_PRECISION).
    //typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<P2L_MATH_CORE_MPT_PRECISION> > mp_float;
    typedef boost::multiprecision::number<boost::multiprecision::gmp_float<P2L_MATH_CORE_MPT_PRECISION> > mp_float;

    //======================================================================
    //======================================================================
    //======================================================================
    

  }
}


#endif
