#include "mod_function.h"


double Vitesse_X(double x, double y, double t, int cas)
// Valide
{
    switch (cas) {
        case 1:
            return 1.0;
        case 2:
            return 0.5;
        case 3:
            return -y;
        default:
            cout << "Erreur dans le numéro du cas" << endl;
            exit(0);
    }
}


double Vitesse_Y(double x, double y, double t, int cas)
// Valide
{
    switch (cas) {
        case 1:
            return 0.0;
        case 2:
            return 0.5;
        case 3:
            return x;
        default:
            cout << "Erreur dans le numéro du cas" << endl;
            exit(0);
    }
}


double Sol_init(double x, double y, int cas)
// Valide
{
    switch (cas) {
        case 1:
            return exp(-x*x/0.0075 - y*y/0.0075);
        case 2:
            if (sqrt(x*x + y*y)<=0.4) {
                return 1;
            }
            else {
                return 0;
            }
        case 3:
            if (sqrt((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5))<=0.4) {
                return 1;
            }
            else {
                return 0;
            }
        default:
            cout << "Erreur dans le numéro du cas" << endl;
            exit(0);
    }
}


double CFL(struct Parameters data)
{
    if (data.time_scheme==1) {
        if (data.space_scheme==1) {
            cout << "Schéma centré explicit non stable veuillez choisir un autre schéma" << endl;
            exit(0);
        }
        else {
            double Vmax(0), Vx(0), Vy(0);
            for (int i=0; i<data.Nx; i++) {
                for (int j=0; j<data.Ny; j++) {
                    Vx = Vitesse_X(data.xmin+i*data.dx, data.ymin+j*data.dy, data.t, data.Cas);
                    Vy = Vitesse_Y(data.xmin+i*data.dx, data.ymin+j*data.dy, data.t, data.Cas);
                    if(sqrt(Vx*Vx + Vy*Vy) > Vmax) {
                        Vmax = sqrt(Vx*Vx + Vy*Vy);
                    }
                }
            }
            return data.CFL*min(data.dx, data.dy)/Vmax;
        }
    }
    else {
        return 0.01;
    }
}