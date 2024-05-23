#include "mod_save_sol.h"


void Save_sol(vector<double> U, struct Parameters data)
// Valide
{
    string fichier;
    if (data.Cas==1) {
        fichier = "Solutions/Cas_1/sol" + std::to_string(data.iterations) + ".dat";
    }
    else if (data.Cas==2) {
        fichier = "Solutions/Cas_2/sol" + std::to_string(data.iterations) + ".dat";
    }
    else if (data.Cas==3) {
        fichier = "Solutions/Cas_3/sol" + std::to_string(data.iterations) + ".dat";
    }
    else if (data.Cas==4) {
        fichier = "Solutions/Cas_4/sol" + std::to_string(data.iterations) + ".dat";
    }
    else {
        fichier = "Solutions/Cas_5/sol" + std::to_string(data.iterations) + ".dat";
    }

    ofstream sol(fichier);
    if (sol.is_open()) {
        for (int i=0; i<U.size(); i++) {
            sol << data.xmin + data.dx * double(i%data.Nx) << " " << data.ymin + data.dy * double(i/data.Nx) << " " << U[i] << endl;
        }
        sol.close();
    } else {
        cerr << "Erreur : Impossible d'ouvrir le fichier." << endl;
    }
}