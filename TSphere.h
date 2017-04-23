#include <TFigure.h>

#ifndef TSPHERE_H
#define TSPHERE_H



class TSphere : public TFigure{
public:
    TSphere() : _a(), _radius(0)
        {_material = TMaterial();}
    TSphere(TPoint a, TPoint::ld radius) : _a(a), _radius(radius)
        {_material = TMaterial();}
    TSphere(TPoint a, TPoint::ld radius, TMaterial material) :
        _a(a), _radius(radius) {_material = TMaterial(material);}


    bool isIntersect(const TRay &ray) const ;
    TPoint intersectPoint(const TRay &ray) const ;
    TPoint normal(const TPoint &point) const;

    TPoint a() const {return _a;}
    TPoint::ld radius() const {return _radius;}

private:
    TPoint _a;
    TPoint::ld _radius;
};

#endif // TSPHERE_H
