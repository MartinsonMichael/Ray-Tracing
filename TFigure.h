#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#include <TPoint.h>
#include <TMaterial.h>

#ifndef TOBJECT
#define TOBJECT

class TFigure{
public:
    virtual bool isIntersect(const TRay &ray) const = 0;
    virtual TPoint intersectPoint(const TRay &ray) const = 0;
    virtual TPoint normal(const TPoint &point) const = 0;

    TMaterial getMaterial() const {return _material;}

protected:
    TMaterial _material;
};

#endif // TOBJECT

