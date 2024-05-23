#include "mod_save_sol.h"


int main(int argc, char ** argv)
{
    int rank, nproc;    
    int iBeg, iEnd;

    Parameters data;
    read_parameters(&data);

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);


    charge(rank, data.Nx*data.Ny, nproc, &iBeg, &iEnd);
    data.iBeg = iBeg, data.iEnd = iEnd, data.proc = rank, data.nb_proc = nproc;

    double err(0);
    vector<double> U, U_ex;
    vector<pair<double, double>> error;


    // Calcul de U et U exact init
    U = Initialisation(data);
    U_ex = U_exacte(data);

    // Sauvegarde dans un fichier de U et U exact
    //Save_sol(U, data, false);
    //Save_sol(U_ex, data, true);

    // Calcul de l'erreur quadratique moyenne
    err = Error_quad_moy(U, U_ex, data.Nx*data.Ny);
    if (data.proc == 0) {
        error.push_back({data.t, err});
        cout << "t = " << data.t << endl;
    }
    
    while (data.t < data.Tf) {
    // Calcul de U et U exact au temps t
        U = Update(U, &data);
        U_ex = U_exacte(data);
        
    // Sauvegarde dans un fichier de U et U exact
        //Save_sol(U, data, false);
        //Save_sol(U_ex, data, true);

    // Calcul de l'erreur quadratique moyenne
        err = Error_quad_moy(U, U_ex, data.Nx*data.Ny);
        if (data.proc==0) {
            error.push_back({data.t, err});
            cout << "t = " << data.t << endl;
        }
    }

    if (data.proc == 0) {
        Save_error(error, data);
    }

    MPI_Finalize();

    return 0;
}