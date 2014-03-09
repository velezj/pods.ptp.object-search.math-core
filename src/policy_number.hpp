
#if !defined( __MATH_CORE_policy_number_HPP__ )
#define __MATH_CORE_policy_number_HPP__

#include <boost/operators.hpp>
#include <boost/math/special_functions/pow.hpp>

namespace math_core {

  //==================================================================

#define POLICY_NUMBER_BINARY_OP_APPLY_POLICY( op, ret )	\
  ret operator op ( const T& a ) {			\
    _value op a;					\
    apply_policy();					\
    return *this;					\
  }							\
  ret operator op (const self_t& a ) {			\
    _value op a._value;					\
    apply_policy();					\
    return *this;					\
  }

#define POLICY_NUMBER_BINARY_BOOL_OP( op )	\
  bool operator op (const T& a ) {		\
    return _value op a;				\
  }						\
  bool operator op (const self_t& a) {		\
    return _value op a._value;			\
  }
  
  //==================================================================

  // Description:
  // A number which does not allow itself to becore too small
  // or too large (as eponent factors of 1.0).
  // This is particularly useful for things like probabilities
  // which should enver actually be zero or infinity
  //
  // In essence, we bound the value by:
  //    low_sign * 10^low_exp <= value <= high_sign * 10^high_exp
  template< class T, int LOW_EXPONENT, int LOW_SIGN, int HIGH_EXPONENT, int HIGH_SIGN >
  class bounded_below_above_number_t
    : public boost::ordered_euclidean_ring_operators<bounded_below_above_number_t<T,LOW_EXPONENT,LOW_SIGN, HIGH_EXPONENT,HIGH_SIGN> >,
      public boost::ordered_euclidean_ring_operators<bounded_below_above_number_t<T,LOW_EXPONENT,LOW_SIGN,HIGH_EXPONENT,HIGH_SIGN>, T>
  {
  public:

    // Description:
    // self_t for convinience
    typedef bounded_below_above_number_t<T,LOW_EXPONENT,LOW_SIGN,HIGH_EXPONENT,HIGH_SIGN> self_t;

    // Description:
    // for reflection
    typedef T value_type;

    // Description:
    // The actual low and high bounds
    static T LOW_BOUND;
    static T HIGH_BOUND;

  public: // API

    bounded_below_above_number_t()
      : _value()
    { apply_policy(); }
    bounded_below_above_number_t( const T& v )
      : _value(v) 
    { apply_policy(); }
    bounded_below_above_number_t( const self_t& s )
      : _value(s._value)
    { apply_policy(); }
    
    
    template< class U >
    U convert_to() const
    {
      return U(_value);
    }

    operator T() const {
      return _value;
    }
    
  public: // operators

    POLICY_NUMBER_BINARY_OP_APPLY_POLICY(+=,self_t);
    POLICY_NUMBER_BINARY_OP_APPLY_POLICY(-=,self_t);
    POLICY_NUMBER_BINARY_OP_APPLY_POLICY(*=,self_t);
    POLICY_NUMBER_BINARY_OP_APPLY_POLICY(/=,self_t);
    POLICY_NUMBER_BINARY_OP_APPLY_POLICY(%=,self_t);
    POLICY_NUMBER_BINARY_BOOL_OP(<);
    POLICY_NUMBER_BINARY_BOOL_OP(>);
    
  protected:
    
    T _value;
    
  protected:
    
    // Description:
    // Applies the policy to _value, settign as needed
    void apply_policy() {
      if( _value < LOW_BOUND ) {
	_value = LOW_BOUND;
      }
      if( _value > HIGH_BOUND ) {
	_value = HIGH_BOUND;
      }
    }
    
  };
  

  // Description:
  // Initialize the statics inside class
  template< class T, int LE, int LS, int HE, int HS > 
  typename bounded_below_above_number_t<T,LE,LS,HE,HS>::value_type 
  bounded_below_above_number_t<T,LE,LS,HE,HS>::LOW_BOUND 
  = LS * boost::math::pow<LE>( 10.0 );
  template< class T, int LE, int LS, int HE, int HS > 
  typename bounded_below_above_number_t<T,LE,LS,HE,HS>::value_type 
  bounded_below_above_number_t<T,LE,LS,HE,HS>::HIGH_BOUND 
  = HS * boost::math::pow<HE>( 10.0 );  

  //==================================================================
  
#define POLICY_NUMBER_PROXY_FUNCTION_1( func )				\
  template< class T, int LE, int LS, int HE, int HS >			\
  bounded_below_above_number_t<T,LE,LS,HE,HS>				\
  func ( const bounded_below_above_number_t<T,LE,LS,HE,HS>& a ) {	\
    return								\
      bounded_below_above_number_t<T,LE,LS,HE,HS>( func ( a._value ) );	\
  }
  
#define POLICY_NUMBER_PROXY_FUNCTION_BOOL_1( func )			\
  template< class T, int LE, int LS, int HE, int HS >			\
  bool									\
  func ( const bounded_below_above_number_t<T,LE,LS,HE,HS>& a ) {	\
    return func ( a._value );						\
  }
  
  
#define POLICY_NUMBER_PROXY_FUNCTION_2( func )				\
  template< class T, int LE, int LS, int HE, int HS >			\
  bounded_below_above_number_t<T,LE,LS,HE,HS>				\
  func ( const bounded_below_above_number_t<T,LE,LS,HE,HS>& a,		\
	 const bounded_below_above_number_t<T,LE,LS,HE,HS>& b) {	\
    return								\
      bounded_below_above_number_t<T,LE,LS,HE,HS>( func ( a._value,	\
							  b._value ) );	\
  }

#define POLICY_NUMBER_PROXY_FUNCTION_BOOL_2( func )			\
  template< class T, int LE, int LS, int HE, int HS >			\
  bool									\
  func ( const bounded_below_above_number_t<T,LE,LS,HE,HS>& a,		\
	 const bounded_below_above_number_t<T,LE,LS,HE,HS>& b) {	\
    return func ( a._value, b._value );					\
  }
  
  
  //==================================================================

