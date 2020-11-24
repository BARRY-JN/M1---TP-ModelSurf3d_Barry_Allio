#ifndef VISUALISATIONSEGMENTS_H
#define VISUALISATIONSEGMENTS_H

#include <vector>

#include <QObject>
#include <QWidget>
#include <QOpenGLFunctions>

#include "segment.h"

class VisualisationSegments
{
public:
    VisualisationSegments();
    std::vector<Point> list_points();
    std::vector<Segment> list_segments();
    std::vector<float> colors();

protected:
    std::vector<Point> ListePoint;
    std::vector<Segment> ListeSegment;
    std::vector<float> couleurs;

    void add_color(float r, float g, float b);

};

#endif
