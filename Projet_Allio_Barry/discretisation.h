#ifndef DISCRETISATION_H
#define DISCRETISATION_H

#include <QObject>

#include "segment.h"
#include "courbeparametrique.h"
#include "courbebezier.h"
#include "carreauxbezier.h"

#include <cmath>

enum enum_methode {FRONT, DEFAULT};
enum type{homogene, heterogene};


class Discretisation
{

public:
    Discretisation();

    static std::vector<Point> discret_segment_seul(Segment S, float param);
    static std::vector<Point> discret_segments(std::vector<Segment> listSegments, float param);
    static std::vector<Point> discretiser_courbe(CourbeBezier *CB, int nbParam, int methode);
    static std::vector<Point> discretiser_carreaux_bezier(CarreauxBezier *carB, int nbParam1, int nbParam2, int sens);
    static std::vector<Point> discretiser_surface(CarreauxBezier *carB, int type,int nbParam1, int nbParam2);
};

#endif // DISCRETISATION_H
