#include <cmath>

#include "segment.h"
#include <QDebug>

Segment::Segment()
{
    //pointList = new Point[2];
    _pointList.clear();
    Point X;
    for (unsigned i=0; i<2; i++)
        _pointList.push_back(X);
}

Segment::~Segment()
{
    //delete [] pointList;
    //pointList = nullptr;
}

Segment::Segment(const Segment & s)
{
    //pointList = new Point[2];
    _pointList.clear();
    Point X;
    for (unsigned i=0; i<2; i++)
        _pointList.push_back(X);

    for (unsigned i=0; i<2; ++i)
        _pointList[i] = s._pointList[i];
}

void Segment::setStart(const Point & p)
{
    _pointList[0] = p;
}

void Segment::setEnd(const Point & p)
{
    _pointList[1] = p;
}

void Segment::setN(unsigned r, const Point & p)
{
	if (r>1)
		r=1;
    _pointList[r] = p;
}

Point Segment::getN(unsigned r) const
{
	if (r>1)
		r=1;

    return _pointList[r];
}

Point Segment::getStart() const
{
	return getN(0);
}


Point Segment::getEnd() const
{
	return getN(1);
}

float Segment::length() const
{
	float res=0.0f;

	for (unsigned i=0; i<3; ++i)
        res += pow((_pointList[1]).getN(i) - (_pointList[0]).getN(i), 2.f);

	return sqrt(res);
}

Segment& Segment::operator= (const Segment &s)
{
	for (unsigned i=0; i<2; ++i)
        _pointList[i] = s._pointList[i];

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Segment& s)
{
    return out << s._pointList[0] << " -- " << s._pointList[1];
}

Point Segment::getValue(float p)
{
    Point A = getStart();
    Point B = getEnd();
    Point C;
    if (p>=0 || p<=1) {
        float xA = A.getX(), yA = A.getY();
        float xB = B.getX(), yB = B.getY();
        float xC = (1-p)*xA + p*xB;
        float yC = (1-p)*yA + p*yB;
        float zC = A.getZ();

        C.set(xC, yC, zC);
        qDebug() << "A : " << xA << yA<< "B : " << xB << yB<< "C : " << xC << yC;
    }
    return C;
}






