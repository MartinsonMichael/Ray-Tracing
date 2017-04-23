#include <TPoint.h>

#ifndef TLIGHT
#define TLIGHT

class TLight : public TPoint{
public:
    TLight() : _power(0), _isVisable(false) {}
    TLight(const TPoint &p) :
        TPoint(p), _power(0), _isVisable(false) {}
    TLight(const TPoint &p, double power, double isVisable) :
        TPoint(p), _power(power), _isVisable(isVisable) {}

    double getPower() const {return _power;}
    double isVisable() const {return _isVisable;}

private:
    double _power;
    bool _isVisable;
};

#endif // TLIGHT

