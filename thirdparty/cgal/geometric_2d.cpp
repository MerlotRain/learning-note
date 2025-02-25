#include <CGAL/Simple_cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/centroid.h>
#include <CGAL/Aff_transformation_2.h>

#include <iostream>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2;
typedef CGAL::Aff_transformationC2<Kernel> Transformation;

void point_code() {
    Point_2 p1(0, 0);
    Point_2 p2(1, 1);
    Point_2 p3(2, 0);
    std::cout << p1.x() << std::endl;
    std::cout << p1.y() << std::endl;
    double squre_distance = CGAL::squared_distance(p1, p2);
    double distance = std::sqrt(squre_distance);

    // 点群的重心
    std::vector<Point_2> ps = { p1, p2, p3 };
    Point_2 cent_point = CGAL::centroid(ps.begin(), ps.end());
    std::cout << cent_point << std::endl;


    CGAL::Orientation orien = CGAL::orientation(p1, p2, p3);
    if (orien == CGAL::Orientation::LEFT_TURN)
    {
        std::cout << "p3 is to the left of line p1-p2" << std::endl;
    }
    else if (orien == CGAL::RIGHT_TURN)
    {
        // 
    }
    else
    {
        std::cout << "p3 is collinear with line p1-p2" << std::endl;
    }
}

void segment_code() {
  Point_2 p1(0, 0);
  Point_2 p2(4, 4);
  Point_2 p3(0, 4);
  Point_2 p4(4, 0);
  Segment_2 seg1(p1, p2);
  Segment_2 seg2(p3, p4);

  if (CGAL::do_intersect(seg1, seg2)) {
    std::cout << "The segments intersect" << std::endl;
    auto result = CGAL::intersection(seg1, seg2);
    // now use std::get_if
    if (const Segment_2 *s = std::get_if<Segment_2>(&*result)) {
      std::cout << *s << std::endl;
    } else {
      const Point_2 *p = std::get_if<Point_2>(&*result);
      std::cout << *p << std::endl;
    }
    return 0;
  }
}

void polygon_code() {
    Point_2 p1(0, 0);
    Point_2 p2(1, 1);
    Point_2 p3(2, 0);

    Polygon_2 polygon;
    polygon.push_back(p1);
    polygon.push_back(p2);
    polygon.push_back(p3);
}
