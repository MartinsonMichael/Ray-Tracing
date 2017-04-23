#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include <QImage>
#include <QColor>

#include <TMaterial.h>
#include <TPoint.h>
#include <TLight.h>
#include <TFigure.h>

#ifndef TSCENE
#define TSCENE

using std::string;
using std::vector;
using std::map;

struct TLook{
    TPoint eye;
    TPoint topleft;
    TPoint topright;
    TPoint bottomleft;

    TLook() {}
};

class TScene{
public:

    void loadFromFile(string filename);
    void fillImage(QImage &image, int thread_count);

private:
    TLook look;
    TPoint::ld light_power, light_dist;
    map <string, TMaterial> materials;
    vector <TLight> lights;
    vector <TFigure*> figures;

    // for debug
    std::ofstream output;
    // end for debug

    static void splitString(const string &s, vector <string> &v);
    static TPoint getPointFromVS(const vector<string> &v, int ind_start);

    void fillImageThread(QImage &image, int fromW, int number, int anti_aliasing);

    void normScreen(TLook &qscr, const QImage &img);
    TColor getRayColor(const TRay &ray, int deep);
    double getLightCoefficient(int index, const TPoint &point);
    void traceRay(const TRay &ray, TPoint &intersect_point,
                  int &index);
};

#endif // TSCENE

