#include "carreauxbezier.h"
#include <QDebug>
#include <cmath>

CarreauxBezier::CarreauxBezier()
{

}

CarreauxBezier::CarreauxBezier(vector<vector<Point>> tab, int degreN, int degreM)
{
    N = degreN;
    M = degreM;
    ListePoints.clear();
    ListePoints = Set_Liste_Points(tab, degreN, degreM);
}

vector<vector<Point>> CarreauxBezier::Set_Liste_Points(vector<vector<Point> > tab, int n, int m)
{
    vector<vector<Point>> liste(n, vector<Point>(m));
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            liste[i][j] = tab[i][j];
        }
    }
    return tab;
}

vector<vector<Point>> CarreauxBezier::Liste_Points()
{
    return ListePoints;
}



Point CarreauxBezier::eval(float u, float v)
{
    if (u>0 && u<1 && v>0 && v<1) {
        Point P;
        float xp=0, yp=0, zp=0, Berst=0, Berst2=0;
        for (int i=0; i<N; i++)
        {
            Berst = Berstein(N-1, i, u);
            for (int j=0; j<M; j++)
            {
                Berst2= Berstein(M-1, j, v);
                xp+= Berst * Berst2 * ListePoints[i][j].getX();
                yp+= Berst * Berst2 * ListePoints[i][j].getY();
                zp+= Berst * Berst2 * ListePoints[i][j].getZ();
            }
        }
        P.set(xp, yp, zp);
        return P;
    }else{exit (1);}

}


void CarreauxBezier::display_points()
{
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<M; j++)
        {
            qDebug() << "ListePoint["<<i<<"]["<<j<<"]="<<ListePoints[i][j].getX()<<ListePoints[i][j].getY()<<ListePoints[i][j].getZ();
        }
    }
}










