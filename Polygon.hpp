#ifndef POLYGON_HPP
#define POLYGON_HPP

#define MINI(X,Y) ( (X) < (Y) ? (X) : (Y) )
#define MAXI(X,Y) ( (X) > (Y) ? (X) : (Y) )


#include<cstdlib>
#include<cmath>
#include<vector>

#include "Point.hpp"



class Polygon
{
protected:
  std::vector< std::pair< Point,Point > > poly;


public:
  Polygon();
  Polygon( Polygon & p);
  Polygon(const Polygon & p);
  
  std::pair< Point,Point >                      operator[](unsigned int i) const {return poly[i];}
  int                                           size() const {return (poly.size());}
  void push_back(std::pair< Point,Point > & e)  {poly.push_back(e);} 
  double                                        area();
  double                                        diameter();
  double                                        width();
  bool                                          isClosed();
  bool                                          isAcceptable(double x);
  Point                                         getBary();
  std::pair<int,Point>                          randPoint();
  std::pair< Polygon,Polygon >                  split();

};

std::ostream & operator<<(std::ostream & out, Polygon & p);


#endif
