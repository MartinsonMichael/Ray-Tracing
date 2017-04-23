#ifndef FGEOMETRY_H
#define FGEOMETRY_H

#include <TPoint.h>
#include <TSphere.h>
#include <TTriangle.h>

class FGeometry{
public:
    #define EPS 1e-5

    static TPoint::ld volume(const TPoint &a, const TPoint &b, const TPoint &c){
        return a.crossProduct(b).dotProduct(c);
    }

    static TPoint planeNormal(const TTriangle &plane){
        return ((plane.b() - plane.a()).crossProduct(
                    plane.c() - plane.a())).norm();
    }

    static TPoint::ld getArea(const TTriangle &triangle){
        return (triangle.b() - triangle.a()).crossProduct(
                    triangle.c() - triangle.a()).len() / 2;
    }

    static TPoint::ld distToPoint(const TPoint &a, const TPoint &b){
        return (a - b).len();
    }

    static TPoint::ld distToLine(const TRay &line, const TPoint &a){
        return (line.first - a).crossProduct(line.second - a).len()/
                (line.first - line.second).len();
    }

    static TPoint::ld distToPlane(const TTriangle &plane, const TPoint &point){
        return volume(plane.a() - point, plane.b() - point, plane.c() - point) /
                getArea(plane);
    }

    static TPoint intersectPlaneLine(const TTriangle &plane, const TRay &line){
        return line.second + ((line.second - line.first).norm()) *
                (line.second - line.first).len()*
                distToPlane(plane, line.second) /
                (distToPlane(plane, line.first) - distToPlane(plane, line.second));
    }

    static bool isCollinear(const TPoint &a, const TPoint &b){
        return a.crossProduct(b).lenQuadr() < EPS;
    }

    static bool isSoDistanse(const TPoint &a, const TPoint &b){
        return isCollinear(a, b) && (a - b).lenQuadr() < (a + b).lenQuadr();
    }

    static bool isInsideOfTriangle(const TTriangle &triangle, const TPoint &point){
        if (distToPlane(triangle, point) > EPS){
            return false;
        }
        TPoint v1, v2, v3;
        v1 = (point - triangle.a()).crossProduct(triangle.b() - triangle.a());
        v2 = (point - triangle.b()).crossProduct(triangle.c() - triangle.b());
        v3 = (point - triangle.c()).crossProduct(triangle.a() - triangle.c());
        return isSoDistanse(v1, v2) && isSoDistanse(v2, v3);
    }

    static TPoint::ld sgn(TPoint::ld x){
        return (x > 0) ? 1 : -1;
    }

    static TPoint projectionToLine(const TRay &ray, const TPoint &point){
        return ray.second + (ray.second - ray.first).norm() *
                sgn(-(ray.first - ray.second).dotProduct(point - ray.second)) *
                std::sqrt((point - ray.second).lenQuadr()
                          - std::pow(distToLine(ray, point), 2));
    }

    static std::pair<TPoint, TPoint> intersectSphereLine(const TSphere &s,
                                                         const TRay &ray){
        TPoint one, two, prjc = FGeometry::projectionToLine(ray, s.a());
        TPoint::ld l = std::sqrt(s.radius() * s.radius()
                                 - std::pow(FGeometry::distToPoint(s.a(), prjc), 2));
        TPoint v = (ray.second - ray.first).norm();
        one = prjc + v * l;
        two = prjc - v * l;
        return std::make_pair(one, two);
    }

    static TRay getRayFromTo(const TRay &ray){
        return getRayFromTo(ray.first, ray.second);
    }

    static TRay getRayFromTo(const TPoint &from, const TPoint &to){
        return std::make_pair(from, from + (to - from).norm() / 10);
    }

    static TRay moveRayABit(const TRay &ray){
        TPoint v = (ray.second - ray.first).norm() / 100;
        return std::make_pair(ray.first + v, ray.second + v);
    }

    static double getCosFall(const TPoint &v, const TPoint &norm){
        return v.dotProduct(norm) / (v.len() * norm.len());
    }

    static bool isOnOneSide(const TPoint &point, const TPoint &norm,
                            const TPoint &a, const TPoint &b){
        return sgn(norm.dotProduct(a - point)) ==
                sgn(norm.dotProduct(b - point));
    }

    static TPoint getReflection(const TPoint &v, const TPoint &point,
                                const TPoint &norm){
        return (norm + point) * (v + point).dotProduct(norm + point) * 2
                - (v + point);
    }

};

#endif // FGEOMETRY_H
