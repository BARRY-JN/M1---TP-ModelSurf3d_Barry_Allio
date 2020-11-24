#ifndef CARREAUXBEZIER_H
#define CARREAUXBEZIER_H

#include <vector>
#include "point.h"

using namespace std;

class CarreauxBezier
{
public:
    CarreauxBezier();
    CarreauxBezier(vector<vector<Point> > tab, int degreN, int degreM);

    vector<vector<Point> > Liste_Points();
    vector<vector<Point>> Set_Liste_Points(vector<vector<Point>> tab, int n, int m);

    float Berstein(int n, int i, float t);
    Point eval(float u, float v);

    void display_points();

protected:
    vector<vector<Point>> ListePoints;
    int N=0;
    int M=0;

};

#endif // CARREAUXBEZIER_H
