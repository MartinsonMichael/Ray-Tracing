#include "TSphere.h"
#include "FGeometry.h"

bool TSphere::isIntersect(const TRay &ray) const {
    if (FGeometry::distToLine(ray, _a) > _radius){
        return false;
    }
    std::pair<TPoint, TPoint> pinters = FGeometry::intersectSphereLine(*this, ray);
    TPoint one = pinters.first, two = pinters.second;
    TPoint v = (ray.second - ray.first).norm();
    if (!FGeometry::isSoDistanse(one - ray.first, v)
        && !FGeometry::isSoDistanse(two - ray.first, v)){
        return false;
    }
    return true;
}

TPoint TSphere::intersectPoint(const TRay &ray) const {
    std::pair<TPoint, TPoint> pinters = FGeometry::intersectSphereLine(*this, ray);
    TPoint one = pinters.first, two = pinters.second;
    TPoint v = (ray.second - ray.first).norm();
    if (FGeometry::isSoDistanse(one - ray.first, v)){
        if (FGeometry::isSoDistanse(two - ray.first, v)){
            return (FGeometry::distToPoint(ray.second, one) <
                    FGeometry::distToPoint(ray.second, two)) ? one : two;
        }
        else{
            return one;
        }
    }
    else{
        if (FGeometry::isSoDistanse(two - ray.first, v)){
            return two;
        }
    }
}

TPoint TSphere::normal(const TPoint &point) const {
    return (point - _a).norm();
}
