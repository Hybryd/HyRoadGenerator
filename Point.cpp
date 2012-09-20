#include "Point.hpp"


std::ostream & operator<<(std::ostream & out, Point & p)
{
  //gnuplotstyle
  out << p.x() << " " << p.y() ;
  return out;
}

