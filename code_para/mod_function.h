#include "mod_parameter.h"

#include <mpich/mpi.h>

#include <cmath>
#include <vector>


double Vitesse_X(double x, double y, double t, int cas);

double Vitesse_Y(double x, double y, double t, int cas);

double Sol_init(double x, double y, int cas);

double CFL(struct Parameters data);

double Error_quad_moy(vector<double> U, vector<double> U_ex, int n);

vector<double> U_exacte (struct Parameters data);

