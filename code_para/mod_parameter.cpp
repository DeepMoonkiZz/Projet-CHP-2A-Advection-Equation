#include "mod_parameter.h"


void read_parameters(struct Parameters *data) 
// Valide
{
    ifstream file("/home/segal/Documents/MatMeca/S8/CHP/Projet/parametres.txt");
    string line;
    while (std::getline(file, line)) {
        istringstream iss(line);
        string value;
        string key;
        if (iss >> key >> value) {
            if (key == "Cas") {
                data->Cas = stoi(value);
            } else if (key == "xmin") {
                data->xmin = stod(value);
            } else if (key == "xmax") {
                data->xmax = stod(value);
            } else if (key == "ymin") {
                data->ymin = stod(value);
            } else if (key == "ymax") {
                data->ymax = stod(value);
            } else if (key == "Tf") {
                data->Tf = stod(value);
            } else if (key == "Nx") {
                data->Nx = stoi(value);
            } else if (key == "Ny") {
                data->Ny = stoi(value);
            } else if (key == "CFL") {
                data->CFL = stod(value);
            } else if (key == "space_scheme") {
                data->space_scheme = stoi(value);
            } else if (key == "time_scheme") {
                data->time_scheme = stoi(value);
            }
        }
    }
    data->Lx = data->xmax - data->xmin;
    data->Ly = data->ymax - data->ymin;
    data->dx = data->Lx/(data->Nx-1.);
    data->dy = data->Ly/(data->Ny-1.);
    data->t = 0;
    data->iterations = 0;
}