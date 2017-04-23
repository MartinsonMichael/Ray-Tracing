#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#include "TTriangle.h"
#include "FGeometry.h"

bool TTriangle::isIntersect(const TRay &ray) const{
    if (abs(FGeometry::volume(ray.first - _a, _b - _a, _c - _a) -
        FGeometry::volume(ray.second - _a, _b - _a, _c - _a)) < EPS){
        return false;
    }
    TPoint point = FGeometry::intersectPlaneLine(*this, ray);
    if (!FGeometry::isSoDistanse(point - ray.first, ray.second - ray.first)){
        return false;
    }
    return FGeometry::isInsideOfTriangle(*this, point);
}

TPoint TTriangle::intersectPoint(const TRay &ray) const{
    return FGeometry::intersectPlaneLine(*this, ray);
}

TPoint TTriangle::normal(const TPoint &point) const{
    (void)point;
    return FGeometry::planeNormal(*this);
}
