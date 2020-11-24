#ifndef COURBEPARAMETRIQUE_H
#define COURBEPARAMETRIQUE_H

#include "point.h"
#include <vector>

class CourbeParametrique
{

private:

protected:
    std::vector<Point> ListePoint;

public:
    CourbeParametrique();
    CourbeParametrique(std::vector<Point> list);

    std::vector<Point> Liste_Point();
    void set_point_list(std::vector<Point> list);
    void add_point(Point P);
    Point eval(float t);

    void display_points_courbe();

};

#endif // COURBEPARAMETRIQUE_H
