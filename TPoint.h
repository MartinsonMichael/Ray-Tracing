#include <math.h>
#include <fstream>
#include <algorithm>

#ifndef TPOINT
#define TPOINT

class TPoint;
typedef std::pair<TPoint, TPoint> TRay;
typedef std::pair<TPoint, TPoint> TLine;

class TPoint{
public:
    typedef double ld;
private:
    ld x, y, z;
public:

    TPoint() : x(0), y(0), z(0) {}
    TPoint(ld x0, ld y0, ld z0) : x(x0), y(y0), z(z0) {}
    TPoint(const TPoint &v) : x(v.x), y(v.y), z(v.z) {}

//    ld operator[](size_t  index);
//    TPoint operator +(const TPoint &v) const;
//    TPoint operator +=(const TPoint &v);
//    TPoint operator -(const TPoint &v) const;
//    TPoint operator *(ld s);
//    TPoint operator *=(ld s);
//    TPoint operator /(ld s);
//    TPoint operator /=(ld s);

//    double dotProduct(const TPoint &v) const;
//    TPoint crossProduct(const TPoint &v) const;
//    double len() const;
//    double lenQuadr() const;
//    TPoint norm();


    ld operator [](size_t index){
        return (index == 0) ? x : (index == 1) ? y : z;
    }

    TPoint operator +(const TPoint &v) const{
        return TPoint(x+v.x, y+v.y, z+v.z);
    }

    TPoint operator +=(const TPoint &v){
        x += v.x, y += v.y, z += v.z;
        return *this;
    }

    TPoint operator -(const TPoint &v) const{
        return TPoint(x-v.x, y-v.y, z-v.z);
    }

    TPoint operator *(ld s){
        return TPoint(x * s, y * s, z * s);
    }

    TPoint operator /(ld s){
        return TPoint(x / s, y / s, z / s);
    }

    TPoint operator *=(ld s){
        x *= s, y *= s, z *= s;
        return *this;
    }

    TPoint operator /=(ld s){
        x /= s, y /= s, z /= s;
        return *this;
    }

    double lenQuadr() const {
        return (x*x + y*y + z*z);
    }

    double len() const {
        return sqrt(x*x + y*y + z*z);
    }

    TPoint norm(){
        return (*this / len());
    }

    double dotProduct(const TPoint &v) const{
        return x*v.x + y*v.y + z*v.z;
    }

    TPoint crossProduct(const TPoint &v) const{
        return TPoint(y*v.z - z*v.y, -x*v.z + z*v.x, x*v.y - y*v.x);
    }

};

#endif // TPOINT
