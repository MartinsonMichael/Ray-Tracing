#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#include <TFigure.h>

#ifndef TTRIANGLE_H
#define TTRIANGLE_H


class TTriangle : public TFigure{
public:
    TTriangle() : _a(), _b(), _c() {}
    TTriangle(TPoint a, TPoint b, TPoint c) : _a(a), _b(b), _c(c)
        {_material = TMaterial();}
    TTriangle(TPoint a, TPoint b, TPoint c, TMaterial mater) :
        _a(a), _b(b), _c(c) { _material = TMaterial(mater);}

    bool isIntersect(const TRay &ray) const ;
    TPoint intersectPoint(const TRay &ray) const;
    TPoint normal(const TPoint &point) const;

    TPoint a() const {return _a;}
    TPoint b() const {return _b;}
    TPoint c() const {return _c;}

private:
    TPoint _a, _b, _c;
};

#endif // TTRIANGLE_H
