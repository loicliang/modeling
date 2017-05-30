#ifndef H_nodes
#define H_nodes

#include "point3.h"

struct Node;
struct Line;
struct Plane;
struct Volume;


struct Node
{
    double x,y,z;
    int n;
    bool f;
    Node() {}
    Node(double x,double y,double z, int n,bool f=true):x(x),y(y),z(z),n(n),f(true) {}
    bool operator == (const Node & a) const{ return sgn(x - a.x) == 0 && sgn(y - a.y) == 0 && sgn(z - a.z) == 0; }

};

inline double dist_node(const Node &A,const Node &B)
{
  double temp;
  temp=std::sqrt(sqr(A.x-B.x)+sqr(A.y-B.y)+sqr(A.z-B.z));
  return temp;
};

struct Line
{
    int n;
    int n1;
    int n2;
    bool f;
    bool edit;
    bool operator == (const Line & a) const{ return sgn(n1 - a.n1) == 0 && sgn(n2 - a.n2) == 0 && f && a.f; }
    Line() {}
   Line(int nn,int nn1,int nn2,bool ff=true,bool editt=true):n(nn),n1(nn1),n2(nn2),f(ff),edit(editt){}

};
struct BSpline
{
    int n;
    int bsp_control;
    std::vector<int> bspoint;
    bool f;
};

struct Plane
{
    int n;      //Plane's number
    int num;    //number of lines
    std::vector<int> line;
    bool f;
};

struct Volume
{
    int n;
    int num;
    std::vector<int> plane;
    bool f;
};











#endif // H_nodes
