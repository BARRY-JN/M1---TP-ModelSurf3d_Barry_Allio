#include "PointToVbo.h"
#include <QDebug>

PointToVbo::PointToVbo()
{

}

QVector<GLfloat> PointToVbo::convert_coords_to_vbo(std::vector<float> listCoords, int dim, std::vector<float> _colors, int flagOneColor)
{
    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;
    QVector<GLfloat> vertData;

    if (listCoords.size()%dim == 0) {
        int nbPoints = listCoords.size() / dim;

        for (int c=0; c<listCoords.size(); c++)
            vertices.append(listCoords[c]);
        for (int c=0; c<_colors.size(); c++)
            colors.append(_colors[c]);

        for (int p = 0; p < nbPoints; ++p)
        {
            for (int j = 0; j < dim; j++)
                vertData.append(vertices[p*dim+j]);
            for (int j = 0; j < 3; j++)
                if (flagOneColor)
                    vertData.append(colors[j]);
                else
                    vertData.append(colors[p*dim+j]);
        }
        return vertData;
    }else{exit(1);}

}

//De liste de points, à un ensemble de QVector de GLfloat, adapté pour un vbo OpenGl
QVector<GLfloat> PointToVbo::convert_listPoints_to_vbo(std::vector<Point> listPoint, std::vector<float> colors)
{
    int dim=3;
    std::vector<float> coords;
    for (unsigned p=0; p<listPoint.size(); p++) {
        coords.push_back(listPoint[p].getX());
        coords.push_back(listPoint[p].getY());
        coords.push_back(listPoint[p].getZ());
    }
    QVector<GLfloat> vertData;
    vertData = PointToVbo::convert_coords_to_vbo(coords, dim, colors, 1);
    return vertData;
}








