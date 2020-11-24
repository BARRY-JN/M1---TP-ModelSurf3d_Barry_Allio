#include "courbeparametrique.h"
#include <QDebug>

CourbeParametrique::CourbeParametrique()
{

}

CourbeParametrique::CourbeParametrique(std::vector<Point> liste)
{
    set_point_list(liste);
}

void CourbeParametrique::set_point_list(std::vector<Point> list)
{
    ListePoint.clear();
    for(int i=0; i<list.size(); i++)
    {
        add_point(list[i]);
    }
}

std::vector<Point> CourbeParametrique::Liste_Point()
{
    return ListePoint;
}

void CourbeParametrique::add_point(Point P)
{
    ListePoint.push_back(P);
}

void CourbeParametrique::display_points_courbe()
{
    for (int i=0; i<ListePoint.size(); i++)
        ListePoint[i].display(i);
}
