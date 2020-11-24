#ifndef DISCRETISATION_H
#define DISCRETISATION_H

#include <QObject>

#include "segment.h"
#include "courbeparametrique.h"
#include "courbebezier.h"

#include <cmath>

enum enum_methode {FRONT, DEFAULT};

class Discretisation
{

public:
    Discretisation();

    static std::vector<Point> discret_segment_seul(Segment S, float param);
    static std::vector<Point> discret_segments(std::vector<Segment> listSegments, float param);
    static std::vector<Point> discretiser_courbe(CourbeBezier *CB, int nbParam, int methode);
};

#endif // DISCRETISATION_H
