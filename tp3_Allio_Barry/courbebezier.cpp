
#include "courbebezier.h"

#include <qdebug.h>
#include <cmath>

CourbeBezier::CourbeBezier()
{

}

CourbeBezier::CourbeBezier(std::vector<Point> list)
{
    set_point_list(list);
}

void CourbeBezier::display_points_controle()
{
    display_points_courbe();
}

int factorielle(int nb)
{
    if(nb==0) return 1;
    int val=1;
    for (int i=1; i<=nb; i++)
    {
       val=val*i;
    }
    return val;
}

float Berstein(int n, int i, float t)
{
    float a = factorielle(n);
    float b = factorielle(i) * factorielle(n-i);
    float c = pow(t, i) * pow(1-t, n-i);
    a = a / b;
    return a * c;
}

Point CourbeBezier::eval(float t)
{
    if (t>0 && t<1) {
        int degre = ListePoint.size()-1;

        float xP=0, yP=0, zP=0, pB;
        for (int i=0; i<=degre; i++)
        {
            pB = Berstein(degre, i, t);
            xP += pB * ListePoint[i].getX();
            yP += pB * ListePoint[i].getY();
            zP += ListePoint[i].getZ();
        }
        Point P;
        P.setX(xP);
        P.setY(yP);
        return P;
    }else{exit(1);}
}


Point CourbeBezier::eval_deriv(float t, float e)
{
    if (t>0 && t<1) {

        exit (1);

        Point Pt = eval(t);
        Point Pe = eval(t+e);

        Point P;
        P.setX(Pe.getX()-Pt.getX());
        P.setY(Pe.getY()-Pt.getY());
        P.setZ(Pt.getZ());
        return P;
    }else{exit(1);}
}
