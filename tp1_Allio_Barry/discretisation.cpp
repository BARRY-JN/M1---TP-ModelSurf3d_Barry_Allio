#include "discretisation.h"
#include <QDebug>

Discretisation::Discretisation()
{

}

std::vector<Point> Discretisation::discret_segment_seul(Segment S, float param)
{
    std::vector<Point> listPoint;
    float debut = 0;
    float fin = 1;
    float pas = 1.f/param;
    float p = pas;

    while (p>=debut && p<=fin)
    {
        qDebug() << "p = " << p;
        Point P = S.getValue(p);
        listPoint.push_back(P);
        p+=pas;
    }
    return listPoint;
}

std::vector<Point> Discretisation::discret_segments(std::vector<Segment> listSegments, float param)
{
    std::vector<Point> listPoint;
    std::vector<Point> listPoint2;
    for (int s=0; s<listSegments.size(); s++)
    {
        listPoint2 = discret_segment_seul(listSegments[s], param);
        for (int p=0; p<listPoint2.size(); p++) {
            listPoint.push_back(listPoint2[p]);
        }
    }
    return listPoint;
}














