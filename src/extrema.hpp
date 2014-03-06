
#if !defined( __MATH_CORE_EXTREMA_HPP__ )
#define __MATH_CORE_EXTREMA_HPP__


#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <functional>
#include <vector>

namespace math_core {


  // Description:
  // Searches for a maximum in a 1D function
  template< typename T_InputDomain, typename T_OutputDomain >
  T_InputDomain
  find_max( const boost::function1<T_OutputDomain, T_InputDomain>& f,
	    const T_InputDomain& low,
	    const T_InputDomain& high,
	    const T_InputDomain& guess );


  // Description:
  // stopping criteria for extrame finding
  struct stop_criteria_t 
  {
    boost::optional<size_t> max_evals;
    boost::optional<double> max_time;
    boost::optional<double> abs_value;
    boost::optional<double> rel_tolerance;
    stop_criteria_t() {}
    stop_criteria_t max_seconds( const double& s )
    { max_time = s; return *this; }
    stop_criteria_t max_evaluations( const size_t& e )
    { max_evals = e; return *this; }
    stop_criteria_t satisfactory_value( const double& s )
    { abs_value = s; return *this; }
    stop_criteria_t relative_tolerance( const double& t )
    { rel_tolerance = t; return *this; }
  };
  
  // global static criteria used to build up actual stopping
  // criteria using member functions above.
  // stop.max_second(5).satisfactory_value(1e20) etc...
  static stop_criteria_t stop;



  // Description:
  // multidimensional maximization/minimization for functions which only
  // deal in doubles.
  // This does global derrivative free optimization with bounded constraints
  // on the parameters dimensions.
  //
  // NOTE: the stopping criteria will at worst be a factor of 2 off.
  //       this is because we run a global optimization, then fine
  //       tune a local optimization using the *same* stopping criteria,
  //       hence if both reach the maximum time, the actual time will
  //       be 2*max_time
  enum extrema_direction_enum { extrema_maximize, extrema_minimize };
  std::vector<double>
  find_global_extrema
  (const stop_criteria_t& stop,
   const std::function<double(const std::vector<double>&)>& f,
   const std::vector<double>& initial_x,
   const std::vector<double>& lower_bounds,
   const std::vector<double>& upper_bounds,
   const extrema_direction_enum& max_min,
   double& extrema_value);

}

#endif

