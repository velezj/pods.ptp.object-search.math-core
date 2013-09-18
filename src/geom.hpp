 
#if !defined( __GEOM_HPP__ )
#define __GEOM_HPP__


#include "lcmtypes/p2l_math_core.hpp"
#include <vector>



namespace math_core {


  // Description:
  // Operators to manipulate vectors (add and subtract)
  nd_vector_t operator- (const nd_vector_t& a,
			 const nd_vector_t& b );
  nd_vector_t operator+ (const nd_vector_t& a,
			 const nd_vector_t& b );
  nd_vector_t operator- (const nd_vector_t&a );

  // Description:
  // We can also scalar multiple vectors
  nd_vector_t operator* (const nd_vector_t& vec,
			 double a );
  nd_vector_t operator* (double a,
			 const nd_vector_t& vec);
  

  // Description:
  // Subtracting two points gives a vector
  nd_vector_t operator- (const nd_point_t& a,
			 const nd_point_t& b );

  // Description:
  // Add poitns and vectors
  // We can always add a vector to a point
  nd_point_t add( const nd_point_t& p,
		  const nd_vector_t& vec );
  nd_point_t operator+ (const nd_point_t& p,
			const nd_vector_t& vec );

  // Description:
  // Multiplying a direction by scalar to give a vector.
  // This is done element-wise
  nd_vector_t operator* (const nd_direction_t& dir,
			 double a );
  nd_vector_t operator* (double a,
			 const nd_direction_t& dir);
  nd_vector_t elementwise_mult( const nd_vector_t& vec,
				double a );
  nd_vector_t elementwise_mult( double a,
				const nd_vector_t& vec );
  nd_vector_t elementwise_divide( const nd_vector_t& vec,
				  double a );
  nd_vector_t elementwise_divide( double a,
				  const nd_vector_t& vec );
  

  
  // Description:
  // The dot product and the magnitude of a vector
  double dot( const nd_vector_t& a,
	      const nd_vector_t& b );
  double magnitude_sq( const nd_vector_t& a );
  double magnitude( const nd_vector_t& a );

  
  // Description:
  // Returns the distance between two points
  double distance_sq( const nd_point_t& a,
		      const nd_point_t& b );
  double distance( const nd_point_t& a,
		   const nd_point_t& b );
  
  

  // Description:
  // Convert  to/from vector and directions
  nd_direction_t direction( const nd_vector_t& a );
  nd_vector_t vector( const nd_direction_t&a );



  // Description:
  // Create simple known vector and points
  nd_point_t zero_point( int64_t n );
  nd_vector_t zero_vector( int64_t n );
  nd_direction_t axis_direction( int64_t n, int64_t dim );
  nd_direction_t x_axis_direction( int64_t n );
  nd_direction_t y_axis_direction( int64_t n );
  nd_direction_t z_axis_direction( int64_t n );

  // Description:
  // Simple creation functions
  nd_point_t point();
  nd_point_t point( double x );
  nd_point_t point( double x, double y );
  nd_point_t point( double x, double y, double z );
  nd_vector_t vector();
  nd_vector_t vector( double x );
  nd_vector_t vector( double x, double y );
  nd_vector_t vector( double x, double y, double z );


  // Description:
  // Create points from arrays (copies the data!)
  nd_point_t point( int64_t n, const double* data );
  nd_point_t point( int64_t n, const std::vector<double>& data );
  nd_point_t point( const std::vector<double>& data );

  // Description:
  // Create an axis abligned bounding pot from corner points
  nd_aabox_t aabox( const nd_point_t& start,
		    const nd_point_t& end );

  // Description:
  // some projection into subspaces
  
  // Description:
  // Project onto a line
  nd_point_t project_onto_line( const line_t& line,
				const nd_point_t& p );

  // Description:
  // Project onto a line segment
  nd_point_t project_onto_line_segment( const line_segment_t& segment,
					const nd_point_t& p,
					double& fraction_along_segment );


  // Description:
  // test if a point is inside of a box
  bool is_inside( const nd_point_t& p,
		  const nd_aabox_t& box );

  // Description:
  // Test if a box is fully inside another box
  bool is_fully_inside( const nd_aabox_t& inner,
			const nd_aabox_t& outer );

  // Description:
  // returns the "length" of a dimension for a box
  double length( const nd_aabox_t& box,
		 const size_t dimension );


  // Description:
  // Returns the center point of a box
  nd_point_t centroid( const nd_aabox_t& box );


  // Descripiton:
  // Equality operators for objects
  bool operator== (const nd_point_t& a,
		   const nd_point_t& b );
  bool operator== (const nd_vector_t& a,
		   const nd_vector_t& b );
  bool operator== (const nd_direction_t& a,
		   const nd_direction_t& b );
  bool operator== (const nd_aabox_t& a,
		   const nd_aabox_t& b );

  // Descriptiojn:
  // Lexicographical compare for points
  bool point_lexicographical_compare( const nd_point_t& a,
				      const nd_point_t& b );

  // Description:
  // Compare points by x coordiante (first coordiante )
  bool point_compare_x( const nd_point_t& a,
			const nd_point_t& b );
  
  // Description:
  // Compare points by y coordiante (second coordiante )
  bool point_compare_y( const nd_point_t& a,
			const nd_point_t& b );


  // Description:
  // Returns the points which are inside of the window
  std::vector<nd_point_t> 
  points_inside_window( const nd_aabox_t& window,
			const std::vector<nd_point_t>& points );


  // Description:
  // returns true iif the given point is undefined
  bool undefined( const nd_point_t& p );
  
  
  // Description:
  // returns true iif the given box is undefined
  bool undefined( const nd_aabox_t& b );
  
}


#endif


