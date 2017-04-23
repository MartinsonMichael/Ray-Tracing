#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <thread>

#include <cctype>
#include <cstdlib>

#include <FGeometry.h>
#include <TScene.h>
#include <TTriangle.h>
#include <TQuadrangle.h>
#include <TSphere.h>

using namespace std;

//using std::string;
//using std::vector;
//using std::map;

using std::cout;

void TScene::normScreen(TLook &qscr, const QImage &img){
    (void)img;
    qscr = look;
//    TPoint vh, vv;
//    vh = (look.topleft - look.topright) / img.height();
//    vv = (look.topleft - look.bottomleft) / img.width();
//    if (vh.lenQuadr() < vv.lenQuadr()){

//    }
}

void TScene::traceRay(const TRay &ray, TPoint &intersect_point,
                      int &index){
    index = -1;
    TPoint::ld dist = 0;
    for (int i = 0; i < (int)figures.size(); i++){
        if (figures[i]->isIntersect(ray)){
            TPoint point = figures[i]->intersectPoint(ray);
            if (index == -1 || dist > (look.eye - point).lenQuadr()){
                index = i;
                dist = (look.eye - point).lenQuadr();
                intersect_point = point;
            }
        }
    }
}

double TScene::getLightCoefficient(int index, const TPoint &point){
    double light_pwr = 0.0;
    TPoint norm = figures[index]->normal(point);
    for (TLight lgh : lights){
        if (!FGeometry::isOnOneSide(point, norm, look.eye, lgh)){
            continue;
        }
        int ind;
        TPoint npnt;
        traceRay(FGeometry::moveRayABit(FGeometry::getRayFromTo(point, lgh)),
                 npnt, ind);
        if (ind != -1){
            continue;
        }
        light_pwr += std::pow((lgh.getPower() *
                               light_dist / light_power), 2) /
                     (point - lgh).lenQuadr() *
                     FGeometry::getCosFall(lgh - point, norm);
    }
    light_pwr += 0.1;
    return light_pwr;
}

TColor TScene::getRayColor(const TRay &ray, int deep){
    if (deep <= 0){
        return TColor(0.0, 0.0, 0.0);
    }
    TPoint point;
    int ind;
    traceRay(ray, point, ind);
    if (ind == -1){
        return TColor(0.0, 0.0, 0.0);
    }
    TMaterial matr = figures[ind]->getMaterial();
    //output << "f alpha : " << matr.getAlpha() << endl;
    double light_pwr = getLightCoefficient(ind, point);
    TColor color = matr.getColor();
    TColor color_refr = TColor(0.0, 0.0, 0.0);
    if (matr.getAlpha() < 1 - EPS){
        output << "f alpha : " << matr.getAlpha() << endl;
        TRay refraction_ray = std::make_pair(point, point
                                             + (ray.second - ray.first));
        refraction_ray = FGeometry::moveRayABit(
                             FGeometry::getRayFromTo(refraction_ray));
        color_refr = getRayColor(refraction_ray, deep - 1);
        output << color_refr.toStr() << "\n***\n"
               << color.toStr() << "\n***\n"
               << "alpha : " << matr.getAlpha() << "\n"
               << (color * matr.getAlpha() + color_refr * (1 - matr.getAlpha())).toStr()
               << " * " << light_pwr << "\n" << endl;
    }
    color = color.mix(color_refr, matr.getAlpha()) * light_pwr;
    return color;
}

struct ftr{
    QImage im;
    int start;
    int len;
    int anti;
};

void TScene::fillImageThread(QImage &image, int fromW, int number, int anti_aliasing){
    TPoint vh, vw;
    output << image.width() << " " << image.height() << "\n";
    vh = (look.topright - look.topleft) / (image.width() * anti_aliasing);
    vw = (look.bottomleft - look.topleft) / (image.height() * anti_aliasing);
    output << "vh : " << vh[0] << " " << vh[1] << " " << vh[2] << endl;
    for (int i = fromW; i < min(fromW + number, image.width()); i++){
        for (int j = 0; j < image.height(); j++){
            if (i == 300 && j == (int)(image.height() * 0.75)){
                i = 300;
            }
            TColor color = TColor();
            for (int ii = 0; ii < anti_aliasing; ii++){
                for (int jj = 0; jj < anti_aliasing; jj++){
                    color = color +  getRayColor(
                                 make_pair(look.eye, look.topleft +
                                           (vw*j + vh*i)*anti_aliasing +
                                           vw*jj + vh*ii), 2);
                }
            }
            color = color * (1.0 / anti_aliasing * anti_aliasing);
            image.setPixelColor(i, j, color.getQColor());
        }
    }
}

void TScene::fillImage(QImage &image, int thread_count){
    thread_count = 1;
    int anti_al = 1;
    int start = image.width() / thread_count;
    std::thread t1(&TScene::fillImageThread, this, std::ref(image),
                   0, start, anti_al);
    //std::thread t2(&TScene::fillImageThread, this, std::ref(image),
    //               start, start + 1, anti_al);

    t1.join();
    //t2.join();
}

