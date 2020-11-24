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

std::vector<Point> discretiser_bezier(CourbeBezier *CB, int nbParam)
{
    std::vector<Point> ListePoint;
    float pas = 1/nbParam;
    float currentPas = pas;
    while (currentPas>=0 && currentPas<=1)
    {
        ListePoint.push_back(CB->eval(currentPas));
        currentPas+=pas;
    }
    return ListePoint;
}

float norme(Point P)
{
    return sqrt(pow(P.getX(),2)+pow(P.getY(),2)+pow(P.getZ(),2));
}

float ProdScalaire(Point v1, Point v2){
    return v1.getX()*v2.getX()+v1.getY()*v2.getY()+v1.getZ()*v2.getZ();
}

std::vector<Point> discretiser_bezier_de_front(CourbeBezier *CB, int nbParam)
{
    std::vector<Point> ListePoint;

    float TaillePas = 1/nbParam;
    float PasCourant = TaillePas;
    float seuilBas = 0.1f;
    float seuilHaut = 1.f;
    float currentAngle;

    Point v1 = CB->eval(0);
    Point v2 = CB->eval(0+TaillePas);
    Point tangente = CB->eval_deriv(PasCourant, 0.003);

    while (PasCourant>=0 && PasCourant<=1 )
    {
        v1 = CB->eval(PasCourant);
        v2 = CB->eval(PasCourant+TaillePas);
        float prodScal = ProdScalaire(v1,v2);
        currentAngle = prodScal/(norme(v1)*norme(v2));


        if (currentAngle > seuilHaut)
        {
            TaillePas = TaillePas/2;
        }
        else if (currentAngle < seuilBas) {
            TaillePas += TaillePas/2;
        }
        else if (currentAngle == seuilBas){
            ListePoint.push_back(CB->eval(PasCourant+TaillePas));
            PasCourant+=TaillePas;
        }
    }
    return ListePoint;
}

std::vector<Point> Discretisation::discretiser_courbe(CourbeBezier *CB, int nbParam, int methode)
{
    std::vector<Point> ListePoint;

    switch (methode)
    {
    case FRONT:
        ListePoint = discretiser_bezier_de_front(CB, nbParam);
        break;
    default:
        ListePoint = discretiser_bezier(CB, nbParam);
        break;
    }

    return ListePoint;
}

std::vector<Point> Discretisation::discretiser_carreaux_bezier(CarreauxBezier *carB,int nbParam1, int nbParam2,int sens)
{
    std::vector<Point> ListePoint;
    float pas1 = 1/nbParam1-1;
    float pas2 = 1/nbParam2-1;

    for (float u=0 ; u<=1; u+=pas1)
    {
        for (float v=0 ; v<=1 ;v+=pas2 )
        {
            switch (sens){
                case 0:
                    ListePoint.push_back(carB->eval(u, v));
                default:
                    ListePoint.push_back(carB->eval(v, u));
            }
        }
    }
    return ListePoint;
}















