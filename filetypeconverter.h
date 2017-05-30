#ifndef H_filetypeconverter
#define H_filetypeconverter

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>

class filetypeconverter
{
public:
    void geofile(std::string geo,std::string geomod)
    {
        std::ifstream fin;
        std::ofstream fout;
        fin.open(geo+".geo");
        fout.open(geomod+".dat");
        char ch;
        while (fin.get(ch))
        {
            if (ch<='9' and ch>='0') {fout<<ch;}
            else if (ch<='z' and ch>='a') {fout<<ch;}
            else if (ch<='Z' and ch>='A') {fout<<ch;}
            else
            {
                switch(ch)
                {
                    case('.') :
                        fout<<ch;
                        break;
                    case(' '):
                        fout<<ch;
                        break;
                    case('\n'):
                        fout<<ch;
                        break;
                    case('-'):
                        fout<<ch;
                        break;
                    default:
                        fout<<' ';
                        break;

                }
            }
        }
        fin.close();
        fout.close();
    }

};
#endif
