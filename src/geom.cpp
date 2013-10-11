
#include "geom.hpp"
#include "io.hpp"
#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Eigen>
#include <limits.h>
#include <stdexcept>
#include <algorithm>

namespace math_core {

  //========================================================================

  nd_vector_t operator- (const nd_vector_t& a,
			 const nd_vector_t& b )
  {
    assert( a.n == b.n );
    nd_vector_t v = zero_vector(a.n);
    for( int64_t i = 0; i < a.n; ++i ) {
      v.component[i] = a.component[i] - b.component[i];
    }
    return v;
  }

  //========================================================================

  nd_vector_t operator+ (const nd_vector_t& a,
			 const nd_vector_t& b )
  {
    assert( a.n == b.n );
    nd_vector_t v = zero_vector(a.n);
    for( int64_t i = 0; i < a.n; ++i ) {
      v.component[i] = a.component[i] + b.component[i];
    }
    return v;
  }

  //========================================================================

  nd_vector_t operator- (const nd_vector_t&a )
  {
    nd_vector_t v = zero_vector(a.n);
    for( int64_t i = 0; i < a.n; ++i ) {
      v.component[i] = -a.component[i];
    }
    return v;
  }

  //========================================================================

  nd_vector_t operator- (const nd_point_t& a,
			 const nd_point_t& b )
  {
    assert( a.n == b.n );
    nd_vector_t v = zero_vector( a.n );
    for( int64_t i = 0; i < a.n; ++i ) {
      v.component[i] = a.coordinate[i] - b.coordinate[i];
    }
    return v;
  }

  //========================================================================

  nd_vector_t operator* (const nd_vector_t& v,
			 double a )
  {
    nd_vector_t vec = zero_vector( v.n );
    for( int64_t i = 0; i < v.n; ++i ) {
      vec.component[i] = a * v.component[i];
    }
    return vec;
  }

  //========================================================================

  nd_vector_t operator* (double a,
			 const nd_vector_t& v ) 
  {
    return v * a;
  }

  //========================================================================

  nd_vector_t operator* (const nd_direction_t& dir,
			 double a )
  {
    nd_vector_t vec = zero_vector( dir.n );
    for( int64_t i = 0; i < dir.n; ++i ) {
      vec.component[i] = a * dir.value[i];
    }
    return vec;
  }

  //========================================================================

  nd_vector_t operator* (double a,
			 const nd_direction_t& dir ) 
  {
    return dir * a;
  }

  //========================================================================

  nd_point_t operator+ (const nd_point_t& p,
			const nd_vector_t& vec )
  {
    return add( p, vec );
  }

  //========================================================================
  
  // Description:
  // The dot product and the magnitude of a vector
  double dot( const nd_vector_t& a,
	      const nd_vector_t& b )
  {
    double sum = 0;
    assert( a.n == b.n );
    for( int64_t i = 0; i < a.n; ++i ) {
      sum += ( a.component[i] * b.component[i] );
    }
    return sum;
  }

  //========================================================================

  double magnitude_sq( const nd_vector_t& a )
  {
    double sum = 0;
    for( int64_t i = 0; i < a.n; ++i ) {
      sum += ( a.component[i] * a.component[i] );
    }
    return sum;
  }

  //========================================================================

  double magnitude( const nd_vector_t& a )
  {
    return sqrt( magnitude_sq( a ) );
  }

  //========================================================================
  
  // Description:
  // Returns the distance between two points
  double distance_sq( const nd_point_t& a,
		      const nd_point_t& b )
  {
    assert( a.n == b.n );
    double sum = 0;
    for( int64_t i = 0; i < a.n; ++i ) {
      double d = a.coordinate[i] - b.coordinate[i];
      sum += ( d * d );
    }
    return sum;
  }

  //========================================================================

  double distance( const nd_point_t& a,
		   const nd_point_t& b )
  {
    return sqrt( distance_sq( a, b ) );
  }

  //========================================================================
  
