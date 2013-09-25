
#if !defined( __MATH_CORE_UTILS_HPP__ )
#define __MATH_CORE_UTILS_HPP__

#include <vector>
#include <cstddef>

namespace math_core {


  // Description:
  // Remove an element from vector by index
  template<typename T>
  void remove( std::vector<T>& vec,
	       std::size_t index )
  {
    vec.erase( vec.begin() + index );
  }

  // Description:
  // Take the mean of a vector of numbers
  template<typename T_Num>
  T_Num mean( const std::vector<T_Num>& a )
  {
    T_Num sum = 0;
    for( std::size_t i = 0; i < a.size(); ++i ) {
      sum += a[i];
    }
    return sum / (T_Num)a.size();
  }

  // Description:
  // Take the variance of a vector of numbers
  template<typename T_Num>
  T_Num variance( const std::vector<T_Num>& a )
  {
    if( a.size() < 2 )
      return 0;
    T_Num sum = 0;
    T_Num m = mean( a );
    for( std::size_t i = 0; i < a.size(); ++i ) {
      T_Num d = a[i] - m;
      sum += (d*d);
    }
    return sum / (T_Num)(a.size()-1);
  }


  // Description:
  // Symetric round a floating number
  template< class T >
  T symmetric_round( const T& a )
  {
    return ( a > 0.0) ? floor( a + 0.5 ) : ceil( a - 0.5 );
  }


  // Description:
  // sort a given vectory using a proxy vector for the comparions
  

}

#endif