void TScene::splitString(const string &s, vector <string> &v){
    v.clear();
    bool make_new = true;
    for (char c : s){
        if (isspace(c)){
            make_new = true;
            continue;
        }
        if (c == '#'){
            break;
        }
        if (make_new){
            v.push_back("");
            make_new = false;
        }
        v.back() += c;
    }
}

TPoint TScene::getPointFromVS(const vector<string> &v, int ind_start){
    return TPoint(atof(v[ind_start + 0].c_str()),
                  atof(v[ind_start + 1].c_str()),
                  atof(v[ind_start + 2].c_str()));
}

void TScene::loadFromFile(string filename){
    std::ifstream input(filename);
    output.open("output.txt");
    output << "I am still alive!\n";
    output << std::setprecision(2);
    string s;
    vector <string> v;
    string state = "none";
    TMaterial curmaterial;
    bool material_start = false;
    bool referense = false;

    vector <TPoint> p;
    double radius, power;
    double alpha, refract, reflect;
    string matreial_name;
    TColor material_color;
    while(std::getline(input, s)){
        if (s.size() <= 0){
            continue;
        }
        v.clear();
        splitString(s, v);
        if (v.size() <= 0 || v[0].size() <= 0){
            continue;
        }
        if (state == "none"){
            state = v[0];
            continue;
        }
        if (state == "viewport"){
            if (v[0] == "endviewport"){
                state = "none";
                continue;
            }

            if (v[0] == "origin"){
                look.eye = getPointFromVS(v, 1);
            }
            if (v[0] == "topleft"){
                look.topleft = getPointFromVS(v, 1);
            }
            if (v[0] == "bottomleft"){
                look.bottomleft = getPointFromVS(v, 1);
            }
            if (v[0] == "topright"){
                look.topright = getPointFromVS(v, 1);
            }
            continue;
        }

        if (state == "materials"){
            if (v[0] == "endmaterials"){
                state = "none";
                continue;
            }
            if (v[0] == "entry"){
                curmaterial = TMaterial();
                material_start = true;
            }
            if (v[0] == "endentry"){
                materials[matreial_name] = TMaterial(matreial_name,
                                                     material_color,
                                                     alpha,
                                                     reflect,
                                                     refract);
                material_start = false;
            }
            if (material_start){
                if (v[0] == "name"){
                    matreial_name = v[1];
                }
                if (v[0] == "color"){
                    material_color = TColor(atoi(v[1].c_str()),
                                               atoi(v[2].c_str()),
                                               atoi(v[3].c_str()) );
                }
                if (v[0] == "alpha"){
                    alpha = atof(v[1].c_str());
                }
                if (v[0] == "reflect"){
                    reflect = atof(v[1].c_str());
                }
                if (v[0] == "refract"){
                    refract = atof(v[1].c_str());
                }
            }
            continue;
        }

        if (state == "geometry"){
            if (v[0] == "endgeometry"){
                state = "none";
                continue;
            }
            if (v[0] == "material"){
                curmaterial = materials[v[1]];
            }
            if (v[0] == "triangle" || v[0] == "quadrangle"
                || v[0] == "sphere"){
                p.clear();
                curmaterial = TMaterial();
            }
            if (v[0] == "radius"){
                radius = atof(v[1].c_str());
            }
            if (v[0] == "endtriangle"){
                figures.push_back(new TTriangle(p[0], p[1], p[2], curmaterial));
            }
            if (v[0] == "endquadrangle"){
                figures.push_back(new TQuadrangle(p[0], p[1], p[2], p[3],
                        curmaterial));
            }
            if (v[0] == "endsphere"){
                figures.push_back(new TSphere(p[0], radius, curmaterial));
            }
            if (v[0] == "vertex" || v[0] == "coords"){
                p.push_back(getPointFromVS(v, 1));
            }
        }

        if (state == "lights"){
            if (v[0] == "endlights"){
                state = "none";
                continue;
            }
            if (v[0] == "reference"){
                referense = true;
            }
            if (v[0] == "endreference"){
                referense = false;
            }
            if (referense){
                if (v[0] == "power"){
                    light_power = atof(v[1].c_str());
                }
                if (v[0] == "distance"){
                    light_dist = atof(v[1].c_str());
                }
            }
            else{
                if (v[0] == "point"){
                    p.clear();
                    power = 0;
                }
                if (v[0] == "endpoint"){
                    lights.push_back(TLight(p[0], power, false));
                }
                if (v[0] == "vertex" || v[0] == "coords"){
                    p.push_back(getPointFromVS(v, 1));
                }
                if (v[0] == "power"){
                    power = atof(v[1].c_str());
                }
            }
        }
    }
    input.close();

    output << "Load:\n";
    output << "materials loaded : " << materials.size() << endl;
    output << "figures loaded : " << figures.size() << endl;
    output << "lights loaded : " << lights.size() << endl;
    output << "***\n\n";
}
