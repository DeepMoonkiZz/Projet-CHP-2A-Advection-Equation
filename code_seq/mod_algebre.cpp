#include "mod_algebre.h"
#include <chrono>
#include <thread>


vector<double> Compute_Coeff(int i, struct Parameters data)
{
    double alpha(0.), beta(0.);
    vector<double> Coeff(5, 0.);

    alpha = Vitesse_X(data.xmin + data.dx * double(i%data.Nx), data.ymin + data.dy * double(i/data.Nx), data.t, data.Cas) * data.dt/data.dx;
    beta = Vitesse_Y(data.xmin + data.dx * double(i%data.Nx), data.ymin + data.dy * double(i/data.Nx), data.t, data.Cas) * data.dt/data.dy;

    if (data.space_scheme == 1) {
        if (data.time_scheme == 1) {
            Coeff[0] = 1;
            Coeff[1] = -alpha/2.;
            Coeff[2] = alpha/2.;
            Coeff[3] = -beta/2.;
            Coeff[4] = beta/2.;
        }
        else if (data.time_scheme == 2) {
            Coeff[0] = 1.;
            Coeff[1] = alpha/2.;
            Coeff[2] = -alpha/2.;
            Coeff[3] = beta/2.;
            Coeff[4] = -beta/2.;
        }
        else {
            cout << "Error with time scheme" << endl;
            exit(0);
        }
    }
    else if (data.space_scheme == 2) {
        Coeff[0] = 1.;
        if (data.time_scheme == 1) {
            if (alpha >= 0) {
                Coeff[0] = Coeff[0] - alpha;
                Coeff[2] = alpha;
            }
            else {
                Coeff[0] = Coeff[0] + alpha;
                Coeff[1] = -alpha;
            }
            if (beta >= 0) {
                Coeff[0] = Coeff[0] - beta;
                Coeff[4] = beta;
            }
            else {
                Coeff[0] = Coeff[0] + beta;
                Coeff[3] = -beta;
            }        
        }
        else if (data.time_scheme == 2) {
            if (alpha >= 0) {
                Coeff[0] = Coeff[0] + alpha;
                Coeff[2] = -alpha;
            }
            else {
                Coeff[0] = Coeff[0] - alpha;
                Coeff[1] = alpha;
            }
            if (beta >= 0) {
                Coeff[0] = Coeff[0] + beta;
                Coeff[4] = -beta;
            }
            else {
                Coeff[0] = Coeff[0] - beta;
                Coeff[3] = beta;
            }    
        }
        else {
            cout << "Error with time scheme" << endl;
            exit(0);
        }
    }
    else {
        cout << "Error with space scheme" << endl;
        exit(0);
    }

    return Coeff;
}


vector<double> Prod_MatVect(vector<double> U, struct Parameters data)
{
    vector<double> U_update(U.size(), 0.);
    vector<double> Coeff(5, 0.);

    for (int i=0; i<U.size(); i++) {
        Coeff = Compute_Coeff(i, data);
        U_update[i] = Coeff[0]*U[i] + \
                      Coeff[1]*U[(i+1) % data.Nx == 0 ? i-data.Nx+1 : i+1] + \
                      Coeff[2]*U[i % data.Nx == 0 ? i+data.Nx-1 : i-1] + \
                      Coeff[3]*U[(i + data.Nx) % (data.Nx*data.Ny)] + \
                      Coeff[4]*U[i - data.Nx < 0 ? (data.Nx-1)*data.Ny + i -1 : i-data.Nx];
    }

    return U_update;
}


double ProduitScalaire(vector<double> a, vector<double> b) 
{
    double pscal(0.0);

    for (int k = 0; k < a.size(); k++) 
    {
        pscal += a[k]*b[k];
    }

    return pscal;
}

double Norme(vector<double> a)
{
    double ps(0.0),norme(0.0);

    ps = ProduitScalaire(a,a);
    norme = sqrt(ps);

    return norme;
}


vector<double> Sum_Vect(vector<double> u, vector<double> v)
{
    vector<double> sum(u.size(), 0.0);

    for (int i=0; i<u.size(); i++) {
        sum[i] = u[i] + v[i];
    }
    
    return sum;
}

vector<double> Prod_Vect(vector<double> u, double c)
{
    vector<double> prod(u.size(), 0.0);
    
    for (int i=0; i<u.size(); i++) {
        prod[i] = c*u[i];
    }
    
    return prod;
}