#ifndef MAILLAGE_H
#define MAILLAGE_H
#include <QVector>
#include <QPair>
#include <QMap>
#include "sommet.h"
#include "triangle.h"

class Maillage
{
public:
    Maillage(int nbsommets=0, int nbtriangles=0);
    QVector<Sommet> sommets;
    QVector<Triangle> triangles;
    QMap<QPair<int, int>, QVector<int> > map;
    int infiniteSommet;
    void addSommet(int index, float x, float y, float z);
    void addTriangle(int index, int i, int j, int k);
    void parseMap();
    bool seeArrete(int index, int a, int b);
    bool isInTrianle(int pointIndex, int triangleIndex);
    void flipArrete(int triangleA, int triangleB);
    bool divideTriangle(int sommet, int triangle);
    void addPoint(float x, float y, float z);
};

#endif // MAILLAGE_H
