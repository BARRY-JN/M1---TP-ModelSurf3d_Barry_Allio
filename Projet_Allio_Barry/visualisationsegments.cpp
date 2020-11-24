#include "visualisationsegments.h"

VisualisationSegments::VisualisationSegments()
{
    Point A;
    A.set (0.f, 0.f, 0.f);
    ListePoint.push_back(A);
    add_color(1.f, 0.f, 0.f);
    Point B;
    B.set(1.f, 0.f, 0.f);
    ListePoint.push_back(B);
    add_color(1.f, 0.f, 0.f);
    Segment S1;
    S1.setStart(A);
    S1.setEnd(B);
    ListeSegment.push_back(S1);
}

std::vector<Point> VisualisationSegments::list_points()
{
    return ListePoint;
}

std::vector<Segment> VisualisationSegments::list_segments()
{
    return ListeSegment;
}

std::vector<float> VisualisationSegments::colors()
{
    return couleurs;
}

void VisualisationSegments::add_color(float r, float g, float b)
{
    couleurs.push_back(r);
    couleurs.push_back(g);
    couleurs.push_back(b);
}












