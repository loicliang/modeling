#ifndef H_geo_io
#define H_geo_io
#define MIN(a,b) (((a)<(b)) ? a : b)
#define MAX(a,b) (((a)>(b)) ? a : b)
#include "geoclass.h"


double fun(double x);

class fileinputoutput: public geometry
{
protected:
    int LC;
    int L_min;
    int Scale;
    Node A;//xmin & ymin;
    Node B;//xmax & ymin;
    Node C;//xmin & ymax;
    Node D;//xmax & ymax;
public:
    void parameterdef(int lc=3,int lmin=1,int scale=1000)
    {
        LC=lc;
        L_min=lmin;
        Scale=scale;
    }
    void Read_node(int n, double x,double y,double z)
    {
        Node temp;
        temp.n=n; temp.x=x;temp.y=y;temp.z=z;temp.f=true;
        Node_add(temp);
    }
    void Read_line(int n, int n1, int n2)
    {
        Line temp;
        temp.n=n; temp.n1=n1;temp.n2=n2;temp.f=true;temp.edit=true;
        Line_add(temp);
    }

    void Read_line(int n,int n1,int n2,int ncc,int pn)
    {
        double x,y;int nc;
        Line ltemp;
        Node head,temp,tail;
        nc=floor(abs(Node_x(n1-1)-Node_x(n2-1))/ncc)+1;
        if((Node_x(n1-1)-Node_x(n2-1))<0) {head=nodes[n1-1];tail=nodes[n2-1];}
        else {head=nodes[n2-1];tail=nodes[n1-1];}

        for(int i=0;i<nc-2;i++)
            {
                x=(fabs(Node_x(n1-1)-Node_x(n2-1)))/(nc-1)*(i+1)+MIN(Node_x(n1-1),Node_x(n2-1));
                //edited shape control function!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


                //y=fun(x)+(((i+1)%2)*2-1)*rough;

                y=fun(x);

                temp.x=x;temp.y=y;temp.z=0.0;temp.f=true;
                temp.n=Node_size()+1;
                Node_add(temp);
                ltemp.n=Line_size()+1;ltemp.f=true;ltemp.n1=head.n;ltemp.n2=temp.n;
                Line_add(ltemp);
                Plane_line_add(pn,ltemp.n);
                head=temp;
            }
            ltemp.n=Line_size()+1;ltemp.f=true;ltemp.n1=head.n;ltemp.n2=tail.n;
            Line_add(ltemp);
            Plane_line_add(pn,ltemp.n);


    }


    void Read_plane(int n)
    {
        Plane temp;
        temp.n=n;temp.num=0;temp.f=true;
        Plane_add(temp);
    }
    void Read_plane_line(int n,int temp)
    {
        Plane_line_add(n,temp);

    }
    void Read_volume(int n)
    {
        Volume temp;
        temp.n=n;temp.num=0;temp.f=true;
    }
    void Read_volume_plane(int n,int num)
    {
        Volume_plane_add(n,num);
    }

// deal with an entire line of input
    void InputLineGeoMod(std::string temp);


    void InputGeo(std::string geoname);


    void OutputGeo(std::string geoname);                     // to be modified,  'cause not consider yet the singular case,  i.e. sphline..................................


};






