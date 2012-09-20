#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>


class Point
{
protected:
  float ax;
  float ay;


public:
  Point(const Point & p): ax(p.ax),ay(p.ay) {}
  Point(float xx, float yy): ax(xx),ay(yy) {}
  Point(Point & p): ax(p.ax),ay(p.ay) {}
  
  float x(void) {return ax;}
  float y(void) {return ay;}
  
  void x(float xx) {ax=xx;}
  void y(float yy) {ay=yy;}
  
  bool operator==(Point & p) {return ( (ax ==p.ax)&&(ay==p.ay)   );}

};

std::ostream & operator<<(std::ostream & out, Point & p);

#endif
