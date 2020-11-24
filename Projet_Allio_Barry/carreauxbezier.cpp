#include "carreauxbezier.h"
#include "discretisation.h"
#include <QDebug>
#include <cmath>

CarreauxBezier::CarreauxBezier()
{

}

////////////Vieille Méthode
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

/////////Nouvelle méthode


CarreauxBezier::CarreauxBezier(int degreN, int degreM)
{
    N = degreN;
    M = degreM;
    ListePoints.clear();
    ListePoints = Pol_Contr_Aleatoire(ordre);
    generer_carreaux(0, 4, 4);
}

int random(int min, int max)
{
    int rand=qrand()%((max+1)-min)+min;
    return rand;
}

//Polygone de controle de degré 3 aléatoire
vector<vector<Point>> CarreauxBezier::Pol_Contr_Aleatoire(bool desordre)
{  
    vector<vector<Point>> list(N, vector<Point>(M));
    float xp, yp, zp;
    Point X;
    qsrand(time(NULL));

    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++) {
            if (desordre){
                xp = random(-100, 100) / 100;
                yp = random(-100, 100) / 100;
                zp = random(-100, 100) / 100;
            }else{
                int min = (j*50)-200;
                int max = (j*50)-100;
                xp = float(random((i*50)+min, (i*50)+max)) / 100;
                yp = float(random(min+50, max+50)) / 100;
                zp = float(random(min, max)) / 100;
            }
            X.set(xp, yp, zp);
            list[i][j] = X;
        }
    }
    return list;
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

vector<vector<Point>> list_to_tab(std::vector<Point> liste, int n, int m, int begin)
{
    vector<vector<Point>> tab(n, vector<Point>(m));
    int k=begin;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            tab[i][j] = liste[k];
            k++;
            qDebug()<<"\ttab["<<i<<"]["<<j<<"]="<<tab[i][j].getX()<<tab[i][j].getY()<<tab[i][j].getZ();
        }
    }
    return tab;
}

void CarreauxBezier::generer_carreaux(int methode, float nbU, float nbV)
{
    NbU = nbU;
    NbV = nbV;
    vector<Point> liste = Discretisation::discretiser_surface(this,methode, NbU, NbV);
    //vector<Point> liste = Discretisation::discretiser_surface(this,homogene, _nbU, _nbV);
    Carreaux.clear();
    Carreaux = list_to_tab(liste, nbU, nbV, 0);
}

vector<vector<Point>> CarreauxBezier::coordsCarreaux(){ return Carreaux; }

vector<vector<Point>> CarreauxBezier::coords(){ return ListePoints; }

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
    qDebug() << "Points de controle :";
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<M; j++)
        {
            qDebug() << "ListePoint["<<i<<"]["<<j<<"]="<<ListePoints[i][j].getX()<<ListePoints[i][j].getY()<<ListePoints[i][j].getZ();
        }
    }
    qDebug() << "Carreaux :";
    for (int i=0; i<NbU; i++)
    {
        for (int j=0; j<NbV; j++)
        {
            qDebug() << "CoordCarreaux["<<i<<"]["<<j<<"]="<<Carreaux[i][j].getX()<<Carreaux[i][j].getY()<<Carreaux[i][j].getZ();
        }
    }
}










