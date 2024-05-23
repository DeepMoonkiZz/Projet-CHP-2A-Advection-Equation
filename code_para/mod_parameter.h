#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


struct Parameters 
{
    int Cas;

    double xmin;
    double xmax;
    double ymin;
    double ymax;

    int Nx;
    int Ny;

    double dx;
    double dy;
    double Lx;
    double Ly;

    double dt; 
    double Tf;
    
    int space_scheme;
    int time_scheme;

    double t;
    int iterations;
    double CFL;

    int iBeg;
    int iEnd;
    int proc;
    int nb_proc;
};


void read_parameters(struct Parameters *data);