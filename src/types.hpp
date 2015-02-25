

#ifndef __MATH_CORE_types_HPP__
#define __MATH_CORE_types_HPP__

#include <cstddef>
#include <vector>

namespace math_core {

  using std::size_t;

  //======================================================================

  //
  // An N-Dimensional Point
  class nd_point_t
  {
  public:
    std::size_t n;
    std::vector<double> coordinate;
  };
  
  //======================================================================

  //
  // An N-Dimensional Direcotion (normalized to magnitude 1)
  class nd_direction_t
  {
  public:
    std::size_t    n;
    std::vector< double > value;
  };
  
  //======================================================================

  //
  // And N-Dimensional Vector (treated as a direction from origin with
  // magnitude ratehr than a point in space)
  class nd_vector_t
  {
  public:
    std::size_t    n;
    std::vector< double > component;
  };
  
  //======================================================================

  //
  // An N-Dimensional Axis Aligned Bounding Box determined by  two extrema
  // points of opposing corners
  class nd_aabox_t
  {
  public:
    std::size_t    n;
    nd_point_t start;
    nd_point_t end;
  };
    
  //======================================================================

  //
  // An N-Dimensional line segment defined by start and end points
  class line_segment_t
  {
  public:
    nd_point_t start;
    nd_point_t end;
  };
  
  //======================================================================

  //
  // An N-Dimensional line defined by an origin and a direction
  // This ttype may be used for a formal line or for a ray.
  class line_t
  {
  public:
    nd_point_t origin;
    nd_direction_t direction;
  };
  
  //======================================================================

  //
  // A dense matrix of double-valued numbers
  class dense_matrix_t
  {
  public:
    std::size_t    rows;
    std::size_t    cols;
    std::size_t    num_elements;
    std::vector< double > data;
  };
  
  //======================================================================
  //======================================================================
  //======================================================================
  //======================================================================
  


}


#endif
