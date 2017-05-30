#include "filetypeconverter.h"
#include "point3.h"
#include "geomod.h"

int main(int argc, char *argv[])
{
    std::string name1, name2;
    name1 = "123";

    std::ifstream ffin;
    ffin.open("temp.txt",std::ios::in);
    getline(ffin,name1);
    ffin.close();

    std::cout<<name1<<"GGG"<<std::endl;


    name2 = name1+"mod";

    filetypeconverter test;
    test.geofile(name1,name2);



    int ch_length,ch_lc;
    ch_length=5;
    ch_lc=1;

    if(argc<2)
    {
        ch_length=5;
        ch_lc=1;
    }
    else if(argc==2)
    {

    std::stringstream ss;
    ss<<argv[1];
    ss>>ch_length;
    ss.clear();
    ch_lc=1;
    }
    else if(argc==3)
    {
    std::stringstream ss;
    ss<<argv[1];
    ss>>ch_length;
    ss.clear();
    ss<<argv[2];
    ss>>ch_lc;
    ss.clear();

    }



    geomod test2;
    test2.InputGeo(name2);



    test2.parameterdef(ch_length,ch_lc,1000);//1st characteristic length,2nd range of points,3rd scale

    test2.judge();
    test2.addJ2plastic();

    test2.OutputGeo(name2);






    return 0;
}


double fun(double x)
{
    double y;
    if(x<=1950 and x>=1550)
    {
        y=599.9000-fabs((double)std::sqrt(40000-(x-1750)*(x-1750)));
    }
    else if(x<=2450 and x>=2050)
    {
        y=599.9000-fabs((double)std::sqrt(40000-(x-2250)*(x-2250)));
    }
    else
        y=599.9000;
    return y;
}
//
//double fun(double x)
//
//{
//    double y;
//    y=599.9000;
//    return y;
//}
//



//double fun(double x)
//
//    {
//        double y;
//        if(x<=450 and x>=50)
//        {
//            y=599.9-(double)std::sqrt(40000-(x-250)*(x-250));
//        }
//        else if(x<=950 and x>=550)
//        {
//            y=599.9-(double)std::sqrt(40000-(x-750)*(x-750));
//        }
//        else if(x<=1450 and x>=1050)
//        {
//            y=599.9-(double)std::sqrt(40000-(x-1250)*(x-1250));
//        }
//        else if(x<=1950 and x>=1550)
//        {
//            y=599.9-(double)std::sqrt(40000-(x-1750)*(x-1750));
//        }
//        else if(x<=2450 and x>=2050)
//        {
//            y=599.9-(double)std::sqrt(40000-(x-2250)*(x-2250));
//        }
//        else if(x<=2950 and x>=2550)
//        {
//            y=599.9-(double)std::sqrt(40000-(x-2750)*(x-2750));
//        }
//        else if(x<=3450 and x>=3050)
//        {
//            y=599.9-(double)std::sqrt(40000-(x-3250)*(x-3250));
//        }
//        else if(x<=3950 and x>=3550)
//        {
//            y=599.9-(double)std::sqrt(40000-(x-3750)*(x-3750));
//        }
//        else
//            y=599.9;
//
//        //y=0.9+0.09*x;
//        return y;
//    }
