#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include "courbeparametrique.h"

class CourbeBezier : public CourbeParametrique
{
public:
    CourbeBezier ();
    CourbeBezier (std::vector<Point> list);

    void display_points_controle();

    Point eval(float t);
    Point eval_deriv(float t, float e);

};

#endif
