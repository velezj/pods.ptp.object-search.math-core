
#if !defined( __MATH_CORE_MATH_FUNCITON_HPP__ )
#define __MATH_CORE_MATH_FUNCITON_HPP__

#include <boost/shared_ptr.hpp>

namespace math_core
{

  
  // Description:
  // A mathematical function which can be composed using 
  // mathematical operators
  template<typename T_Input, typename T_Output>
  class math_function_t
  {
  public:

    // Description:
    // The function operator
    virtual
    T_Output operator() ( const T_Input& x ) const = 0;
    
  };


  // Description:
  // A wrapper fo a math function shared pointer into
  // a structure that can be used with opeartor()
  template<typename T_Input, typename T_Output >
  class solid_function
    : public math_function_t<T_Input,T_Output>
  {
  public:
    boost::shared_ptr<math_function_t<T_Input,T_Output> > _func;
    solid_function( const boost::shared_ptr<math_function_t<T_Input, T_Output> >& f )
      : _func(f)
    {}
    virtual
    T_Output operator()( const T_Input& x ) const
    {
      return (*_func)(x);
    }
  };


  // Description:
  // Operator implementations
  namespace operator_impl {

    
    // Descriuption:
    // Multiplication
    template<typename T_Input, typename T_Output >
    class multiply_t : public math_function_t<T_Input,T_Output>
    {
    public:
      boost::shared_ptr<math_function_t<T_Input, T_Output> > _a;
      boost::shared_ptr<math_function_t<T_Input, T_Output> > _b;
      multiply_t( const boost::shared_ptr<math_function_t<T_Input, T_Output > >& a,
		  const boost::shared_ptr<math_function_t<T_Input, T_Output > >& b )
	: _a(a), _b(b)
      {}
      
      virtual 
      T_Output operator() ( const T_Input& x ) const
      {
	return (*_a)(x) * (*_b)(x);
      }
    };

  }


  // Desacription:
  // Multiply functions totgehter to get a new function
  template<typename T_Input, typename T_Output >
  boost::shared_ptr<math_function_t<T_Input,T_Output> >
  operator* ( const boost::shared_ptr<math_function_t<T_Input,T_Output> >& a,
	      const boost::shared_ptr<math_function_t<T_Input,T_Output> >& b )
  {
    return boost::shared_ptr<operator_impl::multiply_t<T_Input,T_Output> >( new operator_impl::multiply_t<T_Input, T_Output>(a,b) );
  }

}

#endif

