#include "mod_algebre.h"


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
    vector<double> U_update(U.size(), 0.), U_plus_in(U.end() - data.Nx, U.end()), U_moins_in(U.begin(), U.begin() + data.Nx), U_plus_out(data.Nx, 0.0), U_moins_out(data.Nx, 0.0);
    vector<double> Coeff(5, 0.), U_combined(2*data.Nx + U.size(), 0.0);

    // Send au proc supérieur 
    MPI_Sendrecv(&U_moins_in[0], data.Nx, MPI_DOUBLE, (data.nb_proc + data.proc - 1) % data.nb_proc, data.proc,
                &U_plus_out[0], data.Nx, MPI_DOUBLE, (data.nb_proc + data.proc + 1) % data.nb_proc, (data.nb_proc + data.proc + 1) % data.nb_proc,
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Sendrecv(&U_plus_in[0], data.Nx, MPI_DOUBLE, (data.nb_proc + data.proc + 1) % data.nb_proc, data.nb_proc + data.proc,
                &U_moins_out[0], data.Nx, MPI_DOUBLE, (data.nb_proc + data.proc - 1) % data.nb_proc, data.nb_proc + (data.nb_proc + data.proc - 1) % data.nb_proc,
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    copy(U_moins_out.begin(), U_moins_out.end(), U_combined.begin());
    copy(U.begin(), U.end(), U_combined.begin() + U_moins_out.size());
    copy(U_plus_out.begin(), U_plus_out.end(), U_combined.begin() + U_moins_out.size() + U.size());

    for (int i=data.iBeg; i<=data.iEnd; i++) {
        Coeff = Compute_Coeff(i, data);

        int i_loc(i-data.iBeg+data.Nx);

        U_update[i-data.iBeg] = Coeff[0]*U_combined[i-data.iBeg+data.Nx] + \
                      Coeff[1]*U_combined[(i+1) % data.Nx == 0 ? i_loc-data.Nx+1 : i_loc+1] + \
                      Coeff[2]*U_combined[i % data.Nx == 0 ? i_loc+data.Nx-1 : i_loc - 1] + \
                      Coeff[3]*U_combined[i_loc + data.Nx] + \
                      Coeff[4]*U_combined[i_loc - data.Nx];
    }
   
    return U_update;
}


double ProduitScalaire(vector<double> a, vector<double> b) 
{
    double pscal_loc(0.0), pscal(0.0);

    for (int k = 0; k < a.size(); k++) 
    {
        pscal_loc += a[k]*b[k];
    }

    MPI_Allreduce(&pscal_loc, &pscal, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

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