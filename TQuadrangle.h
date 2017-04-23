#include <TFigure.h>

#ifndef TQUADRANGLE_H
#define TQUADRANGLE_H


class TQuadrangle : public TFigure{
public:
    TQuadrangle() : _a(), _b(), _c(), _d() {}
    TQuadrangle(TPoint a, TPoint b, TPoint c, TPoint d) :
        _a(a), _b(b), _c(c), _d(d)
        {_material = TMaterial();}
    TQuadrangle(TPoint a, TPoint b, TPoint c, TPoint d, TMaterial mater) :
        _a(a), _b(b), _c(c), _d(d) { _material = TMaterial(mater);}

    bool isIntersect(const TRay &ray) const ;
    TPoint intersectPoint(const TRay &ray) const ;
    TPoint normal(const TPoint &point) const ;

    TPoint a() const {return _a;}
    TPoint b() const {return _b;}
    TPoint c() const {return _c;}
    TPoint d() const {return _d;}

private:
    TPoint _a, _b, _c, _d;
};

#endif // TQUADRANGLE_H
