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

QVector<GLfloat> PointToVbo::convert_listPoints_to_vbo(std::vector<Point> listPoint, float colorR, float colorG, float colorB)
{
    int dim=3;
    std::vector<float> coords;
    for (unsigned p=0; p<listPoint.size(); p++) {
        coords.push_back(listPoint[p].getX());
        coords.push_back(listPoint[p].getY());
        coords.push_back(listPoint[p].getZ());
    }
    QVector<GLfloat> vertData;
    std::vector<float> colors;
    colors.push_back(colorR);
    colors.push_back(colorG);
    colors.push_back(colorB);
    vertData = PointToVbo::convert_coords_to_vbo(coords, dim, colors, 1);
    return vertData;
}

//Adapte les coordonnées pour créer un polyèdre de controle de degré 3
QVector<GLfloat> PointToVbo::convert_to_grid(std::vector<Point> listPoint,int dim1, int dim2, float colorR, float colorG, float colorB)
{
    for (int j=0; j<dim2; j+=1){
        for (int i=0; i<dim1*dim2; i+=dim2){
            listPoint.push_back(listPoint[j+i]);
        }
    }
    return convert_listPoints_to_vbo(listPoint, colorR, colorG, colorB);;
}

//Adapte les cordonnées pour dessiner avec des triangles
//Dim1 -> colonnes     Dim2->lignes
QVector<GLfloat> PointToVbo::convert_triangulation(std::vector<Point> listPoint,int dim1, int dim2, float colorR, float colorG, float colorB)
{
    std::vector<Point> ListePointTriangle;

    for (int i=0; i<(dim1*dim2)-dim2; i+=dim2){
        for (int j=0; j<dim2-1; j++){
            int k = i+j;
            ListePointTriangle.push_back(listPoint[k]);
            ListePointTriangle.push_back(listPoint[k+1]);
            ListePointTriangle.push_back(listPoint[k+dim2]);
            ListePointTriangle.push_back(listPoint[k+dim2]);
            ListePointTriangle.push_back(listPoint[k+1+dim2]);
            ListePointTriangle.push_back(listPoint[k+1]);
        }
    }
    return convert_listPoints_to_vbo(ListePointTriangle, colorR, colorG, colorB);
}









