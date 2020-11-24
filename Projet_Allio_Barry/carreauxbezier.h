#ifndef CARREAUXBEZIER_H
#define CARREAUXBEZIER_H

#include <vector>
#include "point.h"

using namespace std;
enum tri{ordre, desordre};

class CarreauxBezier
{
public:
    CarreauxBezier();
    //old
    CarreauxBezier(vector<vector<Point> > tab, int degreN, int degreM);
    //new
    CarreauxBezier(int degreN, int degreM);

    vector<vector<Point> > Liste_Points();
    vector<vector<Point>> Set_Liste_Points(vector<vector<Point>> tab, int n, int m);

    Point eval(float u, float v);
    void display_points();

    void generer_carreaux(int methode, float nbU, float nbV);

    vector<vector<Point>> coords();
    vector<vector<Point>> coordsCarreaux();

protected:
    //Points de controle
    vector<vector<Point>> ListePoints;
    int N=0;
    int M=0;


    //Carreaux
    vector<vector<Point>> Carreaux;
    float NbU=0; //lignes
    float NbV=0; //colonnes


    vector<vector<Point>> Pol_Contr_Aleatoire(bool desordre);

};

#endif // CARREAUXBEZIER_H
