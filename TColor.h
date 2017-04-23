#include <QColor>
#include <string>

#ifndef TCOLOR_H
#define TCOLOR_H

using std::string;

class TColor{
public:
    double r, g, b;

public:

    TColor() : r(0.0), g(0.0), b(0.0) {}
    TColor(int _r, int _g, int _b) : r(_r/255.0), g(_g/255.0), b(_b/255.0) {}
    TColor(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}
    TColor(const TColor &color) : r(color.r), g(color.g), b(color.b) {}

    QColor getQColor() const{
        return QColor((int)(std::min(1.0, r) * 255),
                      (int)(std::min(1.0, g) * 255),
                      (int)(std::min(1.0, b) * 255));
    }

    TColor operator *(double alpha) const{
        TColor color = TColor();
        color.r = r * alpha;
        color.g = g * alpha;
        color.b = b * alpha;
        return color;
    }

    TColor operator /(double alpha) const{
        TColor color = TColor();
        color.r = r / alpha;
        color.g = g / alpha;
        color.b = b / alpha;
        return color;
    }

    TColor operator +(TColor c) const{
        TColor color = TColor();
        color.r = r + c.r;
        color.g = g + c.g;
        color.b = b + c.b;
        return color;
    }

    TColor mix(const TColor &c, double alpha) const {
        TColor color = TColor();
        color.r = r * alpha + c.r * (1.0 - alpha);
        color.g = g * alpha + c.g * (1.0 - alpha);
        color.b = b * alpha + c.b * (1.0 - alpha);
        return color;
    }

    string toStr() const {
        return std::to_string(r) + " " + std::to_string(g)
                + " " + std::to_string(b);
    }
};

#endif // TCOLOR_H