  // Description:
  // Elementwise operations
  nd_vector_t elementwise_mult( const nd_vector_t& vec,
				double a )
  {
    nd_vector_t v = zero_vector( vec.n );
    for( int64_t i = 0; i < vec.n; ++i ) {
      v.component[i] = a * vec.component[i];
    }
    return v;
  }

  //========================================================================

  nd_vector_t elementwise_mult( double a,
				const nd_vector_t& vec )
  {
    return elementwise_mult( vec, a );
  }

  //========================================================================

  nd_vector_t elementwise_divide( const nd_vector_t& vec,
				  double a )
  {
    nd_vector_t v = zero_vector( vec.n );
    for( int64_t i = 0; i < vec.n; ++i ) {
      v.component[i] = a / vec.component[i];
    }
    return v;
  }

  //========================================================================

  nd_vector_t elementwise_divide( double a,
				  const nd_vector_t& vec )
  {
    nd_vector_t v = zero_vector( vec.n );
    for( int64_t i = 0; i < vec.n; ++i ) {
      v.component[i] = vec.component[i] / a;
    }
    return v;

  }

  //========================================================================

  // Description:
  // Convert  to/from vector and directions
  nd_direction_t direction( const nd_vector_t& a )
  {
    double mag = magnitude( a );
    nd_direction_t dir = axis_direction( a.n, 0 );
    for( int64_t i = 0; i < a.n; ++i ) {
      dir.value[i] = a.component[i] / mag;
    }
    return dir;
  }

  //========================================================================

  nd_vector_t vector( const nd_direction_t&a )
  {
    nd_vector_t vec = zero_vector( a.n );
    for( int64_t i = 0; i < a.n; ++i ) {
      vec.component[i] = a.value[i];
    }
    return vec;
  }

  //========================================================================


  // Description:
  // Add poitns and vectors
  nd_point_t add( const nd_point_t& p,
		  const nd_vector_t& vec )
  {
    assert( p.n == vec.n );
    nd_point_t res = zero_point( p.n );
    for( int64_t i = 0; i < p.n; ++i ) {
      res.coordinate[i] = p.coordinate[i] + vec.component[i];
    }
    return res;
  }

  //========================================================================

  // Description:
  // Create simple known vector and points
  nd_point_t zero_point( int64_t n )
  {
    nd_point_t p;
    p.n = n;
    p.coordinate = std::vector<double>( n, 0.0 );
    return p;
  }

  //========================================================================

  nd_vector_t zero_vector( int64_t n )
  {
    nd_vector_t v;
    v.n = n;
    v.component = std::vector<double>( n, 0.0 );
    return v;
  }

  //========================================================================

  nd_direction_t axis_direction( int64_t n, int64_t dim )
  {
    nd_direction_t dir;
    dir.n = n;
    dir.value = std::vector<double>( n, 0.0 );
    dir.value[ dim ] = 1.0;
    return dir;
  }

  //========================================================================

  nd_direction_t x_axis_direction( int64_t n )
  {
    return axis_direction( n, 0 );
  }

  //========================================================================

  nd_direction_t y_axis_direction( int64_t n )
  {
    return axis_direction( n, 1 );
  }


  //========================================================================

  nd_direction_t z_axis_direction( int64_t n )
  {
    return axis_direction( n, 2 );
  }


  //========================================================================

  // Description:
  // Simple creation functions
  nd_point_t point()
  {
    nd_point_t p;
    p.n = 0;
    return p;
  }

  //========================================================================

  nd_point_t point( double x )
  {
    nd_point_t p;
    p.n = 1;
    p.coordinate = std::vector<double>( 1, x );
    return p;
  }

  //========================================================================

  nd_point_t point( double x, double y )
  {
    nd_point_t p;
    p.n = 2;
    p.coordinate = std::vector<double>( 2, x );
    p.coordinate[1] = y;
    return p;
  }

  //========================================================================

  nd_point_t point( double x, double y, double z )
  {
    nd_point_t p;
    p.n = 3;
    p.coordinate = std::vector<double>( 3, x );
    p.coordinate[1] = y;
    p.coordinate[2] = z;
    return p;
  }

