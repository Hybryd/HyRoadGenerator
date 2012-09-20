/*

Source : "An iterated subdivision algorithm for procedural road plan generation", Nicholas Rudzicz & Clark Verbrugge.

Hybryd-

*/




#include <iostream>
#include <stack>
#include <vector>

#include "Point.hpp"
#include "Polygon.hpp"




/*
  Density population, defined on the whole square and has values in (0,1)
*/
double density(double x,double y)
{
  // Gaussian centered on (x0,y0), of meansquare value sig.
  double x0=2;
  double y0=2;
  double sig=18;
  return (exp(-((x-x0)*(x-x0) + (y-y0)*(y-y0))/sig)*0.98);
}





int main()
{
  srand(time(NULL));
  double Amin=0.05;
  double Amax=0.7;
  int iterMax=20;
  
  
  std::stack<Polygon> mustBeEmpty;
  std::vector<Polygon> mustBeFull;
  
  
  Polygon pInit;

  // DO NOT PUT NEGATIVE VALUES (for the algorithm for areas)  
  std::pair < Point,Point > e1 (Point(0,0), Point(10,0));
  std::pair < Point,Point > e2 (Point(10,0), Point(10,10));
  std::pair < Point,Point > e3 (Point(10,10), Point(0,10));
  std::pair < Point,Point > e4 (Point(0,10),Point(0,0));

  
  pInit.push_back(e1);
  pInit.push_back(e2);
  pInit.push_back(e3);
  pInit.push_back(e4);

//  std::pair < Point,Point > e1 (Point(0,0), Point(10,0));
//  std::pair < Point,Point > e2 (Point(10,0), Point(0,10));
//  std::pair < Point,Point > e3 (Point(0,10), Point(0,0));

//  
//  pInit.push_back(e1);
//  pInit.push_back(e2);
//  pInit.push_back(e3);


  mustBeEmpty.push(pInit);


  Polygon p;
  std::pair< Polygon,Polygon> pair;
  bool ok=true;
  int j=0;
  double xbar1=0;
  double ybar1=0;
  double xbar2=0;
  double ybar2=0;


  while(mustBeEmpty.size()!=0)
  {
    p=mustBeEmpty.top();
    mustBeEmpty.pop();
    if(p.area() > (1-density(p.getBary().x(),p.getBary().y()))*Amax)
    {
      ok=true;
      j=0;
      xbar1=0;
      ybar1=0;
      xbar2=0;
      ybar2=0;
      while(ok && j<iterMax)
      {
        pair = p.split();
        xbar1=pair.first.getBary().x();
        ybar1=pair.first.getBary().y();
        xbar2=pair.second.getBary().x();
        ybar2=pair.second.getBary().y();
        
        // constraints on the resulting polygons
        ok = !(pair.first.area() > (1-density(xbar1,ybar1))*Amin && pair.second.area() > (1-density(xbar2,ybar2))*Amin && pair.first.isClosed() && pair.second.isClosed() && (pair.first.isAcceptable(10)  && pair.second.isAcceptable(10)  ));
        ++j;
      }
      mustBeEmpty.push(pair.first);
      mustBeEmpty.push(pair.second);
    }
    else
    {
      mustBeFull.push_back(p);
    }
//    std::cerr << mustBeFull.size() << std::endl;
  }



  // display all the polygons
  for(int i=0;i<mustBeFull.size();++i)
    std::cout << mustBeFull[i] << std::endl << std::endl;

  return 0;
}
