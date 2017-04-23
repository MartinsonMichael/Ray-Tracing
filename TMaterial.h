#include <string>
#include <QColor>

#include "TColor.h"

#ifndef TMATERIAL
#define TMATERIAL

using std::string;

class TMaterial{
private:
    string name;
    TColor color;
    double alpha;
    double reflect;
    double refract;
public:
    TMaterial() : color(0, 0, 0), alpha(1), reflect(0), refract(1) {}

    TMaterial(const TMaterial &m) : name(m.name), color(m.color),
        alpha(m.alpha), reflect(m.reflect), refract(m.refract) {}

    TMaterial(const string &_name, const TColor &_color, double _alpha,
              double _reflect, double _refract) : name(_name), color(_color),
        alpha(_alpha), reflect(_reflect), refract(_refract) {}

    TColor getColor() const {return color;}
    double getAlpha() const {return alpha;}
};

#endif // TMATERIAL