  //========================================================================

  nd_point_t point( int64_t n, const double* data ) 
  {
    nd_point_t p;
    p.n = n;
    p.coordinate.assign( data, data + n );
    return p;
  }

  //========================================================================

  nd_point_t point( int64_t n, const std::vector<double>& data ) 
  {
    nd_point_t p;
    p.n = n;
    p.coordinate = data;
    return p;
  }

  //========================================================================

  nd_point_t point( const std::vector<double>& data ) 
  {
    return point( data.size(), data );
  }

  //========================================================================

  nd_vector_t vector()
  {
    nd_vector_t v;
    v.n = 0;
    return v;
  }

  //========================================================================

  nd_vector_t vector( double x )
  {
    nd_vector_t v;
    v.n = 1;
    v.component = std::vector<double>( 1, x );
    return v;
  }

  //========================================================================

  nd_vector_t vector( double x, double y )
  {
    nd_vector_t v;
    v.n = 2;
    v.component = std::vector<double>( 2, x );
    v.component[1] = y;
    return v;
  }

  //========================================================================

  nd_vector_t vector( double x, double y, double z )
  {
    nd_vector_t v;
    v.n = 3;
    v.component = std::vector<double>( 3, x );
    v.component[1] = y;
    v.component[2] = z;
    return v;
  }


  //========================================================================

  nd_aabox_t aabox( const nd_point_t& start,
		    const nd_point_t& end )
  {
    assert( start.n == end.n );
    if( start.n != end.n )
      throw std::domain_error( "Cannot create box with different dimensional points!" );
    nd_aabox_t box;
    box.n = start.n;
    box.start = start;
    box.end = end;
    return box;
  }

  //========================================================================

  nd_point_t project_onto_line( const line_t& line,
				const nd_point_t& p )
  {
    // readjust point to be in a coordinate frame with line's origin
    // as origin
    nd_point_t p_in_line_origin = p + ( line.origin - zero_point(p.n) );
    
    // ok, now take line direction as vector nad projec onto that subspace
    nd_vector_t line_dir_vec = vector( line.direction );
    double subspace_dot_inv = 1.0 / dot( line_dir_vec, line_dir_vec );
    nd_vector_t p_as_vec = p_in_line_origin - zero_point(p.n);
    double proj_dot = dot( line_dir_vec, p_as_vec );
    double fraction_along_direction = subspace_dot_inv * proj_dot;
    
    // now add from line origin along direction the given amount
    nd_point_t proj_p = line.origin + ( fraction_along_direction * line.direction );
    
    return proj_p;
  }

  //========================================================================
  
  nd_point_t project_onto_line_segment( const line_segment_t& segment,
					const nd_point_t& p,
					double& fraction_along_segment )
  {
    // readjust point to be in a coordinate frame with segment's start
    // as origin
    nd_point_t p_in_line_origin = p + ( segment.start - zero_point(p.n) );
    
    // ok, now take segment (end-start) as vector nad projec onto that subspace
    nd_vector_t line_dir_vec = segment.end - segment.start;
    double subspace_dot_inv = 1.0 / dot( line_dir_vec, line_dir_vec );
    nd_vector_t p_as_vec = p_in_line_origin - zero_point(p.n);
    double proj_dot = dot( line_dir_vec, p_as_vec );
    fraction_along_segment = subspace_dot_inv * proj_dot;
    
    // now add from segment start along direction the given amount
    nd_point_t proj_p = segment.start + ( fraction_along_segment * line_dir_vec );

    // // debug
    // std::cout << "  -- p_in_line_origin: " << p_in_line_origin << std::endl;
    // std::cout << "  -- line_dir_vec: " << line_dir_vec << std::endl;
    // std::cout << "  -- subspace_dot_inv: " << subspace_dot_inv << std::endl;
    // std::cout << "  -- p_as_vec: " << p_as_vec << std::endl;
    // std::cout << "  -- proj_dot: " << proj_dot << std::endl;
    // std::cout << "  -- frac * line_dir_vec: " << ( fraction_along_segment * line_dir_vec ) << std::endl;
    
    return proj_p;
  }
  
