#include "mod_parameter.h"

#include <cmath>


double Vitesse_X(double x, double y, double t, int cas);

double Vitesse_Y(double x, double y, double t, int cas);

double Sol_init(double x, double y, int cas);

double CFL(struct Parameters data);