void fileinputoutput::OutputGeo(std::string geoname)
{
    {

        std::ofstream fout;
        fout.open(geoname+".geo");
        int i, iend, j,k;
        std::vector<int> tt;
        iend = Node_size();
        for (i = 0;i<iend-2;i++)
            {
                if (Node_f(i))
                fout << "Point (" << Node_n(i) << ") = {" <<Node_x(i)/Scale << ',' << Node_y(i)/Scale << ',' << Node_z(i)/Scale<<','<<LC*1.0/Scale << "};" << std::endl;

            }
        for (i = iend-2;i<iend;i++)
            {
                if (Node_f(i))
                fout << "Point (" << Node_n(i) << ") = {" <<Node_x(i)/Scale << ',' << Node_y(i)/Scale << ',' << Node_z(i)/Scale<<','<<LC*1.0<< "};" << std::endl;

            }

        iend = Line_size();
        for (i = 0;i<iend;i++)
            {
                if (Line_f(i))
                {
                    fout << "Line (" << Line_n(i) << ") = {" <<Line_n1(i) << ',' << Line_n2(i) << "};" << std::endl;
                }

            }

        iend=bsplines.size();
        for(i=0;i<iend;i++)
            {
                if (bsplines[i].f)
                {
                    fout << "BSpline (" << bsplines[i].n << ") = {"<<bsplines[i].bspoint[0] ;
                    for(j=1;j<bsplines[i].bsp_control;j++)
                    {
                      fout<<','<<bsplines[i].bspoint[j];
                    }
                     fout<< "};" << std::endl;
                }



            }


        iend = Plane_size();
        for (i = 0;i<iend;i++)
            {
                if (Plane_f(i))
                {
                fout << "Line Loop (" << Plane_n(i) <<") = {";
                tt = Plane_Line(i);
                k=0;
                for (j = 0;j<Plane_number(i);j++)
                    {
                        if (Line_f(abs(tt[j])-1))
                        {
                            if (k == 0) {fout << tt[j];k++;}
                            else {fout << ','<< tt[j];k++;}
                        }
                    }
                fout << "};" << std::endl;
                fout << "Plane Surface ("<<Plane_n(i)<<") = {"<<Plane_n(i)<<"}; Physical Surface ("<<Plane_n(i)<<") = {"<<Plane_n(i)<<"};" << std::endl;
                }

            }

        // not yet deal with the volume!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        iend = Volume_size();
        /*




        */


        fout.close();
    }

}








void fileinputoutput::InputGeo(std::string geoname)
{
        {
        std::ifstream fin;
        fin.open(geoname+".dat");
        std::string FileLine;

        while (getline(fin,FileLine))
        {
            InputLineGeoMod(FileLine);
        }
        //set initial number of geo
        n_initial=Node_size();
        l_initial=Line_size();
        p_initial=Plane_size();
        v_initial=Volume_size();
        fin.close();
    }
}






void fileinputoutput::InputLineGeoMod(std::string temp)

{
        {
        if(temp.find("Point")!=std::string::npos)
        {
            std::istringstream ins;
            ins.str(temp);
            std::string t; int n; double x,y,z;
            ins >> t >> n >> x >> y >> z;
            Read_node(n,(double)x,(double)y,(double)z);
            if(x<=A.x && y<=A.y) A=nodes[n-1];
            if(x>B.x && y<=B.y) B=nodes[n-1];
            if(x<=C.x && y>=C.y) C=nodes[n-1];
            if(x>=D.x && y<=D.y) D=nodes[n-1];

        }
        else if(temp.find("Line")!=std::string::npos and temp.find("Loop")==std::string::npos)
        {
            std::istringstream ins;
            ins.str(temp);
            std::string t; int n,n1,n2;
            ins >> t >> n >> n1 >> n2;
            Read_line(n,n1,n2);
        }
        else if(temp.find("Line")!=std::string::npos and temp.find("Loop")!=std::string::npos)
        {
            std::istringstream ins;
            ins.str(temp);
            std::string t; int n,ntemp;
            ins>> t;
            ins>> t;
            ins>> n;
            Read_plane(n);
            while (ins>>ntemp)
                {
                    Read_plane_line(n-1,ntemp);
                }
        }
        else if (temp.find("Surface")!=std::string::npos)    // to be modified,  'cause not tried yet with 3d model .........................................................
        {
            std::istringstream ins;
            ins.str(temp);
        /*
            std::string t; int n,ntemp;
            ins>> t;
            ins>> t;
            ins>> n;
            Read_volume(n);
            while (ins>>ntemp)
                {
                    Read_plane_line(n-1,ntemp);
                }




        */
        }
        else {return;}
    }
//end InputGeofile
}

#endif // H_geo