  //========================================================================

  bool is_inside( const nd_point_t& p,
		  const nd_aabox_t& box )
  {
    assert( p.n == box.n );
    if( p.n != box.n )
      return false;
    
    // linearly test each coordiante
    for( int32_t i = 0; i < p.n; ++i ) {
      if( ! ( box.start.coordinate[i] <= p.coordinate[i] &&
	      p.coordinate[i] <= box.end.coordinate[i] ) )
	return false;
    }
    return true;
  }

  //========================================================================
  
  bool is_fully_inside( const nd_aabox_t& inner,
			const nd_aabox_t& outer )
  {
    return 
      is_inside( inner.start, outer ) &&
      is_inside( inner.end, outer );
  }

  //========================================================================

  double length( const nd_aabox_t& box,
		 const size_t dimension )
  {
    assert( dimension < box.n );
    if( (long)dimension >= box.n )
      return std::numeric_limits<double>::signaling_NaN();
    
    return box.end.coordinate[ dimension ] - box.start.coordinate[ dimension ];
  }

  //========================================================================

  bool operator== (const nd_point_t& a,
		   const nd_point_t& b )
  {
    return a.coordinate == b.coordinate;
  }
  bool operator== (const nd_vector_t& a,
		   const nd_vector_t& b )
  {
    return a.component == b.component;
  }
  bool operator== (const nd_direction_t& a,
		   const nd_direction_t& b )
  {
    return a.value == b.value;
  }
  bool operator== (const nd_aabox_t& a,
		   const nd_aabox_t& b )
  {
    return 
      a.start == b.start &&
      a.end == b.end;
  }

  //========================================================================

  bool point_lexicographical_compare( const nd_point_t& a,
				      const nd_point_t& b )
  {

    assert( a.n == a.coordinate.size() );
    assert( b.n == b.coordinate.size() );
    return std::lexicographical_compare( a.coordinate.begin(),
					 a.coordinate.end(),
					 b.coordinate.begin(),
					 b.coordinate.end() );

    // if ( a.n < b.n ) {
    //   return true;
    // }
    // if( b.n < a.n ) {
    //   return false;
    // }
    // assert( a.n == b.n );
    // for( int i = 0 ; i < a.n; ++i ) {
    //   if( a.coordinate[i] < b.coordinate[i] )
    // 	return true;
    // }
    // return false;
  }

  //========================================================================
  
  bool point_compare_x( const nd_point_t& a,
			const nd_point_t& b )
  {
    assert( a.n == b.n );
    assert( a.n > 0 );
    if( a.coordinate[0] < b.coordinate[0] )
      return true;
    return false;
  }

  //========================================================================
  
  bool point_compare_y( const nd_point_t& a,
			const nd_point_t& b )
  {
    assert( a.n == b.n );
    assert( a.n >= 2 );
    if( a.n < 2 )
      throw std::domain_error( "Cannot compare < 2D points by their y coordiante!" );
    if( a.coordinate[1] < b.coordinate[1] )
      return true;
    return false;
  }

  //========================================================================

  nd_point_t centroid( const nd_aabox_t& box ) {
    return box.start + ( 0.5 * (box.end - box.start) );
  }

  //========================================================================

  std::vector<nd_point_t>
  points_inside_window( const nd_aabox_t& window,
			const std::vector<nd_point_t>& points )
  {
    std::vector<nd_point_t> res;
    for( std::vector<nd_point_t>::const_iterator iter = points.begin();
	 iter != points.end();
	 ++iter ) {
      if( is_inside( *iter, window ) ) {
	res.push_back( *iter );
      }
    }
    return res;
  }

  //========================================================================

  bool undefined( const nd_point_t& p )
  {
    return p.n == 0 ||
      p.coordinate.size() == 0;
  }

  //========================================================================

  bool undefined( const nd_aabox_t& b )
  {
    return undefined( b.start ) ||
      undefined( b.end );
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
  //========================================================================
  //========================================================================
  //========================================================================

  
}
