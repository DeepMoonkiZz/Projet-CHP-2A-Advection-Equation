#include "mod_save_sol.h"


int main(int argc, char ** argv)
{
    Parameters data;
    vector<double> U;

    read_parameters(&data);

    U = Initialisation(data);
    Save_sol(U, data);
    cout << "t = " << data.t << endl;
    
    while (data.t < data.Tf) {
        U = Update(U, &data);
        Save_sol(U, data);
        cout << "t = " << data.t << endl;
    }

    return 0;
}