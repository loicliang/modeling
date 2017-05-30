#ifndef H_geomod
#define H_geomod

#include "geo-io.h"

#define erreur 0.000001

class geomod: public fileinputoutput
{


double x0,x1,y0,y1;

std::vector<int> Lset;
public:

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // p2-priority-search-algorithm
       Node intersec_segment(Node p1,Node p2)
    {
        Node temp;
        if((p1.y-fun(p1.x))*(p2.y-fun(p2.x))>0) {temp.x=-1;temp.y=-1;temp.z=-1;temp.f=false;return temp;std::cout<<"what?"<<std::endl;}
        else{
                do{
                    temp.x=(p1.x+p2.x)/2.0;
                    temp.y=(p1.y+p2.y)/2.0;
                    temp.z=(p1.z+p2.z)/2.0;

                    if((temp.y-fun(temp.x))*(p2.y-fun(p2.x))<0)
                    {
                        p1=temp;

                    }
                    else
                    {
                        p2=temp;

                    }
                }while(fabs(temp.y-fun(temp.x))>=erreur and fabs(p1.x-p2.x)>=erreur and fabs(p1.y-p2.y)>=erreur);

            temp.f=true;
            temp.n=nodes.size()+1;
            return temp;
            }
    }

    void judge();

    void ABCDlookup();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void fxyminmax()
    {
//        int i,j;
//        double ymin,xmin,xmax;
//        ymin=999999.9; xmin=999999.9;xmax=-999999.9;
//        j=nodes.size();
//        for(i=0;i<j;i++)
//        {
//            if (nodes[i].y<ymin) ymin=nodes[i].y;
//             if (nodes[i].x<xmin) xmin=nodes[i].x;
//             if (nodes[i].x>xmax) xmax=nodes[i].x;
//        }
       y0=A.y;x0=A.x;x1=D.x;y1=D.y;
    }



    void chercher();

    void addJ2plastic();

};

void geomod::chercher()

{
    std::vector<int> lset;
    double bound;
    bound=y0;
//    if (nom=='y0') {bound=y0;}
//    if (nom=='x0') {bound=x0;}//useless now
//    if (nom=='x1') {bound=x1;}//useless now wobuzhidao zenme ba xhey tiqucheng muban, suoyi xiamian de panduanli zhiyou y
    int i,j;
    j=lines.size();
    for(i=0;i<j;i++)
    {
        if(lines[i].f==true)
        {
            if(nodes[lines[i].n1-1].y==bound && nodes[lines[i].n2-1].y==bound)
            {
                if(nodes[lines[i].n1-1].x<nodes[lines[i].n2-1].x) Lset.push_back(lines[i].n);
                else Lset.push_back(-lines[i].n);
            }

        }

    }



}


void geomod::judge()
{
     {
        int i,j,k,l,t;
        //double x,y;

        // deal with nodes
        t=Node_size();
        for(i=0;i<t;i++)
        {
            if (nodes[i].y>fun(nodes[i].x)) {nodes[i].f=false; }
        }
std::cout<<"nodes OK"<<std::endl;

        //deal with lines
        t=Line_size();
//std::cout<<t<<std::endl;
        for(i=0;i<t;i++)
        {
//           std::cout<<"line"<<i<<"OK"<<std::endl;
            if (nodes[lines[i].n1-1].f==true and nodes[lines[i].n2-1].f==true) {continue;}
            else if (nodes[lines[i].n1-1].f==false and nodes[lines[i].n2-1].f==false){lines[i].f=false;continue;}
            else if (nodes[lines[i].n1-1].f==true and nodes[lines[i].n2-1].f==false)
            {
 //               std::cout<<"gg"<<std::endl;
                Node temp;
                temp=intersec_segment(nodes[lines[i].n1-1],nodes[lines[i].n2-1]);
                Node_add(temp);
                lines[i].n2=temp.n;
                lines[i].edit=false;

            }
            else if (nodes[lines[i].n1-1].f==false and nodes[lines[i].n2-1].f==true)
            {
 //               std::cout<<"gg"<<std::endl;
                Node temp;
                temp=intersec_segment(nodes[lines[i].n1-1],nodes[lines[i].n2-1]);
                Node_add(temp);
                lines[i].n1=temp.n;
                lines[i].edit=false;
            }

        }
std::cout<<"lines OK"<<std::endl;
        // deal with planes
        t=Plane_size();
        bool checkflag,editflag;
        int top,bottom,topcreate,bottomcreate;
        for(i=0;i<t;i++)
        {
            //only if all the lines in a plane are deleted,delete this plane.(checkflag==false)
            //only edit those kept but incomplete planes(checkflag==true & editflag==true)
            checkflag=false;editflag=false;
            l=planes[i].line.size();
            for(j=0;j<l;j++)
            {
                if(lines[abs(planes[i].line[j])-1].f==true) checkflag=true;


                if(lines[abs(planes[i].line[j])-1].f==false or lines[abs(planes[i].line[j])-1].edit==false) editflag=true;



            }
            planes[i].f=checkflag;
            //end

            if(checkflag and editflag)
            {
                l=planes[i].line.size();
                for(k=0;k<l;k++)
                {
                    if(planes[i].line[k]>0)
                    {
                    top=lines[abs(planes[i].line[k])-1].n1;
                    bottom=lines[abs(planes[i].line[k])-1].n2;
                    }
                    else
                    {
                    top=lines[abs(planes[i].line[k])-1].n2;
                    bottom=lines[abs(planes[i].line[k])-1].n1;
                    }
                    if(top>n_initial) {topcreate=top;}
                    if(bottom>n_initial) {bottomcreate=bottom;}
                }
                j=Line_size()+1+bsplines.size();

               // Read_line(j,bottomcreate,topcreate);
               // Read_plane_line(i,j);


                    Read_line(j,bottomcreate,topcreate,L_min,i);


            }

        }
std::cout<<"planes OK"<<std::endl;

        //deal with volumes


    }

    fxyminmax();
    chercher();
    ABCDlookup();
}


