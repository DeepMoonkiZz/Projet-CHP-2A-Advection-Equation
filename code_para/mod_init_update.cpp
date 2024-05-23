#include "mod_init_update.h"


vector<double> Initialisation(struct Parameters data)
{
    vector<double> U0(data.iEnd-data.iBeg+1, 0.0);

    for (int i=data.iBeg; i<=data.iEnd; i++) {
        U0[i-data.iBeg] = Sol_init(data.xmin + data.dx * double(i%data.Nx), data.ymin + data.dy * double(i/data.Nx), data.Cas);
    }

    return U0;
}


vector<double> Update(vector<double> U, struct Parameters *data)
{
    data->dt = CFL(*data);
    data->t = data->t + data->dt;
    data->iterations = data->iterations + 1;

    if (data->time_scheme==1) {
        U = Prod_MatVect(U, *data);
    }
    else if (data->time_scheme==2) {
        U = BiCg(U, *data);
    }
    else {
        cout << "Wrong time scheme" << endl;
        exit(0);
    }

    return U;
}