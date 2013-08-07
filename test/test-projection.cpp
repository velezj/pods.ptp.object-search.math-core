
#include <math-core/geom.hpp>
#include <math-core/io.hpp>
//#include <cstdio>
#include <iostream>

using namespace math_core;
using namespace std;



int main( int argc, char** argv )
{

  // craete a line segment
  nd_point_t start2 = zero_point( 2 );
  nd_point_t end2 = point( 0, 1 );
  line_segment_t segment2 = { start2, end2 };
  nd_point_t p2 = point( 1,1 );
  double frac2;
  nd_point_t proj2 = project_onto_line_segment( segment2, p2, frac2 );
  cout << "Segment " << segment2 << " P: " << p2 << " Proj: " << proj2 << " f:" << frac2 << endl;

  // craete a line segment
  nd_point_t start3 = zero_point( 3 );
  nd_point_t end3 = point( 0, 1, 0 );
  line_segment_t segment3 = { start3, end3 };
  nd_point_t p3 = point( 1,1,1 );
  double frac3;
  nd_point_t proj3 = project_onto_line_segment( segment3, p3, frac3 );
  cout << "Segment " << segment3 << " P: " << p3 << " Proj: " << proj3 << " f:" << frac3 << endl;

  return 0;
}
