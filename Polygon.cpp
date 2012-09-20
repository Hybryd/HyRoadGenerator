#include "Polygon.hpp"


Polygon::Polygon()
{
  
}


Polygon::Polygon( Polygon & p)
{
  for(int i=0;i<p.size();++i)
    this->poly.push_back(p[i]);
}


Polygon::Polygon(const Polygon & p)
{
  for(int i=0;i<p.size();++i)
    this->poly.push_back(p[i]);
}


double Polygon::area()
{
  double res=0;
  for(int i=0;i<size();++i)
    res+=(poly[i].second.x()-poly[i].first.x())*(poly[i].first.y()+poly[i].second.y());
  return fabs(res)/2.0;
}

double Polygon::diameter()
{
  double res=0;
  for(int i=0;i<size();++i)
    res=MAXI(res,sqrt((poly[i].second.x() - poly[i].first.x())*(poly[i].second.x() - poly[i].first.x()) + (poly[i].second.y() - poly[i].first.y())*(poly[i].second.y() - poly[i].first.y())));

  return res;
}



double Polygon::width()
{
  double res=100000000; // the power of infinity
  for(int i=0;i<size();++i)
    res=MINI(res,sqrt((poly[i].second.x() - poly[i].first.x())*(poly[i].second.x() - poly[i].first.x()) + (poly[i].second.y() - poly[i].first.y())*(poly[i].second.y() - poly[i].first.y())));
  return res;
}



/*
  Check if the polygon is closed
*/
bool Polygon::isClosed()
{
  bool res=true;
  for(int i=0;i<size()-1;++i)
    res &= (poly[i].second == poly[i+1].first);
  res &= (poly[size()-1].second == poly[0].first);
  return res;
}




/*
  Check if the polygon has a good shape
*/

bool Polygon::isAcceptable(double x)
{
  //return (area()/perimeter() > x); // notgood
  bool res;
  double w=width();
  if(w==0)
    res=false;
  else
  {
    res = (diameter()/w < x);
//    if(res)
//      std::cerr << diameter()/w << std::endl;
  }
  return res;
}


/*
  Barycenter
*/

Point Polygon::getBary()
{
  Point res(0,0);
  
  for(int i=0;i<size();++i)
  {
    res.x(res.x() + poly[i].first.x());
    res.y(res.y() + poly[i].first.y());
  }
  
  res.x(res.x()/size());
  res.y(res.y()/size());

  return res;
}




/*
  Return the index of the edge containing the random Point and the Point
*/

std::pair<int,Point> Polygon::randPoint()
{
  Point res(0,0);
  
  int rEdge = rand()%size();
  double t=((double)rand()/(double)RAND_MAX);
  
  res.x(poly[rEdge].first.x() + t*(poly[rEdge].second.x() - poly[rEdge].first.x()));
  res.y(poly[rEdge].first.y() + t*(poly[rEdge].second.y() - poly[rEdge].first.y()));

  return std::pair<int,Point>(rEdge,res);
}



/*
  Split the polygon by choosing random point and cutting orthogonaly
*/

std::pair< Polygon,Polygon > Polygon::split()
{
  std::pair<int,Point> pair = randPoint();
  int ed=pair.first; // indice de l'arete contenant le point aleatoire
  Point p=pair.second; // le point aleatoire
  Point v(poly[ed].second.x()-poly[ed].first.x(), poly[ed].second.y()-poly[ed].first.y()); // vecteur arete
  double c=-(v.x()*p.x() + v.y()*p.y()); // le c de l'equation de la droite ax + bx + c =0
  int i=0;
  bool bb=true;
  while (i<size() && bb)
  {
    if(i!=ed)
    {
      // on regarde si pour chaque arete les deux points sont du meme coté de la droite, ie meme signe
      bb = (poly[i].first.x()*v.x() + poly[i].first.y()*v.y() + c)*(poly[i].second.x()*v.x() + poly[i].second.y()*v.y() + c) > 0;
    }
    if(bb)
    {
      ++i;
    }
  }
  double denom=(v.x()*(poly[i].second.x()-poly[i].first.x()) + v.y()*(poly[i].second.y()-poly[i].first.y()));
  double t=0;
  if(denom != 0)
  {
    t=-(v.x()*poly[i].first.x() + v.y()*poly[i].first.y() + c)/denom;
  }
  else
  {
    std::cerr << " PROBLEME DENOMINATEUR NUL " << std::endl; // impossible to get here
  }
  
  
  Point intersec(poly[i].first.x() + t*(poly[i].second.x() - poly[i].first.x() ), poly[i].first.y() + t*(poly[i].second.y() - poly[i].first.y() )  );
  
  
  Polygon p1,p2;
  
  // split de l'arete de depart
  std::pair< Point,Point > ed1(p,poly[ed].second);
  std::pair< Point,Point > ed2(poly[ed].first,p);
  
  // split de l'arete d'intersection
  std::pair< Point,Point > edd1(poly[i].first,intersec);
  std::pair< Point,Point > edd2(intersec,poly[i].second);
  
  // creation du segment [intersec,p] (a inverser pour p2)
  std::pair< Point,Point > pont(intersec,p);
  
  p1.push_back(ed1);
  
  int k=ed;
  if(k==size()-1)
    k=0;
  else
    ++k;
  
  while(k<size() && k != i)
  {
    p1.push_back(poly[k]);
    ++k;
  }
  if(k==size())
  {
    k=0;
    while(k<size() && k != i)
    {
      p1.push_back(poly[k]);
      ++k;
    }
  }
  // on est arrivé en i
  p1.push_back(edd1);
  p1.push_back(pont); // p1 est defini
  

  // on commence p2
  if(k==size()-1)
    k=0;
  else
    ++k;
  
  p2.push_back(edd2);
  while(k<size() && k != ed)
  {
    p2.push_back(poly[k]);
    ++k;
  }
  if(k==size())
  {
    k=0;
    while(k<size() && k != ed)
    {
      p2.push_back(poly[k]);
      ++k;
    }
  }
  // on arrive en ed
  p2.push_back(ed2);
  // on inverse pont
  std::pair< Point,Point > tnop(pont.second,pont.first);
  p2.push_back(tnop);
  
  return std::pair< Polygon,Polygon >(p1,p2);
}




std::ostream & operator<<(std::ostream & out, Polygon & p)
{
  //gnuplotstyle
  for(int i=0;i<p.size();++i)
  {
    Point f=p[i].first;
    Point s=p[i].second;
    out << f << std::endl << s << std::endl << std::endl;
  }
  
  return out;
}

