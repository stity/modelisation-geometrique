#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <QVector>
#include "sommet.h"

class Sommet;

class Triangle
{
public:
    Triangle();
    QVector<int> triangles;
    QVector<int> sommets;
    void setSommets (int s1, int s2, int s3);
    void setTriangles (int t1, int t2, int t3);
};

#endif // TRIANGLE_H
