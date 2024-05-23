#include "mod_bigcstab.h"


vector<double> BiCg (vector<double> U, struct Parameters data)
{
    vector<double> x(U);

    double rho(0), alpha(0), omega(0), beta(0);
    double tol(1e-14);

    vector<double> r(data.iEnd-data.iBeg+1, 0.0), r1(data.iEnd-data.iBeg+1, 0.0); // Etape 1 et 2
    vector<double> p(data.iEnd-data.iBeg+1, 0.0); // Etape 4
    vector<double> v(data.iEnd-data.iBeg+1, 0.0); // Etape 5.1
    vector<double> h(data.iEnd-data.iBeg+1, 0.0); // Etape 5.3
    vector<double> s(data.iEnd-data.iBeg+1, 1.0); // Etape 5.4
    vector<double> t(data.iEnd-data.iBeg+1, 0.0); // Etape 5.6

    r = Sum_Vect(U, Prod_Vect(Prod_MatVect(x, data), -1.0));
    r1 = Prod_Vect(r, 1.0);
    p = Prod_Vect(r, 1.0);
    rho = ProduitScalaire(r,r1);  

    while (Norme(r)>tol && Norme(s)>tol) {
        v = Prod_MatVect(p, data);                              
        alpha = rho/ProduitScalaire(r1,v);   
        h = Sum_Vect(x, Prod_Vect(p, alpha));                   
        s = Sum_Vect(r, Prod_Vect(v, -alpha));                  
        t = Prod_MatVect(s, data);                              
        omega = ProduitScalaire(t,s)/ProduitScalaire(t,t);      
        x = Sum_Vect(h, Prod_Vect(s, omega));
        r = Sum_Vect(s, Prod_Vect(t, -omega));
        beta = (ProduitScalaire(r1,r)/rho)*(alpha/omega);
        rho = ProduitScalaire(r1,r);
        p = Sum_Vect(r, Prod_Vect(Sum_Vect(p, Prod_Vect(v, -omega)), beta));
    }

    if (Norme(s)<tol) {      
        return h;
    }
    else {        
        return x;
    }
}