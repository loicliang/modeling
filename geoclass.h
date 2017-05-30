#ifndef H_geoclass
#define H_geoclass

#include "geo-datastruct.h"

class geometry
{
protected:
    std::vector<Node> nodes;
    std::vector<Line> lines;
    std::vector<BSpline> bsplines;
    std::vector<Plane> planes;
    std::vector<Volume> volumes;
    int n_initial,l_initial,p_initial,v_initial;
public:
    //read & write nodes
    int Node_n(int t) {return(nodes[t].n);}
    double Node_x(int t) {return(nodes[t].x);}
    double Node_y(int t) {return(nodes[t].y);}
    double Node_z(int t) {return(nodes[t].z);}
    bool Node_f(int t) {return(nodes[t].f);}
    int Node_size() {return(nodes.size());}
    void Node_add(Node temp) {nodes.push_back(temp);}

    //read & write lines
    int Line_n(int t) {return(lines[t].n);}
    int Line_n1(int t) {int temp; temp=lines[t].n1; return(temp);}
    int Line_n2(int t) {int temp; temp=lines[t].n2; return(temp);}
    bool Line_f(int t) {return(lines[t].f);}
    bool Line_edit(int t) {return(lines[t].edit);}
    int Line_size() {return(lines.size());}
    void Line_add(Line temp) {lines.push_back(temp);}

    //read & write planes
    int Plane_n(int t) {return(planes[t].n);}
    std::vector<int> Plane_Line(int t) {return(planes[t].line);}
    int Plane_number(int t) {return(planes[t].num);}
    bool Plane_f(int t) {return(planes[t].f);}
    int Plane_size() {return(planes.size());}
    void Plane_add(Plane temp) {planes.push_back(temp);}
    void Plane_line_add(int t,int temp) {planes[t].line.push_back(temp);planes[t].num++;}// Note here t=t-1!!!!!!!!!!!!!! cause the sequence of array begins at 0. But to output is different.
//     void Set_Plane_Number(int t) {planes[t].num=planes[t].line.size();}

    //read & write volumes
    int Volume_n(int t) {return(volumes[t].n);}
    std::vector<int> Volume_Plane(int t) {return(volumes[t].plane);}
    int Volume_number(int t) {return(volumes[t].num);}
    bool Volume_f(int t) {return(volumes[t].f);}
    int Volume_size() {return(volumes.size());}
    void Volume_add(Volume temp) {volumes.push_back(temp);}
    void Volume_plane_add(int t,int temp) {volumes[t].plane.push_back(temp);volumes[t].num++;}//here,too.
//     void Set_Volume_Number(int t) {volumes[t].num=volumes[t].plane.size();}


};





#endif // H_geoclass
