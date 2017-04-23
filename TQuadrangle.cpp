#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

#include "TQuadrangle.h"
#include "TTriangle.h"
#include "FGeometry.h"

bool TQuadrangle::isIntersect(const TRay &ray) const {
    if (FGeometry::volume(ray.first - _a, _b - _a, _c - _a) ==
        FGeometry::volume(ray.second - _a, _b - _a, _c - _a)){
        return false;
    }
    TPoint point = FGeometry::intersectPlaneLine(TTriangle(_a, _b, _c), ray);
    if (!FGeometry::isSoDistanse(point - ray.first, ray.second - ray.first)){
        return false;
    }
    if (FGeometry::isInsideOfTriangle(TTriangle(_a, _b, _c), _d)){
        return FGeometry::isInsideOfTriangle(TTriangle(_a, _b, _d), point) ||
               FGeometry::isInsideOfTriangle(TTriangle(_b, _d, _c), point);
    }
    return FGeometry::isInsideOfTriangle(TTriangle(_a, _b, _c), point) ||
           FGeometry::isInsideOfTriangle(TTriangle(_a, _c, _d), point);
}

TPoint TQuadrangle::intersectPoint(const TRay &ray) const {
    return FGeometry::intersectPlaneLine(TTriangle(_a, _b, _c), ray);
}

TPoint TQuadrangle::normal(const TPoint &point) const {
    (void)point;
    return FGeometry::planeNormal(TTriangle(_a, _b, _c));
}
