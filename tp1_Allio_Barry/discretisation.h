#ifndef DISCRETISATION_H
#define DISCRETISATION_H

#include <QObject>

#include "segment.h"

class Discretisation
{

public:
    Discretisation();

    static std::vector<Point> discret_segment_seul(Segment S, float param);
    static std::vector<Point> discret_segments(std::vector<Segment> listSegments, float param);

};

#endif // DISCRETISATION_H
