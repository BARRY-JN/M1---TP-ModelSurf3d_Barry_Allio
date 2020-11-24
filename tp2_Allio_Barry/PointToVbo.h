#ifndef POINTTOVBO_H
#define POINTTOVBO_H

#include <QObject>
#include <QWidget>
#include <QOpenGLFunctions>

#include "point.h"
#include "segment.h"

class PointToVbo
{
public:
    PointToVbo();
    static QVector<GLfloat> convert_listPoints_to_vbo(std::vector<Point> listPoint, std::vector<float> _colors);
    static QVector<GLfloat> convert_listPoints_to_vbo(std::vector<Point> listPoint, float r, float g, float b);
    static QVector<GLfloat> convert_listSegments_to_vbo(std::vector<Segment> listSegment, std::vector<float> colors);
    static QVector<GLfloat> convert_coords_to_vbo(std::vector<float> listCoords, int dim, std::vector<float> _colors, int flagOneColor);

private:

};

#endif