  // <cmath> API

  // MISSING:
  //    frexp
  //    ldexp
  //    modf
  //    ilogb
  //    scalbn
  //    scalbin
  //    lround
  //    llround
  //    rint
  //    lrint
  //    llrint
  //    nearbyint
  //    remainder
  //    remquo
  //    copysign
  //    nextafter
  //    nexttoward
  //    fma
  //    fpclassify
  //    signbit

  POLICY_NUMBER_PROXY_FUNCTION_1( log );
  POLICY_NUMBER_PROXY_FUNCTION_1( log10 );
  POLICY_NUMBER_PROXY_FUNCTION_1( log2 );
  POLICY_NUMBER_PROXY_FUNCTION_1( log1p );
  POLICY_NUMBER_PROXY_FUNCTION_1( logb );
  POLICY_NUMBER_PROXY_FUNCTION_1( sqrt );
  POLICY_NUMBER_PROXY_FUNCTION_1( cbrt );
  POLICY_NUMBER_PROXY_FUNCTION_1( exp );
  POLICY_NUMBER_PROXY_FUNCTION_1( exp2 );
  POLICY_NUMBER_PROXY_FUNCTION_1( expm1 );
  POLICY_NUMBER_PROXY_FUNCTION_1( cos );
  POLICY_NUMBER_PROXY_FUNCTION_1( sin );
  POLICY_NUMBER_PROXY_FUNCTION_1( tan );
  POLICY_NUMBER_PROXY_FUNCTION_1( acos );
  POLICY_NUMBER_PROXY_FUNCTION_1( asin );
  POLICY_NUMBER_PROXY_FUNCTION_1( atan );
  POLICY_NUMBER_PROXY_FUNCTION_1( cosh );
  POLICY_NUMBER_PROXY_FUNCTION_1( sinh );
  POLICY_NUMBER_PROXY_FUNCTION_1( tanh );
  POLICY_NUMBER_PROXY_FUNCTION_1( acosh );
  POLICY_NUMBER_PROXY_FUNCTION_1( asinh );
  POLICY_NUMBER_PROXY_FUNCTION_1( atanh );
  POLICY_NUMBER_PROXY_FUNCTION_1( erf );
  POLICY_NUMBER_PROXY_FUNCTION_1( erfc );
  POLICY_NUMBER_PROXY_FUNCTION_1( tgamma );
  POLICY_NUMBER_PROXY_FUNCTION_1( lgamma );
  POLICY_NUMBER_PROXY_FUNCTION_1( ceil );
  POLICY_NUMBER_PROXY_FUNCTION_1( floor );
  POLICY_NUMBER_PROXY_FUNCTION_1( trunc );
  POLICY_NUMBER_PROXY_FUNCTION_1( round );
  POLICY_NUMBER_PROXY_FUNCTION_1( fabs );
  POLICY_NUMBER_PROXY_FUNCTION_1( abs );


  POLICY_NUMBER_PROXY_FUNCTION_2( atan2 );
  POLICY_NUMBER_PROXY_FUNCTION_2( pow );
  POLICY_NUMBER_PROXY_FUNCTION_2( hypot );
  POLICY_NUMBER_PROXY_FUNCTION_2( fdim );
  POLICY_NUMBER_PROXY_FUNCTION_2( fmax );
  POLICY_NUMBER_PROXY_FUNCTION_2( fmin );


  POLICY_NUMBER_PROXY_FUNCTION_BOOL_1( isfinite );
  POLICY_NUMBER_PROXY_FUNCTION_BOOL_1( isinf );
  POLICY_NUMBER_PROXY_FUNCTION_BOOL_1( isnan );
  POLICY_NUMBER_PROXY_FUNCTION_BOOL_1( isnormal );

  POLICY_NUMBER_PROXY_FUNCTION_BOOL_2( isgreater );
  POLICY_NUMBER_PROXY_FUNCTION_BOOL_2( isgreaterequal );
  POLICY_NUMBER_PROXY_FUNCTION_BOOL_2( isless );
  POLICY_NUMBER_PROXY_FUNCTION_BOOL_2( islessequal );
  POLICY_NUMBER_PROXY_FUNCTION_BOOL_2( islessgreater );
  POLICY_NUMBER_PROXY_FUNCTION_BOOL_2( isunordered );

  //==================================================================
  //==================================================================
  //==================================================================
  //==================================================================
  //==================================================================
  //==================================================================
  //==================================================================
  //==================================================================
  //==================================================================
  

}


#endif
