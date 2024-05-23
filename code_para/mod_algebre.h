#include "mod_function.h"


vector<double> Compute_Coeff(int i, struct Parameters data);

vector<double> Prod_MatVect(vector<double> U, struct Parameters data);

double ProduitScalaire(vector<double> a, vector<double> b);

double Norme(vector<double> a);

vector<double> Sum_Vect(vector<double> u, vector<double> v);

vector<double> Prod_Vect(vector<double> u, double c);