void geomod::addJ2plastic()
{

    Node nw1(x0,-3400.0,0.0,nodes.size()+1);
    nodes.push_back(nw1);
    Node nw2(x1,-3400.0,0.0,nodes.size()+1);
    nodes.push_back(nw2);
    Line lw1(lines.size()+1,nw2.n,nw1.n);
    lines.push_back(lw1);
    Line lw2(lines.size()+1,nw1.n,A.n);
    lines.push_back(lw2);
    Line lw3(lines.size()+1,B.n,nw2.n);
    lines.push_back(lw3);

    Plane pw;

    pw.f=true;
    pw.n=planes.size()+1;
    pw.line=Lset;
    pw.line.push_back(lw1.n);
    pw.line.push_back(lw2.n);
    pw.line.push_back(lw3.n);
    pw.num=pw.line.size();

    planes.push_back(pw);
}

void geomod::ABCDlookup()
{
    int i,j;
    j=nodes.size();
    A=B=C=D=nodes[0];
    for(i=0;i<j;i++)
    {if(nodes[i].f==true)
    {
        //if(nodes[i].y>C.y || (fabs(nodes[i].y-C.y)<0.05 && nodes[i].x<C.x) ) C=nodes[i];
        //if(nodes[i].y>D.y || (fabs(nodes[i].y-D.y)<0.05 && nodes[i].x>D.x) ) D=nodes[i];
        if( (fabs(nodes[i].x-x0)<1) && nodes[i].y>C.y ) C=nodes[i];
        if( (fabs(nodes[i].x-x1)<1) && nodes[i].y>D.y ) D=nodes[i];

        if(nodes[i].y<=A.y && nodes[i].x<=A.x ) A=nodes[i];
        if(nodes[i].y<=B.y && nodes[i].x>=B.x) B=nodes[i];

    }
    }
std::cout<<C.x<<' '<<C.y<<std::endl;
std::cout<<D.x<<' '<<D.y<<' '<<D.n<<std::endl;
std::cout<<x0<<' '<<x1<<std::endl;
    nodes[C.n-1].x=x0;
    nodes[D.n-1].x=x1;
}

//void geomod::ABCDlookup()
//{
//    int i,j;
//    int Cn,Dn;
//    double dist,distc,distd;
//    dist=9999999.9;
//    j=nodes.size();
//    for(i=0;i<j;i++)
//    {if(nodes[i].f==true)
//    {
//        distc=dist_node(nodes[i],C);
//        distd=dist_node(nodes[i],D);
//        if(distc<dist) {Cn=i;dist=distc;}
//        if(distd<dist) {Dn=i;dist=distd;}
//
//    }
//    }
//    nodes[Cn].x=x0;
//    nodes[Dn].x=x1;
//    C=nodes[Cn];
//    D=nodes[Dn];
//}



#endif // H_geomod
