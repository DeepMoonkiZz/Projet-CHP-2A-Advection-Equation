#include "mod_save_sol.h"


void Save_sol(vector<double> U, struct Parameters data, bool exact)
// Valide
{
    string fichier;
    if (exact) {
        if (data.Cas==1) {
            fichier = "Solutions/Cas_1/sol_ex" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
        else if (data.Cas==2) {
            fichier = "Solutions/Cas_2/sol_ex" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
        else if (data.Cas==3) {
            fichier = "Solutions/Cas_3/sol_ex" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
        else if (data.Cas==4) {
            fichier = "Solutions/Cas_4/sol_ex" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
        else {
            fichier = "Solutions/Cas_5/sol_ex" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
    }
    else {
        if (data.Cas==1) {
            fichier = "Solutions/Cas_1/sol" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
        else if (data.Cas==2) {
            fichier = "Solutions/Cas_2/sol" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
        else if (data.Cas==3) {
            fichier = "Solutions/Cas_3/sol" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
        else if (data.Cas==4) {
            fichier = "Solutions/Cas_4/sol" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
        else {
            fichier = "Solutions/Cas_5/sol" + std::to_string(data.iterations) + "." + std::to_string(data.proc) + ".dat";
        }
    }


    ofstream sol(fichier);
    if (sol.is_open()) {
        for (int i=data.iBeg; i<=data.iEnd; i++) {
            sol << data.xmin + data.dx * double(i%data.Nx) << " " << data.ymin + data.dy * double(i/data.Nx) << " " << U[i-data.iBeg] << endl;
        }
    } else {
        cout << "Erreur : Impossible d'ouvrir le fichier." << endl;
    }
    sol.close();
}


void Save_error(vector<pair<double, double>> error, struct Parameters data)
// Valide
{
    string fichier;
    if (data.Cas==1) {
        fichier = "Solutions/Cas_1/error.dat";
    }
    else if (data.Cas==2) {
        fichier = "Solutions/Cas_2/error.dat";
    }
    else if (data.Cas==3) {
        fichier = "Solutions/Cas_3/error.dat";
    }
    else if (data.Cas==4) {
        fichier = "Solutions/Cas_4/error.dat";
    }
    else {
        fichier = "Solutions/Cas_5/error.dat";
    }


    ofstream sol(fichier);
    if (sol.is_open()) {
        for (int i=0; i<error.size(); i++) {
            sol << error[i].first << " " << error[i].second << endl;
        }
    } else {
        cout << "Erreur : Impossible d'ouvrir le fichier." << endl;
    }
    sol.close();
}